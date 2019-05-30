
#include <iostream>
#include <stdio.h>
#include "SharedPtr.h"



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
        DataPtr sptr = DataPtr::make({5, 3});
        std::cout << "REF1 COUNT: " << sptr.ref_count() << std::endl;
        printf("REF 1 DATA: ");
        sptr->Print();
        {
            printf("CREATING REF 2\n");
            DataPtr sptr1 = sptr;
            std::cout << "REF1 COUNT: " << sptr.ref_count() << std::endl;
            std::cout << "REF2 COUNT: " << sptr1.ref_count() << std::endl;
            printf("REF 2 DATA: ");
            (*sptr1).Print();
            printf("CHANGING FOO IN REF 2 TO 7\n");
            sptr1->foo = 7;
            printf("REF 2 DATA: ");
            sptr1->Print();
            printf("LEAVING SCOPE FOR REF 2\n");
        }
        std::cout << "REF1 COUNT: " << sptr.ref_count() << std::endl;
        printf("REF 1 DATA: ");
        (*sptr).Print();
    }
    printf("=======================================================\n");

    return 0;
}
