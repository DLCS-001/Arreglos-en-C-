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

int mostrarMenu() {
    int opcion;
    cout << "\n===== MENÚ DE AGENDA =====" << endl;
    cout << "1. Agregar contacto" << endl;
    cout << "2. Mostrar contactos" << endl;
    cout << "3. Buscar contacto" << endl;
    cout << "4. Eliminar contacto" << endl;
    cout << "5. Guardar agenda" << endl;
    cout << "6. Cargar agenda" << endl;
    cout << "7. Salir" << endl;
    cout << "Elija una opcion: ";

    while (!(cin >> opcion) || opcion < 1 || opcion > 7) {
        cout << "Opcion invalida. Intente nuevamente: ";
        limpiarBuffer();
    }

    return opcion;
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
        if (agenda[i].nombre.find(busqueda) != string::npos || agenda[i].telefono.find(busqueda) != string::npos) {
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

void cargarAgenda(Contacto agenda[], int& num_contactos) {
    limpiarBuffer();
    char confirmar;
    cout << "\nEsto sobrescribira la agenda actual. ¿Desea continuar? (s/n): ";
    cin >> confirmar;

    if (confirmar != 's' && confirmar != 'S') {
        cout << "Carga cancelada por el usuario." << endl;
        return;
    }

    ifstream archivo(RUTA);
    if (archivo.is_open()) {
        num_contactos = 0;
        string linea, separador;

        while (num_contactos < MAX_CONTACTOS) {
            if (!getline(archivo, linea) || linea.empty()) break;

            if (linea.substr(0, 7) == "nombre: ") {
                agenda[num_contactos].nombre = linea.substr(7);

                if (getline(archivo, linea) && linea.substr(0, 7) == "numero: ") {
                    agenda[num_contactos].telefono = linea.substr(7);

                    if (getline(archivo, linea) && linea.substr(0, 6) == "email: ") {
                        agenda[num_contactos].email = linea.substr(6);
                        getline(archivo, separador);
                    } else {
                        agenda[num_contactos].email = "";
                    }

                    num_contactos++;
                }
            }
        }

        archivo.close();
        cout << "\nAgenda cargada exitosamente desde: " << RUTA << endl;
    } else {
        cout << "\nError: No se pudo abrir el archivo en la ruta: " << RUTA << endl;
    }
}

int main() {
    Contacto agenda[MAX_CONTACTOS];
    int num_contactos = 0;
    int opcion;

    do {
        opcion = mostrarMenu();

        switch (opcion) {
            case 1:
                agregarContacto(agenda, num_contactos);
                break;
            case 2:
                mostrarContactos(agenda, num_contactos);
                break;
            case 3:
                buscarContacto(agenda, num_contactos);
                break;
            case 4:
                eliminarContacto(agenda, num_contactos);
                break;
            case 5:
                guardarAgenda(agenda, num_contactos);
                break;
            case 6:
                cargarAgenda(agenda, num_contactos);
                break;
            case 7:
                guardarAgenda(agenda, num_contactos);
                cout << "Saliendo..." << endl;
                break;
        }
    } while (opcion != 7);

    return 0;
}