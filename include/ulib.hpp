#pragma once

#ifndef ULIB_NO_INCLUDE
    #ifndef ULIB_NO_INCLUDE_ASSERT
        #include <assert.h>
    #endif
    #ifndef ULIB_NO_INCLUDE_FSTREAM
        #include <fstream>
    #endif
    #ifndef ULIB_NO_INCLUDE_STRING
        #include <string>
    #endif
    #ifndef ULIB_NO_INCLUDE_UNORDERED_MAP
        #include <unordered_map>
    #endif
    #ifndef ULIB_NO_INCLUDE_FILESYSTEM
        #include <experimental/filesystem>
    #endif
#endif

namespace fs = ::std::experimental::filesystem::v1;

#include "ulib/Pointers.hpp"
#include "ulib/FileSystem.hpp"
