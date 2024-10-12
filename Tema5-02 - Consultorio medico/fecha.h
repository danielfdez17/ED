#include<iostream>
using namespace std;
class fecha {
private:
	int dia, hora, minuto;
public:
	fecha() :dia(0), hora(0), minuto(0) {}
	fecha(int d, int h, int m) :dia(d), hora(h), minuto(m) {}
	int getDia() const { return dia; }
	int getHora() const { return hora; }
	int getMinuto() const { return minuto; }
};
bool operator<(fecha const& f, fecha const&f2) {
	if (f.getDia() < f2.getDia()) return true;
	if (f.getDia() == f2.getDia()) {
		if (f.getHora() < f2.getHora()) return true;
		if (f.getHora() == f2.getHora())
			if (f.getMinuto()< f2.getMinuto()) return true;
	}
	return false;
}
ostream& operator<<(ostream & COUT, fecha const& f) {
	COUT << (f.getHora() < 10 ? "0" : "") << f.getHora() << ":"
		<< (f.getMinuto() < 10 ? "0" : "") << f.getMinuto();
	return COUT;
}