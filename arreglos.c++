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

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool validarTelefono(const string& telefono) {
    if (telefono.length() != 8) return false;
    for (char c : telefono) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool contactoExiste(Contacto agenda[], int num_contactos, const string& nombre) {
    for (int i = 0; i < num_contactos; i++) {
        if (agenda[i].nombre == nombre) {
            return true;
        }
    }
    return false;
}

int main() {
    cout << "Prueba de validarTelefono:" << endl;
    cout << "12345678: " << (validarTelefono("12345678") ? "válido" : "inválido") << endl;
    cout << "123: " << (validarTelefono("123") ? "válido" : "inválido") << endl;
    cout << "12345abc: " << (validarTelefono("12345abc") ? "válido" : "inválido") << endl;

    Contacto agenda[MAX_CONTACTOS];
    int num_contactos = 1;
    agenda[0] = {"Juan", "12345678", "juan@email.com"};
    
    cout << "\nPrueba de contactoExiste:" << endl;
    cout << "Buscando 'Juan': " << (contactoExiste(agenda, num_contactos, "Juan") ? "encontrado" : "no encontrado") << endl;
    cout << "Buscando 'Pedro': " << (contactoExiste(agenda, num_contactos, "Pedro") ? "encontrado" : "no encontrado") << endl;

    return 0;
}