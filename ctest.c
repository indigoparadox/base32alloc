
#include <stdio.h>

#include "base32alloc.h"

int main( int argc, char* argv[] ) {
	uint8_t* buffer_out;
	char* buffer_in = argv[1];

   buffer_out = base32_encode_alloc( buffer_in, strlen(  buffer_in ) );

	printf( "%s\n", (char*)buffer_out );
}

