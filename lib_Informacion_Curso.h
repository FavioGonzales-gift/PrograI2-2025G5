#ifndef LIB_INFORMACION_CURSO_H
#define LIB_INFORMACION_CURSO_H

#include <iostream>
#include <fstream>
#include <string>
#include "lib_CrearCurso.h"

using namespace std;

void Mostrar_Inf_Por_Curso(string Archivo_crear_curso, string Archivo_Info_Cursos_txt)
{
    ifstream archivo;
    archivo.open(Archivo_crear_curso, ios::binary);
    ofstream archivo_txt;
    archivo_txt.open(Archivo_Info_Cursos_txt);
    
    if (!archivo)
    {
        cout << "\nNo se pudo abrir el archivo.\n\n";
        return;
    }

    Curso curso;
    bool hayCursos = false;

    cout << endl;
    cout << "\t\t---------------LISTA DE CUPOS POR CURSO---------------" << endl;
    cout << "CÓDIGO\tNIVEL\t\t\tPARALELO\tPROFESOR\tCUPO MÁX.\tDISPONIBLES" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;

    archivo_txt << "\t\t---------------LISTA DE CUPOS POR CURSO---------------" << endl;
    archivo_txt << "CÓDIGO\tNIVEL\t\t\tPARALELO\tPROFESOR\tCUPO MÁX.\tDISPONIBLES" << endl;
    archivo_txt << "-------------------------------------------------------------------------------------------------------------" << endl;

    vector<string> niveles = {"", "4to de secundaria", "5to de secundaria", "6to de secundaria"};
    vector<string> paralelos = {"", "A", "B"};

    while (archivo.read((char*)&curso, sizeof(Curso)))
    {
        hayCursos = true;

        string nivel;
        string paralelo;
        if (curso.nivel >= 1 && curso.nivel <= 3)
        {
            nivel = niveles[curso.nivel];
        }
        else
        {
            nivel = "Desconocido";
        }
        if (curso.paralelo >= 1 && curso.paralelo <= 2)
        {
            paralelo = paralelos[curso.paralelo];
        }
        else
        {
            paralelo = "Error";
        }

        cout << curso.codigoCurso << "\t" << nivel << "\t" << paralelo << "\t\t" << curso.profesor << "\t" << curso.cupo_maximo << "\t\t" << curso.cupos_disponibles << endl;
        archivo_txt << curso.codigoCurso << "\t" << nivel << "\t" << paralelo << "\t\t" << curso.profesor << "\t" << curso.cupo_maximo << "\t\t" << curso.cupos_disponibles << endl;
    }

    archivo.close();
    archivo_txt.close();

    if (!hayCursos)
    {
        cout << "No hay cursos registrados.\n";
    }
     else
    {
        cout << "\nReporte generado exitosamente" << endl;
    }

}

#endif