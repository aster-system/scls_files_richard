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
#include "../../scls-foundation-leonhard/scls_foundation.h"

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
        // ZIP_File constructor
        ZIP_File(){};
        // ZIP_File constructor with a path
        ZIP_File(std::string zip_path){load_zip(zip_path);};

        // Loads a ZIP file
        void load_zip(std::string zip_path);
    };
}

#endif // SCLS_FILES_ZIP
