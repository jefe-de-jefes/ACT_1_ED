#include<iostream>
#include <limits>

/*Lia Fernanda Pardo Mireles 2096765​ 
 * Alejandro Quintanilla Leal 2010568​
 * Angel Joseph Meraz Hernandez 2067151
 * Luis Fernando Segobia Torres 2177528
 * */

using namespace std;

struct Paciente{
	int codigo;
	string nombres;
	string apellidos;
	string direccion;
	long long telefono;
	float adeudo;
	bool status;
	Paciente *next;

	Paciente(int codigo, string nombres, string apellidos, string direccion, long long telefono, float adeudo){
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
string leerCadena() {
    string entrada;
    
    do {
        getline(cin, entrada);  
        if (entrada.empty()) {
            cout << "\n**La entrada no puede estar vacía. Intenta de nuevo.**\n" << endl;
        }

    } while (entrada.empty());
    
    return entrada;
}
template <typename T>
T leerValor(T menor, T mayor){
    T valor;
    while (true)
    {
        cin >> valor;
        if (cin.fail())
        {
            cout << "Numero no valido, intente nuevamente.." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        if (valor < menor || valor > mayor)
        {
            cout << "\n**Numero fuera de rango, intente nuevamente**" << endl;
			continue;
        }else{
            return valor;
        }
    }

}



void registrar(Lista &lista_pacientes, const int matricula);
void modificar(Lista &lista_pacientes, const int matricula);
void mostrar(const Lista lista_pacientes);
Lista findMatricula(const Lista lista, int matricula);
void mostrar_paciente(const Paciente* paciente);
void pagar(Lista &lista_pacientes, const int matricula);
void eliminar_paciente(Lista &lista_pacientes);
void eliminar_lista(Lista &lista_pacientes);

int menu();


int main(){
	int matricula = 0;
	int op;
	Lista lista_pacientes = nullptr;

	do{
		op = menu();
		switch(op){
			case 1:
                matricula++;
				registrar(lista_pacientes, matricula);
				break;
			case 2:
				modificar(lista_pacientes, matricula);
				break;
			case 3:
				mostrar(lista_pacientes);
				break;
			case 4:
				pagar(lista_pacientes, matricula);
				break;
			case 5:
				eliminar_paciente(lista_pacientes);
				break;
			case 6:
				cout << "\nSaliendo....";
				eliminar_lista(lista_pacientes);
				cout << "\n**Memoria liberada**\n";
				break;
		}
	}while(op != 6);
	
   return 0;	
}


int menu(){
	system("cls");
	cout << "\n***SERVICIO DE HOSPITAL***"<< endl;
	cout << "\n**MENU**" << endl;
	cout << "\n1.-Registro de paciente\n2.-Modificar paciente\n3.-Mostrar pacientes\n4.-Pagar adeudo\n5.-Eliminar paciente\n6.-Salir"<<endl;
	int op = leerValor<int>(1,6);
	cout << op;
	return op;
}

void registrar(Lista &lista_pacientes, const int matricula){
	system("cls");
	cout << "\n***SISTEMA DE REGISTRO DE PACIENTE***" << endl;

	string nombres, apellidos, direccion;
	long long telefono;
	int aux_status;
	float adeudo;
	bool status;

	cin.ignore();
	cout << "\nIntroduzca el o los nombres del paciente: ";
	nombres = leerCadena();
	
	cout << "\nIntroduzca los apellidos del paciente: ";
	apellidos = leerCadena();

	cout << "\nIntroduzca la direccion del paciente: ";
	direccion = leerCadena();

	cout << "\nIntroduzca el telefono del paciente: ";
	telefono = leerValor<long long>(1000000000, 9999999999);
	
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

void modificar(Lista &lista_pacientes, int matricula){
	int op, mat;
	Paciente * paciente;
	system("cls");
	cout << "\n**MODIFICAR PACIENTE**" << endl;

	if(lista_pacientes == nullptr){
		cout << "Lista vacia" << endl;
		system("pause");
		return;
	}

	cout << "\nIntroduzca la matricula del paciente a modificar: ";
	mat = leerValor<int>(1, numeric_limits<streamsize>::max());
	paciente = findMatricula(lista_pacientes, mat);

	if(paciente == nullptr) return;
	

	cout << "\n1.- Nombres\n2.- Apellidos\n3.- Direccion\n4.-Telefono\n5.-Adeudo" << endl;
	cout << "Que dato desea modificar?: ";
	op = leerValor<int>(1, 6);

	string nuevo;
	long long new_number;
	float new_adeudo;
	cin.ignore();
	switch (op)
	{
	case 1:
		cout << "Introduzca el/los nuevos nombres: ";
		nuevo = leerCadena();
		paciente->nombres = nuevo;
		break;
	case 2:
		cout << "Introduzca los nuevos apellidos: ";
		nuevo = leerCadena();
		paciente->apellidos = nuevo;	
		break;
	case 3:
		cout << "Introduzca la nueva direccion: ";
		nuevo = leerCadena();
		paciente->direccion = nuevo;
		break;
	case 4:
		cout << "Introduzca el nuevo telefono: ";
		new_number = leerValor<long long>(1000000000, 9999999999);
		paciente->telefono = new_number;
		break;
	case 5:
		cout << "Introduzca el nuevo adeudo: ";
		new_adeudo = leerValor<float>(0, 99999999.99999);
		paciente->adeudo = new_adeudo;
		break;
	}

	cout << "\n**Paciente modificado**\n";
	mostrar_paciente(paciente);
	system("pause");

	return;
}

void mostrar(const Lista lista_pacientes){
    system("cls");
	cout << "\n***LISTA DE PACIENTES***" << endl;
	Paciente *aux = lista_pacientes;
	if(lista_pacientes == nullptr){
		cout << "Lista vacia" << endl;
		system("pause");
		return;
	}
	while(aux != nullptr){
        cout << "\n-----------------------------------\n";
		cout << "Matricula: " << aux->codigo << endl
			<< "Nombres: " << aux->nombres << endl
			<< "Apellidos: "<<aux->apellidos << endl
			<< "Adeudo: " << aux->adeudo << endl
			<< "Status: " << (aux->status == 1 ? "**Activo**" : "**Alta**") << endl;
		aux = aux->next;
	}
    cout << endl;
	system("pause");
	return;
}

void mostrar_paciente(const Paciente* paciente){
	cout << "Codigo: " << paciente->codigo << endl
	<< "Nombres: " << paciente->nombres << endl
	<< "Apellidos: "<< paciente->apellidos << endl
	<< "Direccion: " << paciente->direccion << endl
	<< "Telefono: " << paciente->telefono << endl
	<< "Adeudo: " << paciente->adeudo << endl;
	cout <<"-----------------------------------------\n";
	return;
}


Lista findMatricula(const Lista lista, int matricula){
	Paciente* aux = lista;
	while (aux != nullptr)
	{
		if (aux->codigo == matricula){
			cout << "\n**Codigo encontrado**\n";
			mostrar_paciente(aux);
			return aux;
		}
		else
			aux = aux->next;
	}
	cout << "\nMatricula no encontrada\n";
	system("pause");
	return nullptr;	
}

void pagar(Lista &lista_pacientes, int matricula){
	int mat;
	Paciente * paciente;
	system("cls");
	cout << "\n**PAGAR ADEUDO**" << endl;

	if(lista_pacientes == nullptr){
		cout << "Lista vacia" << endl;
		system("pause");
		return;
	}

	cout << "\nIntroduzca la matricula del paciente al cual quitar su adeudo: ";
	mat = leerValor<int>(1, numeric_limits<streamsize>::max());
	paciente = findMatricula(lista_pacientes, mat);

	if(paciente == nullptr)
		return;
	
	paciente->adeudo = 0;
	paciente->status = false;
	cout << "El adeudo del paciente bajo a $0 y fue dado de alta" << endl;
	mostrar_paciente(paciente);
	system("pause");

	return;
}

void eliminar_paciente(Lista &lista_pacientes){
	int encontrar = 0, mat;
	Lista p, ant;
    	p = lista_pacientes;
	system("cls");
	cout << "\n**ELIMINAR PACIENTE**" << endl;

	if(lista_pacientes == nullptr){
		cout << "Lista vacia" << endl;
		system("pause");
		return;
	}
	
	cout << "\nIntroduzca la matricula del paciente a eliminar: ";
	mat = leerValor<int>(1, numeric_limits<streamsize>::max());
	
	while(p!=nullptr){
        if(p->codigo==mat)
        {
            cout << "\n**Paciente encontrdo**" << endl;
            encontrar = 1;
            if (p->status==0){
            	if(p==lista_pacientes)
                	lista_pacientes = lista_pacientes->next;
                else
                    ant->next = p->next;
                delete(p);
                cout << "\n**Paciente eliminado**" << endl;
			}
			if (p->status==1){
				cout << "\n**El paciente aun no esta dado de alta.**" << endl;
			}
			system("pause");
            return;
            }
            ant = p;
            p = p->next;
        }
    	if(encontrar == 0)
		cout << "\n**No se encontro el paciente a eliminar**" << endl;
	system("pause");

	return;
}

void eliminar_lista(Lista &lista_pacientes){
	Lista p;
    p = lista_pacientes;
	cout<< endl;
	
	while(p!=nullptr){
		lista_pacientes = lista_pacientes->next;
        delete(p);
        p = lista_pacientes;
        }

	return;
}
