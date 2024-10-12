#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<vector>
#include"fecha.h"
using namespace std;
using medico = string;
using paciente = string;

class consultorio {
private:
	unordered_map<medico, map<fecha, paciente, less<fecha>>>consulta;
public:
	consultorio() {}
	// COSTE: la busqueda e insercion en unordered_map son constantes, por tanto, el coste es constante
	void nuevoMedico(medico m) {
		unordered_map<medico, map<fecha, paciente>>::iterator it = consulta.find(m);
		if (it == consulta.end()) consulta.insert({ m, {} });
	}
	// COSTE: la busqueda e insercion en map son logaritmicas (tienen que preservar el orden), por tanto, el coste es logaritmico en el tamanio del mapa de fechas del medico m
	void pideConsulta(paciente p, medico m, fecha f) {
		unordered_map<medico, map<fecha, paciente>>::iterator itMedico = consulta.find(m);
		if (itMedico == consulta.end()) throw invalid_argument("Medico no existente");
		map<fecha, paciente>::iterator itFecha = itMedico->second.find(f);
		if (itFecha != itMedico->second.end()) throw invalid_argument("Fecha ocupada");
		itMedico->second.insert({ f,p });
	}
	// COSTE: la busqueda en unordered_map es constante, al igual que mirar si un map es vacio o no y el acceso al primer y ultimo elemento tanto en unordered_map como en map
	// por tanto, el coste es constante
	paciente siguientePaciente(medico m) {
		unordered_map<medico, map<fecha, paciente>>::iterator itMedico = consulta.find(m);
		if (itMedico == consulta.end()) throw invalid_argument("Medico no existente");
		if (itMedico->second.empty()) throw invalid_argument("No hay pacientes");
		return itMedico->second.begin()->second;
	}
	// COSTE: la busqueda en unordered_map es constante, al igual que mirar si un map es vacio o no y el acceso al primer y ultimo elemento tanto en unordered_map como en map
	// por tanto, el coste es logaritmico en el numero de consultas que tenga el medico m (aunque se borre la primera consulta)
	void atiendeConsulta(medico m) {
		unordered_map<medico, map<fecha, paciente>>::iterator itMedico = consulta.find(m);
		if (itMedico == consulta.end()) throw invalid_argument("Medico no existente");
		if (itMedico->second.empty()) throw invalid_argument("No hay pacientes");
		itMedico->second.erase(itMedico->second.begin()->first);
	}
	// COSTE: lineal en el numero de consultas que tiene el medico m
	vector<pair<fecha, paciente>> listaPacientes(medico m, fecha f) {
		unordered_map<medico, map<fecha, paciente>>::iterator itMedico = consulta.find(m);
		if (itMedico == consulta.end()) throw invalid_argument("Medico no existente");
		if (itMedico->second.empty()) return vector<pair<fecha,paciente>>();
		vector<pair<fecha,paciente>>ret;
		for (auto it = itMedico->second.cbegin(); it != itMedico->second.cend(); it++) {
			if (it->first.getDia() == f.getDia()) ret.push_back({ it->first, it->second});
		}
		return ret;
	}
};