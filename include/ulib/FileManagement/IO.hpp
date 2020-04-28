#pragma once

//#include "Safety.hpp"

/*
 This file needs:
 - <experimental/filesystem>
 - <string>
 - <fstream>
 - <vector>
*/

#define ULIB_FAIL (1)
#define ULIB_REPLACE (2)

namespace ulib { 
	
	namespace Directory {

		inline bool create(const std::string& path, std::string& failReason = std::string()) {
			std::error_code _err;
			fs::create_directory(path, _err);
			failReason = _err.message();
			return _err.value() == 0;
		}

		inline bool create_all(const std::string& path, std::string& failReason = std::string()) {
			std::error_code _err;
			fs::create_directories(path, _err);
			failReason = _err.message();
			return _err.value() == 0;
		}

		inline bool remove(const std::string& path)
		{
			std::error_code _err;
			fs::remove_all(path, _err);
			return _err.value() == 0;
		}

	}
	
	namespace File {

		std::string directory_of(const std::string& file);

		inline size_t file_size(const std::string& file)
		{
			std::ifstream in(file);
			return in.tellg();
		}


		typedef std::basic_ofstream<unsigned char, std::char_traits<unsigned char>> uofstream;
		typedef std::basic_ifstream<unsigned char, std::char_traits<unsigned char>> uifstream;

    inline bool write(const std::string& file, const std::string& data, bool binary = false) 
	{
		if (!fs::exists(directory_of(file))) Directory::create_all(directory_of(file));
		std::ofstream t;
		if (binary)	t.open(file.c_str(), std::ios::binary);
		else		t.open(file.c_str());
        if (t.is_open()) 
		{ 
			t << data; 
			if (t.bad()) { t.close(); return false; }
			t.close();
			return true; 
		}
		
		t.close();
        return false;
    }

	inline bool write(const std::string& file, const std::vector<unsigned char>& data, bool binary = false)
	{
		if (data.size() == 0) return false;
		if (!fs::exists(directory_of(file))) Directory::create_all(directory_of(file));
		uofstream t;
		if (binary)	t.open(file.c_str(), std::ios::binary);
		else		t.open(file.c_str());
		if (t.is_open())
		{
			t.write(&data[0], data.size());
			if (t.bad()) { t.close(); return false; }
			t.close();
			return true;
		}

		t.close();
		return false;
	}

	

    inline bool read(const std::string& file, std::string *out, bool binary = false) {
        
		std::ifstream t;
		if (binary)	t.open(file.c_str(), std::ios::binary);
		else		t.open(file.c_str());
		if (t.is_open())
		{
			std::string str((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());
			if (t.bad()) { t.close(); return false; }
			*out = str;
			t.close();
			return true;
		}
		else
		{
			return false;
		}
    }
	inline bool read(const std::string& file, std::vector<unsigned char>* out, bool binary = false)
	{

		uifstream t;
		if (binary)	t.open(file.c_str(), std::ios::binary | std::ios::in);
		else		t.open(file.c_str(), std::ios::in);
		if (t.is_open())
		{
			t.seekg(0, t.end);
			auto length = t.tellg();
			t.seekg(0, t.beg);
			out->resize(length);
			if (out->size() == 0) return true;
			t.read(out->data(), out->size());
			if (t.bad()) { t.close(); return false; }
			t.close();
			return true;
		}
		else
		{
			return false;
		}
	}

    inline bool copy(const std::string& src, std::string dst, int dstExistFlags = ULIB_FAIL, std::string& failReason = std::string()) {

		if (!fs::exists(src)) return false;

		if (fs::exists(dst)) {
			if (dstExistFlags & ULIB_FAIL) {
				return false;
			} else if (dstExistFlags & ULIB_REPLACE) {
				fs::remove(dst);
			} else return false;
		}

		Directory::create_all(fs::path(dst).parent_path().generic_string());

		for (int i = 0; i < dst.size(); i++)
		{
			if (dst[i] == '\\') dst[i] = '/';
		}

	    std::error_code _err;
	    fs::copy(src, dst, fs::copy_options::recursive, _err);
		failReason = _err.message();
	    return _err.value() == 0;
    }

    inline bool remove(const std::string& filePath) {
	return fs::remove(filePath);
    }


	

} 

}
