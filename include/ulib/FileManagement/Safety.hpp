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
        if (!is_absolute(path)) return std::string((const char*)fs::absolute(path).c_str());
        else return "";
    }

    inline bool has_extension(const std::string& file) {
        return fs::path(file).has_extension();
    }

    inline std::string extension_of(const std::string& file) {
        return std::string((const char*)fs::path(file).extension().c_str());
    }

} }
