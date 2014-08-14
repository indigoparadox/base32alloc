
using Base32;

public class Test {
   public static void main( string[] args ) {
      string foo_string = args[1];
      uint8[] foo_static = foo_string.data;
      unowned uint8[] foo_encoded;
      foo_encoded = Base32.encode( foo_static );
      stdout.printf( "%s\n", (string)foo_encoded );
   }
}

