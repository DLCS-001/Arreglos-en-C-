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

void agregarContacto(Contacto agenda[], int& num_contactos) {
    if (num_contactos >= MAX_CONTACTOS) {
        cout << "Agenda llena." << endl;
        return;
    }

    limpiarBuffer();
    string nombre, telefono, email;
    cout << "Ingrese nombre: ";
    getline(cin, nombre);

    if (contactoExiste(agenda, num_contactos, nombre)) {
        cout << "Ese contacto ya existe." << endl;
        return;
    }

    do {
        cout << "Ingrese telefono (8 dígitos): ";
        getline(cin, telefono);
        if (!validarTelefono(telefono)) {
            cout << "Telefono invalido. Intente nuevamente." << endl;
        }
    } while (!validarTelefono(telefono));

    cout << "Ingrese email (opcional): ";
    getline(cin, email);

    agenda[num_contactos] = { nombre, telefono, email };
    num_contactos++;
    cout << "Contacto agregado." << endl;
}

int main() {
    Contacto agenda[MAX_CONTACTOS];
    int num_contactos = 0;

    cout << "Prueba de agregar contactos:" << endl;
    agregarContacto(agenda, num_contactos);
    
    cout << "\nContacto agregado:" << endl;
    cout << "Nombre: " << agenda[0].nombre << endl;
    cout << "Teléfono: " << agenda[0].telefono << endl;
    cout << "Email: " << agenda[0].email << endl;

    return 0;
}