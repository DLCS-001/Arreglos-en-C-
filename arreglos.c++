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

void mostrarContactos(const Contacto agenda[], int num_contactos) {
    if (num_contactos == 0) {
        cout << "No hay contactos en la agenda." << endl;
        return;
    }

    cout << "\n===== LISTA DE CONTACTOS =====" << endl;
    for (int i = 0; i < num_contactos; i++) {
        cout << "\nContacto " << i + 1 << ":" << endl;
        cout << "Nombre: " << agenda[i].nombre << endl;
        cout << "Telefono: " << agenda[i].telefono << endl;
        if (!agenda[i].email.empty())
            cout << "Email: " << agenda[i].email << endl;
        cout << "------------------------" << endl;
    }
}

int main() {
    Contacto agenda[MAX_CONTACTOS];
    int num_contactos = 0;

    // Agregar algunos contactos de prueba
    agenda[num_contactos++] = {"Juan Pérez", "12345678", "juan@email.com"};
    agenda[num_contactos++] = {"María García", "87654321", ""};

    // Mostrar los contactos
    mostrarContactos(agenda, num_contactos);

    return 0;
}