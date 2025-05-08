//******************
//
// scls_files_zip.cpp
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
// This file contains the source code of scls_files_zip.h.
//

// Include the header
#include "../headers/scls_files_zip.h"

// Using of the "scls" namespace to simplify the programmation
namespace scls {
    //*********
    //
    // Mains ZIP classes
    //
    //*********

    // Loads a ZIP file
    void ZIP_File::load_zip(std::string zip_path) {
        // Get the datas
        std::shared_ptr<scls::Bytes_Set> datas = std::make_shared<scls::Bytes_Set>();
        datas.get()->load_from_file(zip_path);

        // Check the signature
        int current_position = 0;
        int file_signature = datas.get()->extract_int(current_position);current_position+=4;
        if(file_signature != 67324752){scls::print(std::string("SCLS Files ZIP"), std::string("The file \"") + zip_path + std::string("\" does not have the signature of a ZIP file."));}

        // Get the datas about the locale file
        int minimum_version = datas.get()->extract_short(current_position);current_position+=2;
        int general_purpose_flag = datas.get()->extract_short(current_position);current_position+=2;
        int compression_method = datas.get()->extract_short(current_position);current_position+=2;
        int last_modification_time = datas.get()->extract_short(current_position);current_position+=2;
        int last_modification_date = datas.get()->extract_short(current_position);current_position+=2;
        int crc = datas.get()->extract_int(current_position);current_position+=4;
        int compressed_size = datas.get()->extract_int(current_position);current_position+=4;
        int uncompressed_size = datas.get()->extract_int(current_position);current_position+=4;
        int name_length = datas.get()->extract_short(current_position);current_position+=2;
        int field_lenght = datas.get()->extract_short(current_position);current_position+=2;
        std::string file_name = datas.get()->extract_string(name_length, current_position);current_position+=name_length;

        std::cout << file_name << std::endl;
    }
}
