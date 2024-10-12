#include<iostream>
#include<vector>
#include<unordered_map>
#include<list>
#include<string>
using namespace std;

enum class Direccion {Norte, Sur, Este, Oeste};

istream& operator>>(istream& in, Direccion& dir) {
	string s; 
	in >> s;
	if (s == "Norte") dir = Direccion::Norte;
	else if (s == "Sur") dir = Direccion::Sur;
	else if (s == "Este") dir = Direccion::Este;
	else if (s == "Oeste") dir = Direccion::Oeste;
	return in;
}

class Desierto {
private:
	unordered_map<string, pair<int, int>>torres;
	unordered_map<pair<int, int>, string>coordenadas;

public:
	void anyadir_torre(const string& nombre, int x, int y) {
		unordered_map<string, pair<int, int>>::iterator itTorres = torres.find(nombre);
		if (itTorres != torres.end()) throw domain_error("Torre ya existente");
		unordered_map<pair<int, int>, string>::iterator itCoordenadas = coordenadas.find(pair<int,int>(x,y));
		if (itCoordenadas != coordenadas.end()) throw domain_error("Posicion ocupada");
		torres.insert({ nombre,{x,y} });
		coordenadas.insert({ {x,y},nombre });
	}
	void eliminar_torre(const string& nombre) {
		unordered_map<string, pair<int, int>>::iterator itTorres = torres.find(nombre);
		if (itTorres == torres.end()) throw domain_error("Torre no existente");
		coordenadas.erase(coordenadas.find( pair<int,int>(itTorres->second.first, itTorres->second.second)));
		//coordenadas.erase({ itTorres->second.first,itTorres->second.second });
		torres.emplace(itTorres);
	}
	pair<int, int>posicion(const string& nombre) const {
		unordered_map<string, pair<int, int>>::const_iterator itTorres = torres.find(nombre);
		if (itTorres == torres.end()) throw domain_error("Torre no existente");
		return { itTorres->second.first,itTorres->second.second };
	}
	pair<bool, string>torre_en_posicion(int x, int y) const {
		unordered_map<pair<int, int>, string>::const_iterator itCoordenadas = coordenadas.find(pair<int,int>(x, y));
		if (itCoordenadas == coordenadas.end()) return { false,"" };
		return { true, itCoordenadas->second };
	}
	string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
		unordered_map<string, pair<int, int>>::const_iterator itTorres = torres.find(nombre);
		if (itTorres == torres.end()) throw domain_error("Torre no existente");
		bool found = false; string s;
		unordered_map<pair<int, int>, string>::const_iterator itCoordenadas = coordenadas.cbegin();
		while (itCoordenadas != coordenadas.cend() && !found) {
			pair<int, int>origen = { itTorres->second.first,itTorres->second.second }, 
				destino = { itCoordenadas->first.first,itCoordenadas->first.second };
			switch (dir) {
			case Direccion::Norte:
				found = (origen.first == destino.first && destino.second > origen.second);
				break;
			case Direccion::Sur:
				found = (origen.first == destino.first && destino.second < origen.second);
				break;
			case Direccion::Este:
				found = (origen.second == destino.second && destino.first > origen.first);
				break;
			case Direccion::Oeste:
				found = (origen.second == destino.second && destino.first < origen.first);
				break;
			default:
				break;
			}
			if (found) s = itCoordenadas->second;
			itCoordenadas++;
		}
		if (!found) throw domain_error("No hay torres en esa direccion");
		return s;
	}
};