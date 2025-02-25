#include<iostream>
#include <limits>
#include <iomanip>

using namespace std;

struct Movimiento {
    int numMovimiento;
    string nombre;
    string cuenta; // Numero de cuenta (minimo 8 dígitos)
    string tipo;   // "Deposito" o "Retiro"
    float monto;
    struct Movimiento *next; 
    
    Movimiento(int numMovimiento, string nombre, string cuenta, string tipo, float monto){
    	this->numMovimiento = numMovimiento;
    	this->nombre = nombre;
    	this->cuenta = cuenta;
    	this->tipo = tipo;
    	this->monto = monto;
    	next = nullptr;
	}
};

typedef Movimiento* Pila;

template <typename T>
T leerValor(int menor, int mayor, const string &aviso = ""){
    T valor;
    while (true)
    {
        try
        {
            cin >> valor;
            if (cin.fail())
            {
                throw exception();
            }
            
            if (valor < menor || valor > mayor)
            {
                if (!aviso.empty() && valor >= 50000) { // para el aviso al retirar solamente
                    cout << aviso << endl;
                    return valor;
                }
				cout << "\n**Introduzca un numero dentro de rango**" << endl;
            }else {
                return valor;
        	}
        }
        catch(const exception& e)
        {
            cout << "Numero no valido" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

}

void ingresarMovimiento(Pila &pila_movimientos, float &fondoCaja);
void mostrarMovimientos(Pila &pila_movimientos);
void corteCaja(Pila &pila_movimientos);
int menu();
float inicio();

int main(){
    int op;
    float fondoCaja;
    Pila pila_movimientos = nullptr;
    
    fondoCaja = inicio();
    do{
    	op = menu();
    	switch(op){
			case 1:
				ingresarMovimiento(pila_movimientos, fondoCaja);
				break;
			case 2:
				mostrarMovimientos(pila_movimientos);
				break;
			case 3:
				
				break;
			case 4:
				cout << "\nSaliendo....";
				break;
		}
	}while(op != 4);
    
	return 0;
}

float inicio(){
	cout << "\n***CAJA BANCARIA***"<< endl;
	cout << "\n**INICIANDO EL DIA EN CAJA**" << endl;
	cout << "\nAntes de comenzar a registrar movimientos, ingrese el fondo de caja inicial (minimo $300000):\n$ ";
	float fondoCaja = leerValor<float>(300000.0, 9999999.0);
	cout << "\nGracias. MOSTRANDO MENU..." << endl;
	return fondoCaja;
}

int menu(){
	system("cls");
	cout << "\n***CAJA BANCARIA***"<< endl;
	cout << "\n**MENU**" << endl;
	cout << "\n1.-Ingresar movimiento bancario\n2.-Mostrar movimientos bancarios\n3.-Generar corte de caja\n4.-Salir\n-> ";
	int op = leerValor<int>(1,4);
	cout << op << " <-";
	return op;
}

int obtenerUltimoNumeroMovimiento(Pila &pila_movimientos) {
    if (pila_movimientos == nullptr) return 0; // Si la pila está vacía, empezar desde 1
    return pila_movimientos->numMovimiento; // Devolver el número del movimiento más reciente
}

void ingresarMovimiento(Pila &pila_movimientos, float &fondoCaja){
	system("cls");
	cout << "\n***INGRESAR MOVIMIENTO BANCARIO***"<< endl;
	
	string nombre, tipo, cuenta;
    int op, val, salida;
    float monto;
	
	cin.ignore();
	cout << "\nIntroduzca el nombre de cuenta: ";
	getline(cin, nombre);
	
	cout << "\nIntroduzca el numero de cuenta (al menos 8 digitos): ";
	do{
		getline(cin, cuenta);
		if(cuenta.length() < 8)
			cout << "\nEl numero de cuenta debe de contener al menos 8 digitos. Intente de nuevo: ";
	}while(cuenta.length() < 8);
	
	cout << "\nElija un tipo de movimiento a realizar:\n(1.- Deposito // 2.- Retiro): ";
	op = leerValor<int>(1,2);

	
	if(op == 1){
		tipo = "Deposito";
		cout << "\nIntroduzca el monto a depositar: $ ";
		monto = leerValor<float>(0.1, 99999999);
		cout << "\nSe ingresara el monto de $" << monto <<" a la caja. Desea proceder? (1.- Si / 2.- No)\n-> ";
		val = leerValor<int>(1,2);
		
		if(val == 2)
			return;
			
		fondoCaja += monto;
	}else{
		tipo = "Retiro";
		cout << "\nIntroduzca el monto a retirar (el maximo a retirar en caja es de $50000): $ ";
		monto = leerValor<float>(0.1, 50000, "\nPor favor, pase a la gerencia para realizar el retiro. Se cancelara la operacion."); 
		
		if(monto >= 50000){
			cout << "\nOperacion cancelada. Presione enter para continuar...";
			cin.ignore();
			cin.get();
			return;
		}
		cout << "\nSe retirara el monto de $" << monto <<" a la caja. Desea proceder? (1.- Si / 2.- No)\n-> ";
		val = leerValor<int>(1,2);
		
		if(val == 2)
			return;
			
		if(fondoCaja - monto < 0) {
            cout << "\nNo hay suficiente dinero en la caja para realizar el retiro. Proceder a hacer corte de caja? (1.- Realizar corte de caja / 2.- Salir al menu y cancelar operacion): " << endl;
            salida = leerValor<int>(1,2);
            if(salida == 1){
            	cin.ignore();
				cin.get();
				//llamada a funcion corte de caja
			}
            else{
            	return;
			}
            return;
        }
        fondoCaja -= monto;
	}
	
	int numMovimiento = obtenerUltimoNumeroMovimiento(pila_movimientos) + 1;
	
	Movimiento* nuevo_movimiento = new Movimiento(numMovimiento, nombre, cuenta, tipo, monto);
	if(pila_movimientos ==  nullptr){
		pila_movimientos = nuevo_movimiento;
	}else{
		nuevo_movimiento->next = pila_movimientos;
		pila_movimientos = nuevo_movimiento;
	}
	
	cout << "\nMovimiento de tipo " << tipo << " realizado correctamente. Presione enter para continuar...";
	cin.ignore();
	cin.get();
	
	return;
}

void mostrarMovimientos(Pila &pila_movimientos){
    system("cls");
    cout << "\n*** MOSTRAR MOVIMIENTOS BANCARIOS ***\n" << endl;

    if (pila_movimientos == nullptr) {
        cout << "\nNo hay movimientos recientes." << endl;
        cout << "\nPresione enter para continuar...";
        cin.ignore();
        cin.get();
        return;
    }

    // Encabezado de la tabla
    cout << left << setw(15) << "Num. Mov" 
         << setw(20) << "Nombre"
         << setw(15) << "Cuenta" 
         << setw(10) << "Tipo"
         << setw(10) << "Monto" << endl;
    cout << string(70, '-') << endl; // Linea divisoria

    Pila aux = pila_movimientos;
    while (aux != nullptr) {
        cout << left << setw(15) << aux->numMovimiento
             << setw(20) << aux->nombre
             << setw(15) << aux->cuenta
             << setw(10) << aux->tipo
             << setw(10) << fixed << setprecision(2) << aux->monto
             << endl;
        aux = aux->next;
    }

    cout << "\nPresione enter para continuar...";
    cin.ignore();
    cin.get();
}
void corteCaja(Pila &pila_movimientos) {
	while(pila_movimientos != nullptr) {
		Movimiento* temp = pila_movimientos;
		pila_movimientos = pila_movimientos->next;
		delete temp;
	}
	pila_movimientos = nullptr;
}
