#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "IOAble.h"
using namespace std;
namespace sdds {
	IOAble::~IOAble() {

	}
    ostream& operator<<(ostream& ostr, const IOAble& a) {
        a.write(ostr);
        return  ostr;
    }
    istream& operator>>(istream& istr, IOAble& a) {
        a.read(istr);
        return istr;
    }
}