//******************
//
// scls_files_compression.cpp
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
// This file contains the source code of scls_files_compression.h.
//

// Include the needed librairies
#include "../headers/scls_files_compression.h"

// Using of the "scls" namespace to simplify the programmation
namespace scls {
    //*********
	//
	// Deflate algorithm
	//
	//*********

	// Compress data from a char array without returning the result
    int __compress_with_deflate(char* to_compress, unsigned int to_compress_size, char* output, unsigned int& total_output_size, unsigned int compression_level) {
		SET_BINARY_MODE(stdin);
        SET_BINARY_MODE(stdout);

		// Create compression ENV
		unsigned int buffer_size = 16384.0 / 2.0;
		int deflate_type = Z_FINISH;
		int ret = 0;
		z_stream strm;
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;

		ret = deflateInit(&strm, compression_level); if (ret != Z_OK) return ret;
		strm.avail_in = to_compress_size;
		strm.next_in = (Bytef*)(to_compress);

		// Set output
        strm.avail_out = buffer_size; strm.next_out = (Bytef*)output;

		// Compress data
		do
		{
		    // Set output
			strm.avail_out = buffer_size;

			// Do the decompression
			ret = deflate(&strm, deflate_type);
			if (ret == Z_STREAM_ERROR)
			{
				(void)deflateEnd(&strm);
				return -1;
			}

			switch (ret)
			{
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;
				break;
			case Z_MEM_ERROR:
				(void)deflateEnd(&strm);
				return -2;
			case Z_BUF_ERROR:
				(void)deflateEnd(&strm);
				return -5;
			case Z_STREAM_END:
				break;
			}
		} while (strm.avail_out == 0);
		(void)deflateEnd(&strm);

		total_output_size = strm.total_out;

		return 1;
	}

	// Compress data from a char array and return the result
    char* compress_with_deflate(char* to_compress, unsigned int to_compress_size, unsigned int& output_size, unsigned int compression_level) {
		char* output = new char[to_compress_size * 2];

		unsigned int ret = __compress_with_deflate(to_compress, to_compress_size, output, output_size, compression_level);
		if (ret != 1) return 0;

		char* final_array = new char[output_size];
		for (unsigned int i = 0; i < output_size; i++) final_array[i] = output[i];

		delete[] output;

		return final_array;
	}
    std::shared_ptr<Bytes_Set> compress_with_deflate(Bytes_Set* to_compress, unsigned int compression_level) {
        char* output = new char[to_compress->datas_size() * 2];unsigned int output_size = 0;
		unsigned int ret = __compress_with_deflate(to_compress->datas(), to_compress->datas_size(), output, output_size, compression_level);
		if (ret != 1){return std::shared_ptr<Bytes_Set>();}

		// Copy the datas
		std::shared_ptr<Bytes_Set> to_return = std::make_shared<Bytes_Set>(output_size);
		for (unsigned int i = 0; i < output_size; i++){to_return.get()->set_data_at_directly(i, output[i]);}
		delete[] output;
		return to_return;
    }

	// Uncompress data from a char array
    int uncompress_from_deflate(char* to_uncompress, unsigned int to_uncompress_size, char* output, unsigned int output_size) {
		// Create compression ENV
		int ret = 0;
		z_stream strm;
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = 0;
		strm.next_in = Z_NULL;
		ret = inflateInit2(&strm, 0);std::cout << "A " << ret << std::endl;
		if (ret != Z_OK){return ret;}
		strm.avail_in = to_uncompress_size;
		strm.next_in = (Bytef*)(to_uncompress);
		bool stream_end = false;

		// Uncompress data
		do {
			// Set output
			strm.avail_out = output_size;
			strm.next_out = (Bytef*)output;

			// Do the decompression
			ret = inflate(&strm, Z_NO_FLUSH);
			if (ret == Z_STREAM_ERROR) {(void)inflateEnd(&strm);return -1;}

			switch (ret) {
			case Z_NEED_DICT:ret = Z_DATA_ERROR;break;
			case Z_MEM_ERROR:(void)inflateEnd(&strm);return -2;
			case Z_STREAM_END:stream_end = true;break;
			case Z_DATA_ERROR:break;
			}
		}
		while (strm.avail_out == 0 && !stream_end);
		(void)inflateEnd(&strm);

		return 1;
	}
    std::shared_ptr<Bytes_Set> uncompress_from_deflate(Bytes_Set* to_compress, unsigned int output_size) {
        std::shared_ptr<Bytes_Set> to_return = std::make_shared<Bytes_Set>(output_size);
        int result = uncompress_from_deflate(to_compress->datas(), to_compress->datas_size(), to_return.get()->datas(), output_size);
        if(result < 0 && false){return std::shared_ptr<Bytes_Set>();}return to_return;
    }
}
