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

    // Analyses a ZIP local file
    void ZIP_File::analyse_file(int& current_position, std::shared_ptr<scls::Bytes_Set> datas) {
        // Get the datas about the locale file
        ZIP_Local_File local_file;
        local_file.minimum_version = datas.get()->extract_short(current_position);current_position+=2;
        local_file.general_purpose_flag = datas.get()->extract_short(current_position);current_position+=2;
        local_file.compression_method = datas.get()->extract_short(current_position);current_position+=2;
        local_file.last_modification_time = datas.get()->extract_short(current_position);current_position+=2;
        local_file.last_modification_date = datas.get()->extract_short(current_position);current_position+=2;
        local_file.crc = datas.get()->extract_int(current_position);current_position+=4;
        local_file.compressed_size = datas.get()->extract_int(current_position);current_position+=4;
        local_file.uncompressed_size = datas.get()->extract_int(current_position);current_position+=4;
        int name_length = datas.get()->extract_short(current_position);current_position+=2;
        int field_lenght = datas.get()->extract_short(current_position);current_position+=2;
        local_file.file_name = datas.get()->extract_string(name_length, current_position);current_position+=name_length;
        current_position += field_lenght;

        // Add the file
        a_local_files.push_back(std::make_shared<ZIP_Local_File>(local_file));
    }

    // Extracts a ZIP local file
    void ZIP_File::__extract_zip_file(int& current_position, std::shared_ptr<scls::Bytes_Set> datas, std::string target_path) {
        // Get the datas about the locale file
        analyse_file(current_position, datas);
        ZIP_Local_File& local_file = *a_local_files.at(a_local_files.size() - 1).get();

        // Get the stored datas
        std::shared_ptr<scls::Bytes_Set> compressed_datas = datas.get()->extract_bytes_set_shared_ptr(local_file.compressed_size, current_position);
        current_position += local_file.compressed_size;
        // Decompress the datas
        std::shared_ptr<scls::Bytes_Set> decompressed_datas = compressed_datas;
        if(local_file.compression_method != 0){decompressed_datas = scls::uncompress_from_deflate(compressed_datas.get(), local_file.uncompressed_size);} // TEMPORALY DISABLED
        std::vector<std::string> cutted = scls::cut_string(scls::replace(local_file.file_name, std::string("\\"), std::string("/")), std::string("/"));
        if(target_path.at(target_path.size() - 1) != '/' || target_path.at(target_path.size() - 1) != '\\'){target_path += std::string("/");}std::string current_path = target_path;
        for(int i = 0;i<static_cast<int>(cutted.size() - 1);i++) {
            current_path += cutted.at(i) + std::string("/");
            if(!std::filesystem::exists(current_path)){std::filesystem::create_directory(current_path);}
            if(i == 0){a_root = cutted.at(i);}
        }
        scls::write_in_file_binary(target_path + local_file.file_name, decompressed_datas.get()->datas(), decompressed_datas.get()->datas_size());


        std::cout << local_file.file_name << std::endl;
    }
    // Extracts a ZIP file
    void ZIP_File::extract_zip(std::string target_path){extract_zip(a_path, target_path);}
    void ZIP_File::extract_zip(std::string zip_path, std::string target_path) {
        // Asserts
        if(!std::filesystem::exists(target_path)){scls::print("SCLS File ZIP", std::string("The ZIP file \"") + zip_path + std::string("\" you want to extract to \"") + target_path + std::string("\" can't be extracted : target does not exist."));return;}
        else if(!std::filesystem::is_directory(target_path)){scls::print("SCLS File ZIP", std::string("The ZIP file \"") + zip_path + std::string("\" you want to extract to \"") + target_path + std::string("\" can't be extracted : target is not a directory."));return;}

        // Get the datas
        int current_position = 0;
        std::shared_ptr<scls::Bytes_Set> datas = std::make_shared<scls::Bytes_Set>();
        datas.get()->load_from_file(zip_path);

        while(true) {
            // Check the signature
            int file_signature = datas.get()->extract_int(current_position);current_position+=4;
            if(file_signature != 67324752){scls::print(std::string("SCLS Files ZIP"), std::string("The file \"") + zip_path + std::string("\" does not have the signature of a ZIP file."));break;}

            // Extract a ZIP local file
            __extract_zip_file(current_position, datas, target_path);
        }
    }
}
