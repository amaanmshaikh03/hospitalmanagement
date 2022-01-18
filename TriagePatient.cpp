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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include "TriagePatient.h"
using namespace std;
namespace sdds {
	int nextTriageTicket = 1;
	TriagePatient::TriagePatient() : Patient(nextTriageTicket){
		symptoms = nullptr;
		nextTriageTicket++;
	}
	TriagePatient::~TriagePatient() {
		delete[] symptoms;
	}
	char TriagePatient::type() const {
		return 'T';
	}
	std::istream& TriagePatient::read(std::istream& istr) {
		if (fileIO() == true) {
			csvRead(istr);
		}
		else {
			delete[] symptoms;
			Patient::read(istr);
			cout << "Symptoms: ";
			string l;
			getline(istr, l, '\n');
			symptoms = new char[strlen(l.c_str()) + 1];
			strcpy(symptoms, l.c_str());
		}
		return istr;
	}
	std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const{
		Patient::csvWrite(ostr);
		ostr << ",";
		ostr << symptoms;
		return ostr;
	}
	std::ostream& TriagePatient::write(std::ostream& ostr) const {
		if (fileIO() == true) {
			csvWrite(ostr);
		}else{
			ostr << "TRIAGE" << endl;
			Patient::write(ostr);
			ostr << endl;
			ostr << "Symptoms: " << symptoms << endl;
		}
		return ostr;
	}
	std::istream& TriagePatient::csvRead(std::istream& istr) {
		char d;
		delete[] symptoms;
		Patient::csvRead(istr);
		istr >> d;
		string l;
		getline(istr, l, '\n');
		symptoms = new char[strlen(l.c_str()) + 1];
		strcpy(symptoms, l.c_str());
		nextTriageTicket = number() + 1;
		return istr;
	}
}