
using Base32;

public class Test {
   public static void main( string[] args ) {
      string foo_string = args[1];
      uint8[] foo_static = foo_string.data;
      unowned uint8[] foo_encoded;
      unowned uint8[] foo_decoded;
      int foo_decoded_len = 0;
      foo_encoded = Base32.encode( foo_static );
      stdout.printf( "%s\n", (string)foo_encoded );
      foo_decoded = Base32.decode( foo_encoded, ref foo_decoded_len );
      stdout.printf( "%s %d\n", (string)foo_decoded, foo_decoded_len );
   }
}

