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
#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_
#include <iostream>
#include "Patient.h"
namespace sdds {
	class CovidPatient : public Patient {
	public:
		CovidPatient();
		char type() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
		std::istream& csvRead(std::istream& istr);
	};
}
#endif // !SDDS_COVIDPATIENT_H_
