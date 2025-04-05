#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const int MAX_CONTACTOS = 100;
const string RUTA = "agenda.txt";

struct Contacto {
    string nombre;
    string telefono;
    string email;
};

int main() {
    cout << "Estructura básica inicializada correctamente" << endl;
    return 0;
}