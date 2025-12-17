#ifndef LIB_INFORMACION_CURSO_H
#define LIB_INFORMACION_CURSO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lib_CrearCurso.h"  

using namespace std;

void Mostrar_Inf_Por_Curso(string Archivo_crear_curso, string Archivo_Txt_Salida = "Cupos_Por_Curso.txt")
{
    ifstream archivo_bin(Archivo_crear_curso, ios::binary);
    ofstream archivo_txt(Archivo_Txt_Salida);  

    if (!archivo_bin)
    {
        cout << "\nNo se pudo abrir el archivo binario de cursos.\n\n";
        system("pause");
        return;
    }

    if (!archivo_txt)
    {
        cout << "\nNo se pudo crear el archivo de texto de salida.\n\n";
        archivo_bin.close();
        system("pause");
        return;
    }

    Curso curso;
    bool hayCursos = false;

    vector<string> niveles = {"", "4to de secundaria", "5to de secundaria", "6to de secundaria"};
    vector<string> paralelos = {"", "A", "B"};

    system("cls");
    cout << "\n";
    cout << "\t\t--------------- LISTA DE CUPOS POR CURSO ---------------" << endl;
    cout << "CODIGO\tNIVEL\t\t\tPARALELO\tPROFESOR\t\t\tCUPO MAX.\tDISPONIBLES" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;

    archivo_txt << "=============== LISTA DE CUPOS POR CURSO ===============" << endl;
    archivo_txt << "CODIGO\tNIVEL\t\t\tPARALELO\tPROFESOR\t\t\tCUPO MAX.\tDISPONIBLES" << endl;
    archivo_txt << "------------------------------------------------------------------------------------------------------------------" << endl;

    while (archivo_bin.read((char*)&curso, sizeof(Curso)))
    {
        hayCursos = true;

        string nivel_str = (curso.nivel >= 1 && curso.nivel <= 3) ? niveles[curso.nivel] : "Desconocido";
        string paralelo_str = (curso.paralelo >= 1 && curso.paralelo <= 2) ? paralelos[curso.paralelo] : "Error";

        cout << curso.codigoCurso << "\t"
             << nivel_str << "\t\t"
             << paralelo_str << "\t\t"
             << curso.profesor << "\t"
             << curso.cupo_maximo << "\t\t"
             << curso.cupos_disponibles << endl;

        archivo_txt << curso.codigoCurso << "\t"
                    << nivel_str << "\t\t"
                    << paralelo_str << "\t\t"
                    << curso.profesor << "\t\t"
                    << curso.cupo_maximo << "\t\t"
                    << curso.cupos_disponibles << endl;
    }

    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
    archivo_txt << "------------------------------------------------------------------------------------------------------------------" << endl;

    if (!hayCursos)
    {
        cout << "No hay cursos registrados aún.\n";
        archivo_txt << "No hay cursos registrados aún." << endl;
    }
    else
    {
        cout << "\nReporte generado exitosamente en: " << Archivo_Txt_Salida << endl;
    }

    cout << "\n";
    system("pause");

    archivo_bin.close();
    archivo_txt.close();
}

#endif