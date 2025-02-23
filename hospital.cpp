#include<iostream>
#include <limits>

using namespace std;

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

int main(){
    int matricula;
    matricula = leerValor<int>(1, numeric_limits<streamsize>::max());

    
}