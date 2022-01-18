#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
    bool debug = false;  // made global in utils.h
    int getTime() {
        int mins = -1;
        if (debug) {
            Time t(0);
            cout << "Enter current time: ";
            do {
                cin.clear();
                cin >> t;   // needs extraction operator overloaded for Time
                if (!cin) {
                    cout << "Invlid time, try agian (HH:MM): ";
                    cin.clear();
                }
                else {
                    mins = int(t);
                }
                cin.ignore(1000, '\n');
            } while (mins < 0);
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }
        return mins;
    }
    int getInt(const char* prompt) {
        istream& istr = cin;
        string input;
        int repeat = 0;
        if (prompt != nullptr) {
            cout << prompt;
        }
        while (repeat == 0) {
            cin.clear();
            getline(istr, input, '\n');
            if (isdigit(input[0]) == 0 && input[0] != '-')
            {
                cout << "Bad integer value, try again: ";
            }
            else {
                for (unsigned int i = 0; i < input.length(); i++)
                {
                    if (isdigit(input[i]) == 0 && input[0] != '-')
                    {
                        cout << "Enter only an integer, try again: ";
                        i = input.length();
                        repeat = 0;
                    }
                    else {
                        repeat = 1;
                    }
                }
            }

        }
        return stoi(input);
    }
    int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError) {
        int a = getInt(prompt);
        while (a < min || a > max) {
            if (errorMessage != nullptr) {
                cout << errorMessage;
            }
            if (showRangeAtError == true) {
                cout << "[" << min << " <= value <= " << max << "]: ";
            }
            a = getInt();
        }
        return a;
    }
    char* getcstr(const char* prompt, std::istream& istr, char delimiter) {
        char* val = nullptr;
        string str;
        if (prompt != nullptr) {
            cout << prompt;
            getline(istr, str, delimiter);
            val = new char[str.length() + 1];
            strcpy(val, str.c_str());
        }
        return val;
    }

}