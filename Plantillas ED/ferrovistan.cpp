//-------------------------------------------------------
// Ejercicio 3: Ferrovistán. Mayo 2022
// Escribe tu nombre y respuestas en las zonas indicadas
//-------------------------------------------------------
//@ <answer>
// Nombre :
// Usiario del Juez de Clase :
// Usuario del Juez de Exámenes :
//@ </answer>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
//Añade las librerías que necesites:
//@ <answer>

//@ </answer>

using namespace std;

// Elige el tipo representante adecuado para el TAD Ferrovistan e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente. Justifica la elección de los tipos y el
// coste de todas las operaciones.
//@ <answer>

using tLinea = string;          //Nombres de líneas
using tEstacion = string;       //Nombres de estaciones

class Ferrovistan {

private:
    

public:

    void nueva_linea(const tLinea &nombre) {
    
    }

    void nueva_estacion(const tLinea &linea, const tEstacion &nombre, int posicion) {
       
    }

    void eliminar_estacion(const tEstacion &estacion) {
       
    }

    vector<string> lineas_de(const tEstacion &estacion) const {
        
    }

    string proxima_estacion(const tLinea &linea, const tEstacion &estacion) const {
        
    }

};

//@ </answer>
//
// ¡No modifiques nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    Ferrovistan trenes;
    string operacion;
    cin >> operacion;

    if (!cin)
        return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "nueva_linea") {
                string nombre;
                cin >> nombre;
                trenes.nueva_linea(nombre);
            }
            else if (operacion == "nueva_estacion") {
                string linea, nombre;
                int posicion;
                cin >> linea;
                cin >> nombre;
                cin >> posicion;
                trenes.nueva_estacion(linea, nombre, posicion);
            }
            else if (operacion == "eliminar_estacion") {
                string estacion;
                cin >> estacion;
                trenes.eliminar_estacion(estacion);
            }
            else if (operacion == "lineas_de") {
                string estacion;
                cin >> estacion;
                vector<string> lineas = trenes.lineas_de(estacion);
                cout << "Lineas de " << estacion << ":";
                for (const string &linea: lineas)
                    cout << " " << linea;
                cout << endl;
            }
            else if (operacion == "proxima_estacion") {
                string linea, estacion;
                cin >> linea;
                cin >> estacion;
                string proxima = trenes.proxima_estacion(linea, estacion);
                cout << proxima << endl;
            }
        }
        catch (exception& e) {
            cout << "ERROR: " << e.what() << endl;
        }
        cin >> operacion;
    }
    cout << "---" << endl;

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("sample3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
    ;

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif


    return 0;

} // main
