#pragma once

/*
 This file needs:
 - <experimental/filesystem>
 - <string>
 - <functional>
*/

namespace ulib { namespace File {

    bool exists(const std::string& file, bool ignoreExtension = false);
    bool is_absolute(const std::string& file);
    bool is_relative(const std::string& file);
    std::string to_absolute(const std::string& path);
    bool has_extension(const std::string& file);
    std::string extension_of(const std::string& file);
    std::string name_of(const std::string& path);
    std::string to_portable_path(const std::string& path);
    std::string without_extension(const std::string& path);
    inline bool has_directory(const std::string& file, const std::string& dirPath);

    inline std::string offset_directory(const std::string& file, const std::string& dir)
    {
        std::string absFile = to_absolute(file);
        std::string absDir = to_absolute(dir);

        if (absDir[absDir.size() - 1] == '/' || absDir[absDir.size() - 1] == '\\') absDir.pop_back();

        if (!has_directory(absFile, absDir)) return file;
        
        std::string absDirName = name_of(absDir);
        return absFile.substr(absFile.find(absDirName) + absDirName.size() + 1);
    }

    inline bool is_valid(const std::string& path)
    {
        return path.find_first_not_of("a-to-zA-to-Z0-to-9_.") == std::string::npos;
    }

    inline bool exists(const std::string& path, bool ignoreExtension) {
        if (ignoreExtension) {
            for (const auto & _entry : fs::directory_iterator(path)) {
                if (without_extension(_entry.path().generic_string()) == without_extension(path)) {
                    return true;
                }
            }
            return false;
        } else {
            return fs::exists(path);
        }
    }

    inline bool is_absolute(const std::string& file) {
        return exists(file) && fs::path(file).is_absolute();

    }
    inline bool is_relative(const std::string& file) {
        return exists(file) && fs::path(file).is_relative();
    }

    inline std::string to_absolute(const std::string& path) {
        if (!is_absolute(path)) return fs::absolute(path).generic_string();
        else return path;
    }

    inline bool has_extension(const std::string& file) {
        return fs::path(file).has_extension();
    }

    inline std::string extension_of(const std::string& file) {
        return fs::path(file).extension().generic_string();
    }

    inline std::string directory_of(const std::string& file) {
        return fs::path(file).parent_path().generic_string();
    }

    inline std::string name_of(const std::string& path) {
		return fs::path(path).filename().generic_string();
    }

    inline std::string to_portable_path(const std::string& path) {
        std::string _portable = path;

        for (size_t i = 0; i < _portable.size(); i++) {
            if (_portable[i] == '\\') {
                _portable[i] = '/';
            }
        }

        return _portable;
    }

    inline std::string without_extension(const std::string& path) {
        if (!has_extension(path)) return path;
        else {
            auto _lastindex = path.find_last_of('.');
            return path.substr(0, _lastindex);
        }
    }

	inline bool is_same_path(const std::string& a, const std::string& b) {
		return fs::equivalent(a, b);
	}

	inline bool has_directory(const std::string& file, const std::string& dirPath) {
		std::string _file = to_portable_path(to_absolute(file));
        std::string _dir = to_portable_path(to_absolute(dirPath));

		return _file.find(_dir) != std::string::npos;
	}

	} 

	namespace Directory {

		enum IterationFlags {
			FILES = 1 << 1, DIRECTORIES = 1 << 2, RECURSIVE = 1 << 3
		};

		inline bool exists(const std::string& path) {
			return fs::exists(path);
		}

		inline bool is_directory(const std::string& path) {
			return exists(path) && fs::is_directory(path);
		}

		inline void for_each(const std::string& dir, int flags, std::function<void(std::string)> fn) {
			if (!is_directory(dir)) return;

			if (flags & RECURSIVE) {
				for (auto _item : fs::recursive_directory_iterator(dir)) {
					std::string _path =_item.path().generic_string();

					if ((is_directory(_path) && flags & DIRECTORIES)
						|| (!is_directory(_path) && flags & FILES)) {
						fn(_path);
					}
				}
			} else {
				for (auto _item : fs::directory_iterator(dir)) {
					std::string _path = _item.path().generic_string();

					if ((is_directory(_path) && flags & DIRECTORIES)
						|| (!is_directory(_path) && flags & FILES)) {
						fn(_path);
					}
				}
			}
			
		}

	}

}


