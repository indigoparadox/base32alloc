#!/usr/bin/env python

import base64
import sys

print( base64.b32encode( sys.argv[1] ) )

