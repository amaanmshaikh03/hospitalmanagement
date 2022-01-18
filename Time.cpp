/* Citation and Sources...
Final Project Milestone 1
Module: utils
Filename: utils.h
Version 1.0
Author	Mohammedamaan Iqbal Shaikh
Revision History
Student Id: 157304197
mail: mishaikh3@myseneca.ca
-----------------------------------------------------------
Date      Reason
2020/03/16  Preliminary release
2020/03/16  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {
    Time& Time::setToNow() {
        m_min = getTime();
        return *this;
    }
    Time::Time(unsigned int min) {
        m_min = min;
    }
    ostream& Time::write(std::ostream& ostr) const {
        int hour, min;
        min = m_min % 60;
        hour = m_min / 60;
        if (hour < 10) {
            if (min < 10) {
                ostr << "0" << hour << ":" << "0" << min;
            }
            else {
                ostr << "0" << hour << ":" << min;
            }
        }
        else if (min < 10) {
            if (hour < 10) {
                ostr << "0" << hour << ":" << "0" << min;
            }
            else {
                ostr << hour << ":" << "0" << min;
            }
        }
        else {
            ostr << hour << ":" << min;
        }
        return ostr;
    }
    istream& Time::read(std::istream& istr) {
        int hour = 0, min = 0;
        char del = ' ';
        bool fail = false;
        istr >> hour;
        istr >> del;
        istr >> min;
        if (del != ':' || hour < 0 || min < 0) {
            fail = true;
        }
        else {
            m_min = min + (hour * 60);
        }
        if (fail == true) {
            istr.setstate(ios::failbit);
        }
        return istr;
    }
    Time& Time::operator-= (const Time& D) {
        while (m_min < D.m_min) {
            m_min += 1440;
        }
        m_min -= D.m_min;
        return *this;
    }
    Time Time::operator-(const Time& D)const {
        Time a;
        unsigned int b = m_min;
        while (b < D.m_min) {
            b += 1440;
        }
        a.m_min = b - D.m_min;
        return a;
    }
    Time& Time::operator+=(const Time& D) {
        m_min += D.m_min;
        return *this;
    }
    Time Time::operator+(const Time& D)const {
        Time a;
        a = m_min + D.m_min;
        return a;
    }
    Time& Time::operator=(unsigned int val) {
        m_min = val;
        return *this;
    }
    Time& Time::operator *= (unsigned int val) {
        m_min *= val;
        return *this;
    }
    Time Time::operator *(unsigned int val)const {
        Time a;
        a.m_min = m_min * val;
        return a;
    }
    Time& Time::operator /= (unsigned int val) {
        m_min /= val;
        return *this;
    }
    Time Time::operator /(unsigned int val)const {
        Time a;
        a.m_min = m_min / val;
        return a;
    }
    Time::operator int()const {
        return (int)m_min;
    }
    Time::operator unsigned int()const {
        return (unsigned int)m_min;
    }
    ostream& operator<<(ostream& ostr, const Time& a) {
        a.write(ostr);
        return ostr;
    }
    istream& operator>>(istream& istr, Time& a) {
        a.read(istr);
        return istr;
    }
}
