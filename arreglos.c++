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

int main() {
    int opcion;
    do {
        opcion = mostrarMenu();
        cout << "Seleccionaste la opción: " << opcion << endl;
    } while (opcion != 7);
    
    return 0;
}