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
2020/04/06  Preliminary release
2020/04/06  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
#include <iostream>
#include "Patient.h"
namespace sdds {
	class TriagePatient : public Patient {
		char* symptoms;
	public:
		TriagePatient();
		~TriagePatient();
		char type() const;
		std::istream& read(std::istream& istr);
		std::ostream& csvWrite(std::ostream& istr) const;
		std::ostream& write(std::ostream& ostr) const;
		std::istream& csvRead(std::istream& istr);
	};
}
#endif // !SDDS_TRIAGEPATIENT_H

