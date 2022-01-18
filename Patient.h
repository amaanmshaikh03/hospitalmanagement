#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
namespace sdds {
    class Patient : public IOAble {
        char* p_patientname;
        int p_ohipnum;
        Ticket t_ticket;
        bool p_ioflag;
    public:
        Patient(int ohipnum = 0, bool ioflag = false);
        ~Patient();
        Patient(const Patient&) = delete;
        void operator=(const Patient&) = delete;
        virtual char type() const = 0;
        bool fileIO() const;
        void fileIO(bool);
        bool operator ==(char) const;
        bool operator ==(const Patient&) const;
        void setArrivalTime();
        operator Time() const;
        int number() const;
        std::istream& read(std::istream& istr);
        std::ostream& write(std::ostream& ostr) const;
        std::istream& csvRead(std::istream& istr);
        std::ostream& csvWrite(std::ostream& ostr) const;
    };
}
#endif 