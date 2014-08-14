
[CCode(cheader_filename = "base32.h")]
namespace Base32 {
   [CCode (cname = "base32_encode", array_length = "false", array_null_terminated = "true")]
   public static int encode(
      [CCode(array_length_pos = 0.2, array_length_type = "gsize")] uint8[] data,
      out uint8[] result
   );
}

