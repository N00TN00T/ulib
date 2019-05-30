
#include <iostream>
#include <stdio.h>
#include "ulib.hpp"

typedef std::string string;

#define BOOL_TO_Y_N(x) (x ? "YES" : "NO")

void print_file_info(const string& filePath, const string& name) {
    std::cout << "TESTING FILE '" << name << "'" << std::endl;
    std::cout << "FILE EXISTS: " << BOOL_TO_Y_N(ulib::File::exists(filePath)) << std::endl;
    if (ulib::File::exists(filePath)) {
        std::cout << "INPUT PATH: '" << filePath << "'" << std::endl;
        std::cout << "IS RELATIVE: " << BOOL_TO_Y_N(ulib::File::is_relative(filePath)) << std::endl;
        std::cout << "IS ABSOLUTE: " << BOOL_TO_Y_N(ulib::File::is_absolute(filePath)) << std::endl;
        if (ulib::File::is_relative(filePath)) {
            std::cout << "TO ABSOLUTE: '" << ulib::File::to_absolute(filePath) << "'" << std::endl;
        }
        std::cout << "HAS EXTENSION: " << BOOL_TO_Y_N(ulib::File::has_extension(filePath)) << std::endl;
        if (ulib::File::has_extension(filePath)) {
            std::cout << "EXTENSION: '" << ulib::File::extension_of(filePath) << "'" << std::endl;
        }
        string _content;
        bool _readSuccess = ulib::File::read(filePath, &_content);
        std::cout << "COULD READ FILE: " << BOOL_TO_Y_N(_readSuccess) << std::endl;
        if (_readSuccess) {
            std::cout << "FILE CONTENT: \n" << _content << std::endl;
        }
        printf("Input new content to write to file:\n > ");
        char _input[420] = "";
        std::cin.getline(_input, 420);
        bool _writeSuccess = ulib::File::write(filePath, _input);
        std::cout << "COULD WRITE FILE: " << BOOL_TO_Y_N(_writeSuccess) << std::endl;
    }
}

int main() {

    printf("====================SharedPtr TEST====================\n");
    {
        struct Data {
            float foo, bar;
            void Print() {
                std::cout << "foo = " << foo << ", bar = " << bar << std::endl;
            }
        };
        typedef ulib::SharedPtr<Data> DataPtr;


        printf("CREATING REF 1\n");
        DataPtr sptr({5, 3});
        std::cout << "REF1 COUNT: " << sptr.GetRefCount() << std::endl;
        printf("REF 1 DATA: ");
        sptr->Print();
        {
            printf("CREATING REF 2\n");
            DataPtr sptr1 = sptr;
            std::cout << "REF1 COUNT: " << sptr.GetRefCount() << std::endl;
            std::cout << "REF2 COUNT: " << sptr1.GetRefCount() << std::endl;
            printf("REF 2 DATA: ");
            (*sptr1).Print();
            printf("CHANGING FOO IN REF 2 TO 7\n");
            sptr1->foo = 7;
            printf("REF 2 DATA: ");
            sptr1->Print();
            printf("LEAVING SCOPE FOR REF 2\n");
        }
        std::cout << "REF1 COUNT: " << sptr.GetRefCount() << std::endl;
        printf("REF 1 DATA: ");
        (*sptr).Print();
    }
    printf("\n====================FileSystem TEST===================\n");
    print_file_info("test_files/data.dat", "data.dat");
    printf("\n");
    print_file_info("/home/charlie/Dev/ulib/test_files/testfile", "testfile");
    printf("\n");
    print_file_info("sadkfhuaskiudf", "non-existent file");

    return 0;
}
