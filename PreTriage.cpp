#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include "PreTriage.h"
using namespace std;
namespace sdds {
	PreTriage::PreTriage(const char* dataFilename) : m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		delete[] m_dataFilename;
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		load();
	}
	PreTriage::~PreTriage()
	{
		ofstream fin;
		fin.open(m_dataFilename);
		if (fin.is_open()){
			fin << m_averCovidWait << ',' << m_averTriageWait << endl;
			cout << "Saving Average Wait Times," << endl << "   COVID Test: " << m_averCovidWait << endl << "   Triage: " << m_averTriageWait << endl << "Saving m_lineup...";
			for (int i = 0; i < m_lineupSize; i++){
				m_lineup[i]->csvWrite(fin) << endl;
			}
			for (int j = 0; j < m_lineupSize; j++)
			{
				cout << '\n' << j + 1 << "- ";
				m_lineup[j]->csvWrite(cout);
			}
			fin.close();
		}
		else{
			cout << "Bad data in file" << endl;
		}
		
		delete[] m_dataFilename;
		cout << '\n' << "done!" << endl;
	}
	const Time PreTriage::getWaitTime(const Patient& p)const
	{
		int a = 0, wait = 0;
		for (int i = 0; i < m_lineupSize; i++)
		{
			if (m_lineup[i]->type() == p.type())
				a++;
		}

		if (p.type() == 'C')
		{
			wait = m_averCovidWait;
			wait *= a;
		}else if (p.type() == 'T')
		{
			wait = m_averTriageWait;
			wait *= a;
		}
		return wait;
	}
	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		int CT = getTime();
		int PTT = p.operator sdds::Time();
		int PTN = p.number();
		if (p.type() == 'C')
		{
			int AWT = m_averCovidWait;
			m_averCovidWait = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
		}
		else if (p.type() == 'T')
		{
			int AWT = m_averTriageWait;
			m_averTriageWait = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
		}
	}
	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}
	int PreTriage::indexOfFirstInLine(char type) const
	{
		int retval = -1;
		int a = 0;
		for (int i = 0; i < m_lineupSize; i++)
		{
			if(a == 0){
				if (m_lineup[i]->type() == type)
				{
					retval = i;
					a = 1;
				}
			}
		}
		return retval;
	}
	void PreTriage::load()
	{
		cout << "Loading data..." << endl;
		string l;
		char del;
		int a = 0;
		ifstream fin;
		fin.open(m_dataFilename);
		if (fin.is_open()){
			getline(fin, l, '\n');
			stringstream ss(l);
			ss >> m_averCovidWait >> del >> m_averTriageWait;
			ss.ignore('\n');
			for (int i = 0; i < maxNoOfPatients; i++){
				Patient* temp = nullptr;
				if (!fin.fail() || !fin.eof()){
					getline(fin, l, ',');
					if (!strcmp(l.c_str(), "C")){
						temp = new CovidPatient();
					}
					else if (!strcmp(l.c_str(), "T")){
						temp = new TriagePatient();
					}
					if (temp != nullptr){
						temp->fileIO(true);
						temp->read(fin);
						temp->fileIO(false);
						m_lineup[i] = temp;
						m_lineupSize++;
					}
				}
				else{
					i = maxNoOfPatients;
				}
			}
			while (getline(fin, l, ',')) {
				a++;
			}
			if (a > 0){
				cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
			}
			if (m_lineupSize > 0) {
				cout << m_lineupSize << " Records imported...\n\n";
			}
			else{
				cout << "No data or bad data file!" << endl << endl;
			}
			fin.close();
		}
		else{
			cout << "Error File Not Loading";
		}
	}
	void PreTriage::reg()
	{
		if (m_lineupSize >= maxNoOfPatients) {
			cout << "Line up full!" << endl;
		}
		else{
			int selection = -1;
			int a = m_lineupSize;
			m_pMenu >> selection;
			if (selection == 1){
				m_lineup[a] = new CovidPatient();
				m_lineup[a]->setArrivalTime();
				cout << "Please enter patient information: " << endl;
				m_lineup[a]->fileIO(false);
				m_lineup[a]->read(cin);
				cout << "\n" << "******************************************" << endl;
				m_lineup[a]->write(cout);
				cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[a]) << endl;
				cout << "******************************************" << endl << endl;
				m_lineupSize++;
			}
			else if (selection == 2){
				m_lineup[a] = new TriagePatient();
				m_lineup[a]->setArrivalTime();
				cout << "Please enter patient information: " << endl;
				m_lineup[a]->fileIO(false);
				m_lineup[a]->read(cin);
				cout << "\n" << "******************************************" << endl;
				m_lineup[a]->write(cout);
				cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[a]) << endl;
				cout << "******************************************" << endl << endl;
				m_lineupSize++;
			}
		}
	}
	void PreTriage::admit()
	{
		int selection = -1, a;
		m_pMenu >> selection;
		if (selection == 1){
			a = indexOfFirstInLine('C');
			if (a != -1){
				cout << '\n' << "******************************************" << '\n';
				m_lineup[a]->fileIO(false);
				cout << "Calling for ";
				m_lineup[a]->write(cout);
				cout << "******************************************" << '\n' << endl;
				setAverageWaitTime(*m_lineup[a]);
				removePatientFromLineup(a);
			}
		}
		else if (selection == 2){
			a = indexOfFirstInLine('T');
			if (a != -1){
				cout << '\n' << "******************************************" << '\n';
				m_lineup[a]->fileIO(false);
				cout << "Calling for ";
				m_lineup[a]->write(cout);
				cout << "******************************************" << '\n' << endl;
				setAverageWaitTime(*m_lineup[a]);
				removePatientFromLineup(a);
			}
		}
	}
	void PreTriage::run(void)
	{
		int selection = -1;
		while (selection != 0){
			m_appMenu >> selection;
			if (selection == 1) {
				reg();
			}
			else if (selection == 2) {
				admit();
			}
		}
	}
}