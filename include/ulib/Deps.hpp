#pragma once

#ifndef ULIB_NO_INCLUDE_ASSERT
    #include <assert.h>
#endif
#ifndef ULIB_NO_INCLUDE_FSTREAM
    #include <fstream>
#endif
#ifndef ULIB_NO_INCLUDE_STRING
    #include <string>
#endif
#ifndef ULIB_NO_INCLUDE_STRING_H
    #include <string.h>
#endif
#ifndef ULIB_NO_INCLUDE_UNORDERED_MAP
    #include <unordered_map>
#endif
#ifndef ULIB_NO_INCLUDE_FILESYSTEM
	#include <filesystem>
#endif
#if defined (_WIN32) && !defined(ULIB_NO_INCLUDE_WINDOWS)
	#include <Windows.h>
#endif

#include <functional>