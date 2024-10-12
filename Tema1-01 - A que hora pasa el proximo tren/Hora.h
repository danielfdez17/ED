#include<iostream>
#include"Error.h"
using namespace std;


class Hora {
private:
	int hora, minuto, segundo;
public:
	Hora() {
		hora = minuto = segundo = 0;
	}
	Hora(int h, int m, int s) {
		if (0 <= h && h <= 23 && 0 <= m && m <= 59 && 0 <= s && s <= 59) {
			hora = h; minuto = m; segundo = s;
		}
		else throw Error("ERROR");
	}
	int getHora()const { return hora; }
	int getMinuto()const { return minuto; }
	int getSegundo()const { return segundo; }
	bool operator<(const Hora& h) const {
		if (hora < h.hora) return true;
		if (hora == h.hora) {
			if (minuto < h.minuto) return true;
			if (minuto == h.minuto) {
				if (segundo < h.segundo) return true;
			}
		}
		return false;
	}
	bool operator==(const Hora& h)const {
		return hora == h.getHora() && minuto == h.getMinuto() && segundo == h.getSegundo();
	}
};

ostream& operator<<(ostream& COUT, Hora& hora) {
	COUT << (hora.getHora() < 10 ? "0" : "") << hora.getHora() << ":" <<
		(hora.getMinuto() < 10 ? "0" : "") << hora.getMinuto() << ":" <<
		(hora.getSegundo() < 10 ? "0" : "") << hora.getSegundo();
	return COUT;
}

istream& operator>>(istream& CIN, Hora& hora) {
	int h, m, s;
	char aux;
	CIN >> h >> aux >> m >> aux >> s;
	hora = Hora(h, m, s);
	return CIN;
}