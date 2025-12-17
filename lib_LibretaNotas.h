#ifndef LIB_LIBRETANOTAS_H
#define LIB_LIBRETANOTAS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lib_RegistroEstudiante.h"
#include "lib_Inscripcion.h"
#include "lib_CrearCurso.h"
#include "lib_RegistroNotas.h"

using namespace std;

void MostrarLibretaEscolar(string Archivo_Registro_Estudiantes, 
                           string Archivo_Inscripcion, 
                           string Archivo_crear_curso, 
                           string Archivo_Registro_Notas)
{
    int CI_buscar;
    cout << "Ingrese el CI del estudiante para ver su libreta: ";
    cin >> CI_buscar;

    bool encontrado = false;

    ifstream archivoEstudiantes;
    archivoEstudiantes.open(Archivo_Registro_Estudiantes, ios::binary);
    Estudiante student;
    string nombre_estudiante = "";
    int edad_estudiante = 0;

    if (archivoEstudiantes)
    {
        while (archivoEstudiantes.read((char*)&student, sizeof(Estudiante)))
        {
            if (student.CI_estudiante == CI_buscar)
            {
                nombre_estudiante = string(student.nombre_estudiante);
                encontrado = true;
                break;
            }
        }
        archivoEstudiantes.close();
    }

    if (!encontrado)
    {
        cout << "\nNo se encontró al estudiante "<< endl;
        return;
    }

    ifstream archivoInscrip;
    archivoInscrip.open(Archivo_Inscripcion, ios::binary);
    Inscripcion ins;
    int codigoCurso = -1;
    encontrado = false;

    if (archivoInscrip)
    {
        while (archivoInscrip.read((char*)&ins, sizeof(Inscripcion)))
        {
            if (ins.CI_estudiante == CI_buscar && ins.estado_inscripcion == 1)
            {
                codigoCurso = ins.codigoCurso;
                encontrado = true;
                break;
            }
        }
        archivoInscrip.close();
    }

    if (!encontrado)
    {
        cout << "\nEl estudiante no está inscrito o su inscripción no está ACEPTADA." << endl << endl;
        return;
    }

    ifstream archivoCursos;
    archivoCursos.open(Archivo_crear_curso, ios::binary);
    Curso curso;
    string nivel = "Desconocido";
    string paralelo= "Error";
    vector<string> niveles = {"4to de secundaria", "5to de secundaria", "6to de secundaria"};
    vector<string> paralelos = {"A", "B"};

    if (archivoCursos)
    {
        while (archivoCursos.read((char*)&curso, sizeof(Curso)))
        {
            if (curso.codigoCurso == codigoCurso)
            {
                if (curso.nivel >= 1 && curso.nivel <= 3)
                {
                    nivel = niveles[curso.nivel-1];
                }
                if (curso.paralelo >= 1 && curso.paralelo <= 2)
                {
                    paralelo = paralelos[curso.paralelo-1];
                }
                break;
            }
        }
        archivoCursos.close();
    }

    ifstream archivoNotas;
    archivoNotas.open(Archivo_Registro_Notas, ios::binary);
    Notas_estudiante notas;
    bool notasEncontradas = false;
    double matematica = 0, fisica = 0, quimica = 0, biologia = 0, lenguaje = 0, promedio = 0;
    string estado = "Sin notas";

    if (archivoNotas)
    {
        while (archivoNotas.read((char*)&notas, sizeof(Notas_estudiante)))
        {
            if (notas.CI_estudiante == CI_buscar)
            {
                matematica = notas.Matematica;
                fisica = notas.Fisica;
                quimica = notas.Quimica;
                biologia = notas.Biologia;
                lenguaje = notas.Lenguaje;
                promedio = notas.Promedio;
                estado = string(notas.Estado);
                notasEncontradas = true;
                break;
            }
        }
        archivoNotas.close();
    }

    if (!notasEncontradas)
    {
        cout << "\nNo se encontraron notas registradas para este estudiante." << endl << endl;
        return;
    }

    cout << endl;
    cout << "\t\t*****************************************************************" << endl;
    cout << "\t\t LIBRETA ESCOLAR" << endl;
    cout << "\t\t*****************************************************************" << endl;
    cout << "Nombre: " << nombre_estudiante << "\tCI: " << CI_buscar << endl;
    cout << "Curso: " << codigoCurso << "\tNivel: " << nivel << "\tParalelo " << paralelo << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << " CALIFICACIONES" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Matemáticas : " << matematica << endl;
    cout << "Física : " << fisica << endl;
    cout << "Química : " << quimica << endl;
    cout << "Biología : " << biologia << endl;
    cout << "Lenguaje : " << lenguaje << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Promedio final : " << promedio << endl;
    cout << "Estado : " << estado << endl;
    cout << endl;

    ofstream archivo_txt("Libreta_" + to_string(CI_buscar) + ".txt");

    if (archivo_txt.is_open())
    {
        archivo_txt << "\t\t*****************************************************************\n";
        archivo_txt << "\t\t LIBRETA ESCOLAR\n";
        archivo_txt << "\t\t*****************************************************************\n\n";
        archivo_txt << "Nombre: " << nombre_estudiante << "\tCI: " << CI_buscar << "\n";
        archivo_txt << "Curso: " << codigoCurso << "\tNivel: " << nivel << "\tParalelo " << paralelo << "\n";
        archivo_txt << "-----------------------------------------------------------------\n";
        archivo_txt << " CALIFICACIONES\n";
        archivo_txt << "-----------------------------------------------------------------\n";
        archivo_txt << "Matemáticas : " << matematica << "\n";
        archivo_txt << "Física : " << fisica << "\n";
        archivo_txt << "Química : " << quimica << "\n";
        archivo_txt << "Biología : " << biologia << "\n";
        archivo_txt << "Lenguaje : " << lenguaje << "\n";
        archivo_txt << "-----------------------------------------------------------------\n";
        archivo_txt << "Promedio final : " << promedio << "\n";
        archivo_txt << "Estado : " << estado << "\n\n";

        archivo_txt.close();
        cout << "Libreta escolar guardada en: Libreta_" << CI_buscar << ".txt\n\n";
    }
    else
    {
        cout << "No se pudo crear el archivo de texto.\n\n";
    }

    system("pause");
}

#endif