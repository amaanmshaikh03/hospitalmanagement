/* Citation and Sources...
Final Project Milestone 1
Module: utils
Filename: utils.h
Version 1.0
Author	Mohammedamaan Iqbal Shaikh
Revision History
-----------------------------------------------------------
Date      Reason
2020/03/16  Preliminary release
2020/03/16  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_
#include <iostream>
#include <cstring>
#include <string>
namespace sdds {
    extern bool debug; // making sdds::debug variable global to all the files
                       // which include: "utils.h"
    int getInt(const char* prompt = nullptr);
    int getInt(int min, int max, const char* prompt = nullptr, const char* errorMessage = nullptr, bool showRangeAtError = true);
    char* getcstr(const char* prompt = nullptr, std::istream& istr = std::cin, char delimiter = '\n');
    int getTime(); // returns the time of day in minutes
    template <typename type>
    void removeDynamicElement(type* array[], int index, int& size) {
        delete array[index];
        for (int j = index; j < size; j++) {
            array[j] = array[j + 1];
        }
        size--;
    }
}
#endif // !SDDS_UTILS_H_