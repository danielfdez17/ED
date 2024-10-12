//#pragma once
#ifndef Horas_H_
#define Horas_H_
#include "Error.h"

class horas {
private:
    int hours, minutes, seconds;
public:
    horas(int hours, int minutes, int seconds);
    horas();
    bool operator<(const horas& h) const;
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    bool esPar() const;
    //istream& operator>>(istream& CIN);
    //ostream& operator<<(ostream& COUT);
};

horas::horas(int hours, int minutes, int seconds) {
    if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59) {
        this->hours = hours;
        this->minutes = minutes;
        this->seconds = seconds;
    }
    else {
        throw Error("ERROR");
    }
}

horas::horas() {
    this->hours = 0;
    this->minutes = 0;
    this->seconds = 0;
}

bool horas::operator<(const horas& h) const {
    if (this->hours < h.hours) { return true; }
    else if (this->hours == h.hours) {
        if (this->minutes < h.minutes) { return true; }
        else if (this->minutes == h.minutes) {
            if (this->seconds < h.seconds) { return true; }
        }
    }
    return false;
}

int horas::getHours() const { return this->hours; }

int horas::getMinutes() const { return this->minutes; }

int horas::getSeconds() const { return this->seconds; }

bool horas::esPar() const {
    return (hours % 2 == 0) && (minutes % 2 == 0) && (seconds % 2 == 0);
}

//istream& operator>>(istream& CIN, horas&h) {
//    int hours, minutes, seconds;
//    char aux;
//    CIN >> hours >> aux >> minutes >> aux >> seconds;
//    h = horas(hours, minutes, seconds);
//    return CIN;
//}
//
//ostream& operator<<(ostream& COUT, horas&h) {
//    if (h.getHours() < 10) {
//        COUT << "0";
//    }
//    COUT << h.getHours() << ":";
//    if (h.getMinutes() < 10) {
//        COUT << "0";
//    }
//    COUT << h.getMinutes() << ":";
//    if (h.getSeconds() < 10) {
//        COUT << "0";
//    }
//    COUT << h.getSeconds();
//    return COUT;
//}

//istream& horas::operator>>(istream& CIN) {
//    int hours, minutes, seconds;
//    char aux;
//    CIN >> hours >> aux >> minutes >> aux >> seconds;
//    h = horas(hours, minutes, seconds);
//    return CIN;
//}
//
//ostream& horas::operator<<(ostream& COUT) {
//    if (h.getHours() < 10) {
//        COUT << "0";
//    }
//    COUT << h.getHours() << ":";
//    if (h.getMinutes() < 10) {
//        COUT << "0";
//    }
//    COUT << h.getMinutes() << ":";
//    if (h.getSeconds() < 10) {
//        COUT << "0";
//    }
//    COUT << h.getSeconds();
//    return COUT;
//}
#endif // !Horas_H_
