//******************
//
// scls_files_compression.h
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Files "Richard" is made to easily handle a lot of formats of datas with SCLS.
// It is named after the founder of the GNU OS, Richard Stallman.
//
// This file contains some tools to compress datas.
//

#ifndef SCLS_FILES_COMPRESSION
#define SCLS_FILES_COMPRESSION

// Avoid some errors with libraries path
// ZLib
#ifndef SCLS_ZLIB_PATH
#define SCLS_ZLIB_PATH <zlib/zlib.h>
#endif // SCLS_ZLIB_PATH

// Include ZLib
#include SCLS_ZLIB_PATH

// ZLib mandatory stuff
#if defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) (void)_setmode(_fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

// Include the needed librairies
#include "../../scls-foundation-leonhard/scls_foundation.h"

// Using of the "scls" namespace to simplify the programmation
namespace scls {
    //*********
	//
	// Deflate algorithm
	//
	//*********

	// Compress data from a char array with / without returning the result
    char* compress_with_deflate(char* to_compress, unsigned int to_compress_size, unsigned int& output_size, unsigned int compression_level = 9);
    std::shared_ptr<Bytes_Set> compress_with_deflate(Bytes_Set* to_compress, unsigned int& output_size, unsigned int compression_level);

	// Uncompress data from a char array
    int uncompress_from_deflate(char* to_uncompress, unsigned int to_uncompress_size, char* output, unsigned int output_size);
    std::shared_ptr<Bytes_Set> uncompress_from_deflate(Bytes_Set* to_compress, unsigned int output_size);
}

#endif // SCLS_FILES_COMPRESSION
