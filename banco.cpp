#include<iostream>
#include <limits>

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
    	this->cuenta = cuenta;
    	this->tipo = tipo;
    	this->monto = monto;
    	next = nullptr;
	}
};

typedef Movimiento* Pila;

template <typename T>
T leerValor(int menor, int mayor){
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
                cout << "\n**Introduzca un numero dentro de rango**" << endl;
            }else{
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

void ingresarMovimiento(Pila &pila_movimientos, float &fondoCaja, const int numMovimiento);
int menu();
float inicio();

int main(){
    int op, numMovimiento = 0, x;
    float fondoCaja;
    Pila pila_movimientos = nullptr;
    
    fondoCaja = inicio();
    do{
    	op = menu();
    	numMovimiento++;
    	switch(op){
			case 1:
				ingresarMovimiento(pila_movimientos, fondoCaja, numMovimiento);
				break;
			case 2:
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

void ingresarMovimiento(Pila &pila_movimientos, float &fondoCaja, const int numMovimiento){
	system("cls");
	cout << "\n***INGRESAR MOVIMIENTO BANCARIO***"<< endl;
	
	string nombre, tipo, cuenta;
    int op, val, x;
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
		cout << "\nIntroduzca el monto a retirar (el maximo a retirar es de $50000): $ ";
		monto = leerValor<float>(0.1, 50000); // aqui hay que ajustar para que muestre el aviso de paso a gerencia
		cout << "\nSe retirara el monto de $" << monto <<" a la caja. Desea proceder? (1.- Si / 2.- No)\n-> ";
		val = leerValor<int>(1,2);
		if(val == 2)
			return;
		if(fondoCaja - monto < 0) {
            cout << "No hay suficiente dinero en la caja para realizar el retiro. Proceder a hacer corte de caja? (1.- Si / 2.- No): " << endl;
            // leer la opción y realizar el logout o salir al menu
            return;
        }
        fondoCaja -= monto;
	}
	
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
