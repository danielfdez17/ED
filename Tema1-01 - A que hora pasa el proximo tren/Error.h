#include <iostream>
using namespace std;
class Error {
private:
	string msg;
public:
	Error(string m) { msg = m; }
	string getMsg() const { return msg; }
};