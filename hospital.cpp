#include<iostream>
#include <limits>

/*Lia Pardo
 * Alejandro Quintanilla
 * Angel Joseph Meraz Hernandez
 * Luis Fernando Segobia Torres 2177528
 * */

using namespace std;

struct Paciente{
	int codigo;
	string nombres;
	string apellidos;
	string direccion;
	long telefono;
	float adeudo;
	bool status;
	Paciente *next;

	Paciente(int codigo, string nombres, string apellidos, string direccion, long telefono, float adeudo){
		this->codigo = codigo;
		this->nombres = nombres;
		this->apellidos = apellidos;
		this->direccion = direccion;
		this->telefono = telefono;
		this->adeudo = adeudo;
		status = true;
		next = nullptr;
	}
};

typedef Paciente* Lista;

template <typename T>
T leerValor(T menor, T mayor){
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


void registrar(Lista &lista_pacientes, const int matricula);
void mostrar(Lista lista_pacientes);
int menu();


int main(){
	int matricula = 0;
	int op;
	Lista lista_pacientes = nullptr;

	do{
		op = menu();
		matricula++;
		switch(op){
			case 1:
				registrar(lista_pacientes, matricula);
				break;
			case 2:
				break;
			case 3:
				mostrar(lista_pacientes);
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				cout << "\nSaliendo....";
				break;
		}
	}while(op != 6);
	

   return 0;	
}


int menu(){
	system("clear");
	cout << "\n***SERVICIO DE HOSPITAL***"<< endl;
	cout << "\n**MENU**" << endl;
	cout << "\n1.-Registro de paciente\n2.-Modificar paciente\n3.-Mostrar pacientes\n4.-Pagar adeudo\n5.-Eliminar paciente\n6.-Salir"<<endl;
	int op = leerValor<int>(1,6);
	cout << op;
	return op;
}

void registrar(Lista &lista_pacientes, const int matricula){
	system("clear");
	cout << "\n***SISTEMA DE REGISTRO DE PACIENTE***" << endl;

	string nombres, apellidos, direccion;
	long telefono;
	int aux_status;
	float adeudo;
	bool status;

	cin.ignore();
	cout << "\nIntroduzca el o los nombres del paciente: ";
	getline(cin, nombres);
	
	cout << "\nIntroduzca los apellidos del paciente: ";
	getline(cin, apellidos);

	cout << "\nIntroduzca la direccion del paciente: ";
	getline(cin, direccion);

	cout << "\nIntroduzca el telefono del paciente: ";
	telefono = leerValor<long>(1000000000, 9999999999);
	
	cout << "\nIntroduzca el adeudo de el paciente: ";
	adeudo = leerValor<float>(0.1, numeric_limits<streamsize>::max());

	Paciente* nuevo_paciente = new Paciente(matricula, nombres, apellidos, direccion, telefono, adeudo);
	if (lista_pacientes == nullptr){
		lista_pacientes = nuevo_paciente;
		return;	
	}
	
	Paciente* aux = lista_pacientes;
	while(aux->next != nullptr){
		aux = aux->next;
	}

	aux->next = nuevo_paciente;

}

void mostrar(Lista lista_pacientes){
	cout << "\n***LISTA DE PACIENTES***" << endl;
	Paciente *aux = lista_pacientes;
	if(lista_pacientes == nullptr){
		cout << "Lista vacia";
		system("pause");
		return;
	}
	while(aux != nullptr){
		cout << "Matricula: " << aux->codigo << endl
			<< "Nombres: " << aux->nombres << endl
			<< "Apellidos: "<<aux->apellidos << endl
			<< "Adeudo: " << aux->adeudo << endl
			<< "Status: " << aux->status << endl;
		aux = aux->next;
	}
	system("pause");
	return;
}






























