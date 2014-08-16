
[CCode(cheader_filename = "base32alloc.h")]
namespace Base32 {
   [CCode (cname = "base32_encode_alloc", array_length = "false", array_null_terminated = "true")]
   public static unowned uint8[] encode(
      [CCode(array_length_pos = 1.2)] uint8[] data
   );
   [CCode (cname = "base32_decode_alloc", array_length = "false", array_null_terminated = "true")]
   public static unowned uint8[] decode(
      [CCode(array_length_pos = 1.2)] uint8[] data, ref int decoded_len
   );
}

