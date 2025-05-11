//******************
//
// scls_files_zip.h
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
// This file contains the tools to use ZIP file.
//

#ifndef SCLS_FILES_ZIP
#define SCLS_FILES_ZIP

#define SCLS_FILES_ZIP_CENTRAL_FILE_SIGNATURE 33770320
#define SCLS_FILES_ZIP_LOCAL_FILE_SIGNATURE 67324752

// Include the needed librairies
#include "scls_files_compression.h"

// Using of the "scls" namespace to simplify the programmation
namespace scls {
    //*********
    //
    // Mains ZIP classes
    //
    //*********

    class ZIP_File {
        // Class representating a ZIP file and ZIP datas
    public:

        // Local files in a ZIP
        struct ZIP_Local_File {
            // Method of compression of the file
            int compression_method = 0;
            // Size of the file compressed
            int compressed_size = 0;
            // CRC of the file
            int crc = 0;
            // Flag of the file
            int general_purpose_flag = 0;
            // Last modification date / time
            int last_modification_date = 0;
            int last_modification_time = 0;
            // Minimum version to decompress the file
            int minimum_version = 0;
            // Name of the file
            std::string file_name = std::string();
            // Size of the file uncompressed
            int uncompressed_size = 0;
        };

        // ZIP_File constructor
        ZIP_File(){};
        // ZIP_File constructor with a path
        ZIP_File(std::string zip_path):a_path(zip_path){};

        // Analyses a ZIP local file
        void analyse_file(int& current_position, std::shared_ptr<scls::Bytes_Set> datas);
        // Extracts a ZIP local file
        void __extract_zip_file(int& current_position, std::shared_ptr<scls::Bytes_Set> datas, std::string target_path);
        // Extracts a ZIP file
        void extract_zip(std::string zip_path, std::string target_path);
        void extract_zip(std::string target_path);

        // Getters and setters
        inline std::vector<std::shared_ptr<ZIP_Local_File>>& local_files() {return a_local_files;};
        inline std::string root() const {return a_root;};

    private:
        // Local files in the ZIP
        std::vector<std::shared_ptr<ZIP_Local_File>> a_local_files;
        // Path of the ZIP file
        std::string a_path = std::string();
        // Root path of the ZIP
        std::string a_root;
    };
}

#endif // SCLS_FILES_ZIP
