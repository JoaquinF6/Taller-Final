#include <iostream>
#include <string>
using namespace std;

void aplicarCargo(double *saldo) {
    if (saldo != NULL) {
        if (*saldo >= 5) {
            *saldo = *saldo - 5;
            cout << "Cargo aplicado correctamente." << endl;
        } else {
            cout << "Saldo insuficiente para aplicar el cargo." << endl;
        }
    }
}

class BilleteraDigital {
private:
    string propietario;
    double saldo;
    double historial[20];
    int cantidadGastos;
    int gastosRegistrados;

    void guardarEnHistorial(double monto) {
        if (cantidadGastos < 20) {
            historial[cantidadGastos] = monto;
            cantidadGastos++;
        } else {
            cout << "Historial lleno. No se puede guardar mas gastos." << endl;
        }
    }

public:
    BilleteraDigital(string nom, double sal) {
        propietario = nom;
        saldo = sal;
        cantidadGastos = 0;
        gastosRegistrados = 0;

        for (int i = 0; i < 20; i++) {
            historial[i] = 0;
        }
    }

    void agregarIngreso(double monto) {
        if (monto > 0) {
            saldo = saldo + monto;
            cout << "Ingreso agregado correctamente." << endl;
        } else {
            cout << "Monto invalido." << endl;
        }
    }

    void registrarGasto(double monto, int &gastosSesion) {
        if (monto <= 0) {
            cout << "Monto invalido." << endl;
        } else if (monto > saldo) {
            cout << "Saldo insuficiente." << endl;
        } else {
            saldo = saldo - monto;
            guardarEnHistorial(monto);
            gastosRegistrados++;
            gastosSesion++;
            cout << "Gasto registrado correctamente." << endl;
        }
    }

    void verHistorial() {
        if (cantidadGastos == 0) {
            cout << "No hay gastos registrados." << endl;
        } else {
            cout << "=== HISTORIAL DE GASTOS ===" << endl;
            for (int i = 0; i < cantidadGastos; i++) {
                cout << i + 1 << ". $" << historial[i] << endl;
            }
        }
    }

    void verEstado() {
        cout << "Propietario: " << propietario << endl;
        cout << "Saldo actual: $" << saldo << endl;
        cout << "Cantidad de gastos: " << gastosRegistrados << endl;
    }

    double calcularPromedio() {
        if (cantidadGastos == 0) {
            return 0;
        }

        double suma = 0;
        for (int i = 0; i < cantidadGastos; i++) {
            suma = suma + historial[i];
        }

        return suma / cantidadGastos;
    }

    double* obtenerSaldo() {
        return &saldo;
    }
};

int main() {
    string propietario;
    double saldoInicial;
    int opcion = 0;
    int gastosSesion = 0;

    cout << "Ingrese el propietario: ";
    cin >> propietario;

    cout << "Ingrese el saldo inicial: ";
    cin >> saldoInicial;

    if (saldoInicial < 0) {
        cout << "Saldo inicial invalido. Se usara 0." << endl;
        saldoInicial = 0;
    }

    BilleteraDigital billetera(propietario, saldoInicial);

    while (opcion != 7) {
        cout << endl;
        cout << "=== MENU ===" << endl;
        cout << "1. Agregar ingreso" << endl;
        cout << "2. Registrar gasto" << endl;
        cout << "3. Ver historial" << endl;
        cout << "4. Ver estado" << endl;
        cout << "5. Ver promedio" << endl;
        cout << "6. Aplicar cargo" << endl;
        cout << "7. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                double monto;
                cout << "Ingrese el ingreso: ";
                cin >> monto;
                billetera.agregarIngreso(monto);
                break;
            }

            case 2: {
                double monto;
                cout << "Ingrese el gasto: ";
                cin >> monto;
                billetera.registrarGasto(monto, gastosSesion);
                break;
            }

            case 3:
                billetera.verHistorial();
                break;

            case 4:
                billetera.verEstado();
                break;

            case 5: {
                double promedio = billetera.calcularPromedio();
                cout << "Promedio de gastos: $" << promedio << endl;
                break;
            }

            case 6:
                aplicarCargo(billetera.obtenerSaldo());
                break;

            case 7:
                cout << "Gastos registrados en la sesion: " << gastosSesion << endl;
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }
    }

    return 0;
}
