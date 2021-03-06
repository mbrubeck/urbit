/* include/c/portable.h
**
** This file is in the public domain.
*/
  /** Must be compiled on gcc with C99 support.
  **/
#    ifndef __GNUC__
#      error "port me"
#    endif
#    define _GNU_SOURCE


  /** System include files.
  ***
  *** Do not put include files that are only used in the
  *** porting layer here.  Include them directly in the
  *** C file.
  **/
#   if defined(U3_OS_linux)
#     include <stdlib.h>
#     include <string.h>
#     include <stdarg.h>
#     include <unistd.h>
#     include <stdint.h>
#     include <assert.h>
#     include <byteswap.h> 
#     include <setjmp.h>
#     include <stdio.h>

#   elif defined(U3_OS_osx)
#     include <stdlib.h>
#     include <string.h>
#     include <stdarg.h>
#     include <unistd.h>
#     include <stdint.h>
#     include <assert.h>
#     include <setjmp.h>
#     include <machine/endian.h> 
#     include <machine/byte_order.h> 
#     include <stdio.h>

#   endif


  /** Global variable control.
  ***
  *** To instantiate globals, #define u3_c_global as extern.
  **/
#   ifndef u3_c_global
#     define u3_c_global
#   endif


  /** External, OS-independent library dependencies.
  **/
    /* The GMP (GNU arbitrary-precision arithmetic) library.
    ** (Tested with version 4.0.1.)
    */
#      include <gmp.h>


  /** Private C "extensions."
  ***
  *** Except for these and main(), any function, macro, or structure
  *** names must be prefixed either by u3_/U3_ (for public names),
  *** or _ (for static and other file-local names).
  **/
    /* Endianness.
    */
#     define u3_c_endian_little     0
#     define u3_c_endian_big        1

#     ifdef U3_OS_ENDIAN_little
#       define u3_c_endian u3_c_endian_little
#     elif defined(U3_OS_ENDIAN_big)
#       define u3_c_endian u3_c_endian_big
#     else
#       error "port: U3_OS_ENDIAN"
#     endif

    /* Byte swapping.
    */
#      if defined(U3_OS_linux)
#        define u3_c_bswap_16(x)  bswap_16(x)
#        define u3_c_bswap_32(x)  bswap_32(x)
#        define u3_c_bswap_64(x)  bswap_64(x)

#      elif defined(U3_OS_osx)
#        define u3_c_bswap_16(x)  NXSwapShort(x)
#        define u3_c_bswap_32(x)  NXSwapInt(x)
#        define u3_c_bswap_64(x)  NXSwapLongLong(x)
#      endif
