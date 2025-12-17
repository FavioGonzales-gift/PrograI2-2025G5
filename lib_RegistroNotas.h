#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Notas_estudiante
{
    int CI_estudiante;;
    double Matematica;
    double Fisica;
    double Quimica;
    double Biologia;
    double Lenguaje;
    double Promedio;
    char Estado[15];
};

void Registrar_Nota(string ArchivoBin)
{
    Notas_estudiante nota;
    ofstream binario;
    binario.open(ArchivoBin, ios::binary|ios::app);

    if (binario.good())
    {
        cout << "Ingrese el CI del estudiante: ";
        cin >> nota.CI_estudiante;

        cout << "Ingrese la nota de Matemáticas: ";
        cin >> nota.Matematica;

        cout << "Ingrese la nota de Física: ";
        cin >> nota.Fisica;

        cout << "Ingrese la nota de Química: ";
        cin >> nota.Quimica;

        cout << "Ingrese la nota de Biología: ";
        cin >> nota.Biologia;

        cout << "Ingrese la nota de Lenguaje: ";
        cin >> nota.Lenguaje;

        nota.Promedio = (nota.Matematica + nota.Fisica + nota.Quimica + nota.Biologia + nota.Lenguaje) / 5;
        
        if (nota.Promedio < 51)
        {
            strcpy(nota.Estado, "REPROBADO");
        }
        
        if (nota.Promedio >= 51 && nota.Promedio <= 100);
        {
            strcpy(nota.Estado, "APROBADO");
        }
        
        binario.write((char*)&nota, sizeof(Notas_estudiante));
    }

    else
    {
        cout << "Archivo no encontrado" << endl;
    }
    
    binario.close();  
}



