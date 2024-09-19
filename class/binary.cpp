#include <stdint.h>
#include <cmath>
#include <iostream>

int main()
{
    char q = 'y';

    while(q == 'y')
    { 
        uint64_t IPv4 = 4294967296;
        uint32_t subnetMask = 0;
        uint64_t addressSpace = 0;
        std::cout<<"Enter subnet mask: ";
        std::cin>>subnetMask;
        addressSpace = IPv4/(std::pow(2,subnetMask));
        std::cout<<"\n Total Address space: "<<addressSpace;
        std::cout<<"\n Usable Address space: "<<addressSpace-2<<std::endl;
        std::cout<<"\n Continue (y/n): ";
        std::cin>>q;
        std::cout<<"\n";
    }
    return 0;
}