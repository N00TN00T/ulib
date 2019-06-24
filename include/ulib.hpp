#pragma once

#ifndef ULIB_NO_INCLUDE
    #include "ulib/Deps.hpp"
#endif

#ifdef _WIN32
namespace fs = ::std::experimental::filesystem;
#else
namespace fs = ::std::experimental::filesystem::v1;
#endif

#include "ulib/Pointers.hpp"
#include "ulib/FileSystem.hpp"
#include "ulib/Containers.hpp"
#include "ulib/Utility.hpp"
