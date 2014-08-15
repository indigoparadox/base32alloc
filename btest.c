
#include <stdio.h>
#include <bstrlib.h>

#include "base32alloc.h"

int main( int argc, char* argv[] ) {
   bstring buffer_out;
	bstring buffer_in = bfromcstr( argv[1] );

   buffer_out = base32_encode_bstr( buffer_in );

	printf( "%s\n", bdata( buffer_out ) );

   bdestroy( buffer_out );
   bdestroy( buffer_in );
}

