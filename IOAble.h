#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H
#include <iostream>
#include "utils.h"
using namespace std;
namespace sdds {
    class IOAble {
        
    public:
        virtual ostream& csvWrite(ostream& ostr)const = 0;
        virtual istream& csvRead(istream& istr) = 0;
        virtual ostream& write(ostream& ostr)const = 0;
        virtual istream& read(istream& istr) = 0;
        virtual ~IOAble();
    };
    ostream& operator<<(ostream& ostr, const IOAble& D);
    istream& operator>>(istream& istr, IOAble& D);
}
#endif