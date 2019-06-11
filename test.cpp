
#include <iostream>
#include <stdio.h>

#include <cstdio>
#include <ctime>

#include "ulib.hpp"

typedef std::string string;

#define BOOL_TO_Y_N(x) (x ? "YES" : "NO")

string dec_to_hex(int dec) {
    std::stringstream ss;
    ss<< std::hex << dec; // int decimal_value
    std::string res ( ss.str() );

    return res;
}

int hex_to_dec(string hex) {
    std::stringstream ss;
    ss  << hex ; // std::string hex_value
    int dec = 0;
    ss >> std::hex >> dec ; //int decimal_value

    return dec;
}

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
    printf("======================UniquePtr TEST====================\n");
    {
        struct Data {
            float foo, bar;
            void Print() {
                std::cout << "foo = " << foo << ", bar = " << bar << std::endl;
            }
        };
        typedef ulib::UniquePtr<Data> DataPtr;


        printf("CREATING REF 1\n");
        DataPtr sptr({5, 3});
        std::cout << "REF 1 IS OWNER?: " << BOOL_TO_Y_N(sptr.IsOwner()) << std::endl;
        printf("REF 1 DATA: ");
        sptr->Print();
        {
            DataPtr sptr1;
            printf("CREATING REF 2\n");
            sptr1 = sptr;
            std::cout << "REF 1 IS OWNER?: " << BOOL_TO_Y_N(sptr.IsOwner()) << std::endl;
            std::cout << "REF 2 IS OWNER?: " << BOOL_TO_Y_N(sptr1.IsOwner()) << std::endl;
            printf("REF 2 DATA: ");
            (*sptr1).Print();
            printf("CHANGING FOO IN REF 2 TO 7\n");
            sptr1->foo = 7;
            printf("REF 2 DATA: ");
            sptr1->Print();
            printf("LEAVING SCOPE FOR REF 2\n");
        }
        std::cout << "REF 1 IS OWNER?: " << BOOL_TO_Y_N(sptr.IsOwner()) << std::endl;
        printf("REF 1 DATA: ");
        (*sptr).Print();
    }
    printf("\n====================Bitset TEST===================\n");
    ulib::Bitset _bitset;
    std::cout << "Setting bit 5" << std::endl;
    _bitset.SetBit(5);
    std::cout << "Is bit 5 set? " << BOOL_TO_Y_N(_bitset.GetBit(5)) << std::endl;

    std::cout << "Setting bit 67" << std::endl;
    _bitset.SetBit(67);
    std::cout << "Is bit 67 set? " << BOOL_TO_Y_N(_bitset.GetBit(67)) << std::endl;
    std::cout << "Is bit 3 set? " << BOOL_TO_Y_N(_bitset.GetBit(3)) << std::endl;
    std::cout << "Is bit 1025 set? " << BOOL_TO_Y_N(_bitset.GetBit(1025)) << std::endl;

    printf("\n====================FileSystem TEST===================\n");
    print_file_info("test_files/data.dat", "data.dat");
    printf("\n");
    print_file_info("/home/charlie/Dev/ulib/test_files/testfile", "testfile");
    printf("\n");
    print_file_info("sadkfhuaskiudf", "non-existent file");
    printf("\n");
    printf("\n=====================Array TEST=======================\n");
    struct Doggy {
        std::string name = "Stray puppy";
        int age = 0;
        void Print() {
            std::cout << "Doggy '" << name << "' is " << age << " years old" << std::endl;
        }
    };
    printf("Creating array of 5 doggies\n");
    ulib::Array<Doggy*> _doggies(5);
    _doggies[0] = new Doggy { "Jacky", 3 };
    _doggies[1] = new Doggy { "Snuffy", 12 };
    _doggies[2] = new Doggy { "Ivy", 8 };
    _doggies[3] = new Doggy { "Lennart", 1 };
	_doggies[4] = new Doggy();
    std::cout << "Actual length: " << _doggies.GetLength() << std::endl;
    printf("Doggies:\n");
    for (uint64_t i = 0; i < _doggies.GetLength(); i++) {
        _doggies[i]->Print();
    }
    printf("\nAfter naming stray puppy to 'Lyra':\n");
    _doggies[4]->name = "Lyra";
    for (uint64_t i = 0; i < _doggies.GetLength(); i++) {
        _doggies[i]->Print();
    }
    printf("\nFinding 2 more puppies...:\n");
    _doggies.Resize(_doggies.GetLength() + 2);
	_doggies[5] = new Doggy();
	_doggies[6] = new Doggy();
    for (uint64_t i = 0; i < _doggies.GetLength(); i++) {
        _doggies[i]->Print();
    }
    printf("\nDeleting 1 puppy :(...\n");
    _doggies.Resize(_doggies.GetLength() - 1);
    for (uint64_t i = 0; i < _doggies.GetLength(); i++) {
        _doggies[i]->Print();
    }
    printf("\n=====================Queue TEST=======================\n");
    struct Order {
        std::string customer = "Johnny";
        std::string name = "Pasta Carbonara";
        double cost = 1.2;

        void Print() {
            std::cout << "Customer '" << customer << "' wants '" << name << "' for $" << cost << std::endl;
        }
    };
    printf("Creating a queue of orders...\n");
    ulib::Queue<Order*> _orders;
    std::cout << "Is queue empty?: " << (_orders.IsEmpty() ? "YES" : "NO") << std::endl;
    printf("Placing 3 orders...\n");
    _orders.Push(new Order());
    _orders.Push(new Order { "Alisha", "Scrambled Eggs", 0.9 });
    _orders.Push(new Order { "Troy", "Baked potato", 1.7 });
    std::cout << "Is queue empty?: " << (_orders.IsEmpty() ? "YES" : "NO") << std::endl;
    printf("Front order: \n");
    _orders.GetTop()->Print();
    printf("\nProcessing orders...\n");
    while (!_orders.IsEmpty()) {
        auto _order = _orders.Pop();
        printf("PROCESSING: "); _order->Print();
        std::cout << "Customer '" << _order->customer << "' was served" << std::endl;
    }



    return 0;
}
