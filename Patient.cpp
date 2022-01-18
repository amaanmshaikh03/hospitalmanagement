#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Patient.h"
#include "utils.h"

using namespace std;
namespace sdds {
    Patient::Patient(int ohipnum, bool ioflag) : t_ticket(ohipnum) {
        p_patientname = nullptr;
        p_ohipnum = 0;
        p_ioflag = ioflag;
    }
    Patient::~Patient(){
        delete[] p_patientname;
        p_patientname = nullptr;
    }
    bool Patient::fileIO() const{
        return p_ioflag;
    }
    void Patient::fileIO(bool ioflag){
        p_ioflag = ioflag;
    }
    bool Patient::operator ==(char c) const{
        bool ok = false;
        if (c == type()) {
            ok = true;
        }
        return ok;
    }
    bool Patient::operator ==(const Patient& currentpatient) const{
        bool ok = false;
        if (type() == currentpatient.type()) {
            ok = true;
        }
        return ok;
    }
    void Patient::setArrivalTime(){
        t_ticket.resetTime();
    }
    Patient::operator Time() const{
        return Time(t_ticket);
    }
    int Patient::number() const{
        return t_ticket.number();
    }
    std::ostream& Patient::csvWrite(std::ostream& os) const {
        os << type() << "," << p_patientname << "," << p_ohipnum << "," ;
        t_ticket.csvWrite(os);
        return os;
    }
    std::istream& Patient::csvRead(std::istream& is) {
        string l;
        getline(is, l, ',');
        delete[] p_patientname;
        p_patientname = new char[l.length() + 1];
        strcpy(p_patientname, l.c_str());
        p_patientname[l.length()] = '\0';
        is >> p_ohipnum;
        is.ignore();
        t_ticket.csvRead(is);
        return is;
    }
    std::ostream& Patient::write(std::ostream& os) const{
        os << t_ticket << '\n';
        for (int i = 0; i < 25 && p_patientname[i]; i++)
        {
            os << p_patientname[i];
        }
        os << ", OHIP: ";
        os << p_ohipnum;
        return os;
    }
    std::istream& Patient::read(std::istream& is){
        cout << "Name: ";
        string l;
        getline(is, l, '\n');
        delete[] p_patientname;
        p_patientname = new char[l.length() + 1];
        strcpy(p_patientname, l.c_str());
        p_patientname[l.length()] = '\0';
        cout << "OHIP: ";
        p_ohipnum = getInt(100000000, 999999999, nullptr, "Invalid OHIP Number, ");
        return is;
    }
}