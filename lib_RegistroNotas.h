#ifndef LIB_REGISTRONOTAS_H
#define LIB_REGISTRONOTAS_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Notas_estudiante
{
    int CI_estudiante;
    double Matematica;
    double Fisica;
    double Quimica;
    double Biologia;
    double Lenguaje;
    double Promedio;
    char Estado[15];
};

void Registrar_Nota(string Archivo_Registro_Notas)
{
    Notas_estudiante nota;
    ofstream archivo;
    archivo.open(Archivo_Registro_Notas, ios::binary|ios::app);

    if (archivo.good())
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

        nota.Promedio = (nota.Matematica + nota.Fisica + nota.Quimica + nota.Biologia + nota.Lenguaje) / 5.0;
        
        if (nota.Promedio < 51)
        {
            strcpy(nota.Estado, "REPROBADO");
        }
        
        if (nota.Promedio >= 51 && nota.Promedio <= 100)
        {
            strcpy(nota.Estado, "APROBADO");
        }
        
        archivo.write((char*)&nota, sizeof(Notas_estudiante));
        archivo.close();

        cout << "Notas registradas correctamente" << endl;
    }

    else
    {
        cout << "Archivo no encontrado" << endl;
    }
}

void Modificar_Nota(string Archivo_Registro_Notas)
{
    int CI_buscar;
    cout << "Ingrese el CI del estudiante que requiere modificar notas: ";
    cin >> CI_buscar;

    fstream archivo(Archivo_Registro_Notas, ios::binary | ios::in | ios::out);
    
    if (!archivo)
    {
        cout << "Error: No se pudo abrir el archivo de notas" << endl;
        return;
    }

    Notas_estudiante nota;
    bool encontrado = false;
    streampos posicion;

    while (archivo.read((char*)&nota, sizeof(Notas_estudiante)))
    {
        posicion = archivo.tellg() - sizeof(Notas_estudiante);  

        if (nota.CI_estudiante == CI_buscar)
        {
            encontrado = true;

            cout << "\nNotas actuales del estudiante: " << endl;
            cout << "Matemáticas: " << nota.Matematica << endl;
            cout << "Física: " << nota.Fisica << endl;
            cout << "Química: " << nota.Quimica << endl;
            cout << "Biología: " << nota.Biologia << endl;
            cout << "Lenguaje: " << nota.Lenguaje << endl;
            cout << "Promedio: " << nota.Promedio << endl; 
            cout << "Estado: " << nota.Estado << endl;

            cout << "\nIngrese las nuevas notas:" << endl;
            cout << "Matemáticas: "; cin >> nota.Matematica;
            cout << "Física: ";       cin >> nota.Fisica;
            cout << "Química: ";      cin >> nota.Quimica;
            cout << "Biología: ";     cin >> nota.Biologia;
            cout << "Lenguaje: ";     cin >> nota.Lenguaje;

            nota.Promedio = (nota.Matematica + nota.Fisica + nota.Quimica + nota.Biologia + nota.Lenguaje) / 5.0;

            if (nota.Promedio >= 51.0)
            {
                strcpy(nota.Estado, "APROBADO");
            }
            else
            {
                strcpy(nota.Estado, "REPROBADO");
            }
            archivo.seekp(posicion);
            archivo.write((char*)&nota, sizeof(Notas_estudiante));

            cout << "\nNotas modificadas correctamente" << endl;
            cout << "Nuevo promedio: " << nota.Promedio << endl;

            break;  
        }
    }

    archivo.close();

    if (!encontrado)
    {
        cout << "No se encontró un estudiante con CI: " << CI_buscar << endl;
    }
}

#endif