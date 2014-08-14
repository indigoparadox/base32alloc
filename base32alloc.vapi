
[CCode(cheader_filename = "base32.h")]
namespace Base32 {
   [CCode (cname = "base32_encode_alloc", array_length = "false", array_null_terminated = "true")]
   public static unowned uint8[] encode(
      [CCode(array_length_pos = 1.2)] uint8[] data
   );
}

