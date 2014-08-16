// Base32 implementation
//
// Copyright 2010 Google Inc.
// Author: Markus Gutschke
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string.h>

#include "base32alloc.h"

const uint8_t* base32_decode_alloc(
   const uint8_t *encoded, int length, int* decoded_len
) {
  int buffer = 0;
  int bitsLeft = 0;
  int count = 0;
  int bufSize = length / 8;
  const uint8_t* ptr;
  uint8_t* result;
  uint8_t ch;

  result = calloc( bufSize, sizeof( uint8_t ) );

  for (ptr = encoded; *ptr; ++ptr) {
    ch = *ptr;
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '-') {
      continue;
    }
    buffer <<= 5;

    // Deal with commonly mistyped characters
    if (ch == '0') {
      ch = 'O';
    } else if (ch == '1') {
      ch = 'L';
    } else if (ch == '8') {
      ch = 'B';
    }

    // Look up one base32 digit
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
      ch = (ch & 0x1F) - 1;
    } else if (ch >= '2' && ch <= '7') {
      ch -= '2' - 26;
    } else {
      // XXX?
      //free(result);
      //return NULL;
      //return result;
      break;
    }

    buffer |= ch;
    bitsLeft += 5;
    if (bitsLeft >= 8) {
      result[count++] = buffer >> (bitsLeft - 8);
      bitsLeft -= 8;
    }

    if (count + 1 >= bufSize) {
      // We've outgrown our buffer, so add another spot.
      bufSize += 1;
      result = realloc( result, bufSize * sizeof( uint8_t ) );
    }

  }
  if (count < bufSize) {
    result[count] = '\000';
  }
  if (NULL != decoded_len) {
    *decoded_len = count;
  }
  return result;
}

const uint8_t* base32_encode_alloc(const uint8_t *data, int length) {
  int bufSize = length * 8;
  uint8_t* result;
  int count = 0;

  if (length < 0 || length > (1 << 28)) {
    return NULL;
  }

  result = calloc( bufSize, sizeof( uint8_t ) );
  
  if (length > 0) {
    int buffer = data[0];
    int next = 1;
    int bitsLeft = 8;
    while (bitsLeft > 0 || next < length) {
      if (bitsLeft < 5) {
        if (next < length) {
          buffer <<= 8;
          buffer |= data[next++] & 0xFF;
          bitsLeft += 8;
        } else {
          int pad = 5 - bitsLeft;
          buffer <<= pad;
          bitsLeft += pad;
        }
      }
      int index = 0x1F & (buffer >> (bitsLeft - 5));
      bitsLeft -= 5;
      result[count++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"[index];
      if (count + 1 >= bufSize) {
        // We've outgrown our buffer, so add another spot.
        bufSize += 1;
        result = realloc( result, bufSize * sizeof( uint8_t ) );
      }
    }
  }
  if (count < bufSize) {
    result[count] = '\000';
  }

  return result;
}

#ifdef BSTRING

bstring base32_decode_bstr(bstring encoded) {
  int buffer = 0;
  int bitsLeft = 0;
  int count = 0;
  const uint8_t* ptr;
  bstring result;
  uint8_t ch;
  bstring chout;

  chout = bfromcstr("");
  result = bfromcstr("");

  for (ptr = bdata(encoded); *ptr; ++ptr) {
    ch = *ptr;
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '-') {
      continue;
    }
    buffer <<= 5;

    // Deal with commonly mistyped characters
    if (ch == '0') {
      ch = 'O';
    } else if (ch == '1') {
      ch = 'L';
    } else if (ch == '8') {
      ch = 'B';
    }

    // Look up one base32 digit
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
      ch = (ch & 0x1F) - 1;
    } else if (ch >= '2' && ch <= '7') {
      ch -= '2' - 26;
    } else {
      // XXX?
      //bdestroy(result);
      bdestroy(chout);
      //return NULL;
      return result;
    }

    buffer |= ch;
    bitsLeft += 5;
    if (bitsLeft >= 8) {
      bassignformat(chout, "%c", (char)(buffer >> (bitsLeft - 8)));
      bsetstr(result, count++, chout, '\0');
      bitsLeft -= 8;
    }
  }
  bdestroy(chout);
  return result;
}

bstring base32_encode_bstr(bstring data) {
  bstring result;
  bstring chout;
  int count = 0;

  if (blength(data) < 0 || blength(data) > (1 << 28)) {
    return NULL;
  }

  result = bfromcstr("");
  chout = bfromcstr("");

  if (blength(data) > 0) {
    int buffer = bdata(data)[0];
    int next = 1;
    int bitsLeft = 8;
    while (bitsLeft > 0 || next < blength(data)) {
      if (bitsLeft < 5) {
        if (next < blength(data)) {
          buffer <<= 8;
          buffer |= bdata(data)[next++] & 0xFF;
          bitsLeft += 8;
        } else {
          int pad = 5 - bitsLeft;
          buffer <<= pad;
          bitsLeft += pad;
        }
      }
      int index = 0x1F & (buffer >> (bitsLeft - 5));
      bitsLeft -= 5;
      bassignformat(
         chout,
         "%c",
         "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"[index]
      );
      bsetstr(result, count++, chout, '\0');
    }
  }
  bdestroy(chout);

  return result;
}

#endif /* BSTRING */

