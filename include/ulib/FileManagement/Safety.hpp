#pragma once

/*
 This file needs:
 - <experimental/filesystem>
 - <string>
*/

namespace ulib { namespace File {

    bool exists(const std::string& file);
    bool is_absolute(const std::string& file);
    bool is_relative(const std::string& file);
    std::string to_absolute(const std::string& path);
    bool has_extension(const std::string& file);
    std::string extension_of(const std::string& file);

    inline bool exists(const std::string& file) {
        return fs::exists(file);
    }

    inline bool is_absolute(const std::string& file) {
        return exists(file) && fs::path(file).is_absolute();
		
    }
    inline bool is_relative(const std::string& file) {
        return exists(file) && fs::path(file).is_relative();
    }

    inline std::string to_absolute(const std::string& path) {
#ifdef _WIN32
		int _len;
		int _slength = (int)path.length() + 1;
		_len = MultiByteToWideChar(CP_ACP, 0, path.c_str(), _slength, 0, 0);
		wchar_t* _windowsCancerBuf = new wchar_t[_len];
		MultiByteToWideChar(CP_ACP, 0, path.c_str(), _slength, _windowsCancerBuf, _len);
		std::wstring _windowsCancerPathString(_windowsCancerBuf);
		delete[] _windowsCancerBuf;
		
		wchar_t _windowsCancerRawRetVal[4096] = TEXT("");

		GetFullPathNameW (
			_windowsCancerPathString.c_str(),
			4096,
			_windowsCancerRawRetVal,
			{NULL}
		);
		
		std::wstring _windowsCancerRetVal = _windowsCancerRawRetVal;

		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &_windowsCancerRetVal[0], (int)_windowsCancerRetVal.size(), NULL, 0, NULL, NULL);
		std::string _retVal(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &_windowsCancerRetVal[0], (int)_windowsCancerRetVal.size(), &_retVal[0], size_needed, NULL, NULL);

		return _retVal;
#else
        if (!is_absolute(path)) return std::string((const char*)fs::absolute(path).c_str());
        else return path;
#endif
    }

    inline bool has_extension(const std::string& file) {
        return fs::path(file).has_extension();
    }

    inline std::string extension_of(const std::string& file) {
#ifdef _WIN32
		std::string _extension;
		bool _foundDot = false;
		for (int i = file.size() - 1; i >= 0; i--) {
			const auto& _char = file[i];

			if (_char == '/' || _char == '\\') break;

			_extension.insert(_extension.begin(), _char);

			if (_char == '.') { _foundDot = true; break; }
		}

		if (_foundDot)	return _extension;
		else			return "";
#else
        return std::string((const char*)fs::path(file).extension().c_str());
#endif
    }

    inline std::string directory_of(const std::string& file) {
        return std::string((const char*)fs::path(file).parent_path().c_str());
    }

} }
