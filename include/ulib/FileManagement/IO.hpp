#pragma once

/*
 This file needs:
 - <experimental/filesystem>
 - <string>
 - <fstream>
*/

namespace ulib { namespace File {

    inline bool write(const std::string& file, const std::string& data) {
        std::ofstream _file(file);
        if (_file.is_open()) { _file << data; _file.close(); return true; }
        return false;
    }

    inline bool read(const std::string& file, std::string *out) {
        *out = "";
        std::string _line;
        std::ifstream _file(file, std::ios::in);
        if (_file.is_open()) {
            while (std::getline(_file, _line)) *out += _line + "\n";
            _file.close();
            return true;
        }

        return false;
    }

    inline bool copy(const std::string& src, const std::string& dst) {
	    fs::copy(src, dst);
    }

} }
