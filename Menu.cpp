#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
using namespace std;
namespace sdds {
	Menu::Menu(){
		m_text = nullptr;
		m_noOfSel = 0;
	}
	Menu::Menu(const char* MenuContent, int NoOfSelections) {
		m_text = new char[strlen(MenuContent) + 1];
		strcpy(m_text, MenuContent);
		m_noOfSel = NoOfSelections;
	}
	Menu::~Menu() {
		delete[] m_text;
	}
	Menu::Menu(const Menu& m) {
		m_noOfSel = m.m_noOfSel;
		if (m.m_text != nullptr) {
			m_text = new char[strlen(m.m_text) + 1];
			strcpy(m_text, m.m_text);
		}
		else {
			m_text = nullptr;
		}
	}
	Menu& Menu::operator=(const Menu& m) {
		m_noOfSel = m.m_noOfSel;
		delete[] m_text;
		if (m.m_text != nullptr) {
			m_text = new char[strlen(m.m_text) + 1];
			strcpy(m_text, m.m_text);
		}
		else {
			m_text = nullptr;
		}
		return *this;
	}
	void Menu::display()const{
		cout << m_text << endl;
		cout << "0- Exit" << endl;
		cout << "> ";
	}
	int& Menu::operator>>(int& Selection) {
		display();
		Selection = getInt(0, m_noOfSel);
		return Selection;
	}
}