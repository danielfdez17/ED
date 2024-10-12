//#pragma once
#ifndef Error_H_
#define Error_H_
#include <string>
using namespace std;

class Error {
private:
    string message;

public:
    Error(string m) { message = m; }
    string getMessage() { return message; }
};
#endif // !Error_H_
