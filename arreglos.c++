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

void buscarContacto(const Contacto agenda[], int num_contactos) {
    if (num_contactos == 0) {
        cout << "No hay contactos en la agenda." << endl;
        return;
    }

    limpiarBuffer();
    string busqueda;
    cout << "Ingrese nombre o telefono a buscar: ";
    getline(cin, busqueda);

    bool encontrado = false;
    for (int i = 0; i < num_contactos; i++) {
        if (agenda[i].nombre.find(busqueda) != string::npos || 
            agenda[i].telefono.find(busqueda) != string::npos) {
            if (!encontrado) {
                cout << "\nContactos encontrados:" << endl;
                encontrado = true;
            }
            cout << "Nombre: " << agenda[i].nombre << endl;
            cout << "Telefono: " << agenda[i].telefono << endl;
            if (!agenda[i].email.empty())
                cout << "Email: " << agenda[i].email << endl;
            cout << "------------------------" << endl;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron contactos." << endl;
    }
}

void eliminarContacto(Contacto agenda[], int& num_contactos) {
    if (num_contactos == 0) {
        cout << "No hay contactos para eliminar." << endl;
        return;
    }

    mostrarContactos(agenda, num_contactos);
    int indice;
    cout << "\nIngrese el número del contacto a eliminar (1-" << num_contactos << "): ";
    while (!(cin >> indice) || indice < 1 || indice > num_contactos) {
        cout << "Número invalido. Intente nuevamente: ";
        limpiarBuffer();
    }

    indice--;
    for (int i = indice; i < num_contactos - 1; i++) {
        agenda[i] = agenda[i + 1];
    }
    num_contactos--;
    cout << "Contacto eliminado exitosamente." << endl;
}

void guardarAgenda(const Contacto agenda[], int num_contactos) {
    ofstream archivo(RUTA);
    if (archivo.is_open()) {
        for (int i = 0; i < num_contactos; i++) {
            archivo << "nombre: " << agenda[i].nombre << endl;
            archivo << "numero: " << agenda[i].telefono << endl;
            if (!agenda[i].email.empty()) {
                archivo << "email: " << agenda[i].email << endl;
            }
            archivo << "------------------------" << endl;
        }
        archivo.close();
        cout << "Agenda guardada en: " << RUTA << endl;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

int main() {
    Contacto agenda[MAX_CONTACTOS];
    int num_contactos = 0;

    // Agregar contactos de prueba
    agenda[num_contactos++] = {"Juan Pérez", "12345678", "juan@email.com"};
    agenda[num_contactos++] = {"María García", "87654321", ""};

    cout << "Guardando agenda de prueba..." << endl;
    guardarAgenda(agenda, num_contactos);

    return 0;
}