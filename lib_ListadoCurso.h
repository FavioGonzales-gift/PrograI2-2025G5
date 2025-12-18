#ifndef LIB_LISTADOCURSO_H
#define LIB_LISTADOCURSO_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "lib_CrearCurso.h"      
#include "lib_RegistroEstudiante.h" 
#include "lib_Inscripcion.h"   

using namespace std;

string obtenerNombreEstudiante(int CI_estudiante, string Archivo_Registro_Estudiantes) 
{
    ifstream archivo;
    archivo.open(Archivo_Registro_Estudiantes, ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo de estudiantes." << endl;
        return "";
    }

    Estudiante student;
    while (archivo.read((char*)&student, sizeof(Estudiante))) 
    {
        if (student.CI_estudiante == CI_estudiante) 
        {
            archivo.close();
            return string(student.nombre_estudiante);
        }
    }
    archivo.close();
    return "Estudiante no encontrado";
}

void listarEstudiantesPorCurso(int codigoCurso, string Archivo_Inscripcion, string Archivo_Registro_Estudiantes) 
{
    ifstream archivoInscrip;
    archivoInscrip.open(Archivo_Inscripcion, ios::binary);
    if (!archivoInscrip) 
    {
        cout << "Error al abrir el archivo de inscripciones." << endl;
        return;
    }

    vector<int> estudiantesInscritos;
    Inscripcion ins;
    bool encontrado = false;
    while (archivoInscrip.read((char*)&ins, sizeof(Inscripcion))) 
    {
        if (ins.codigoCurso == codigoCurso && ins.estado_inscripcion == 1) 
        { 
            estudiantesInscritos.push_back(ins.CI_estudiante);
            encontrado = true;
        }
    }
    archivoInscrip.close();

    if (!encontrado) 
    {
        cout << "No hay estudiantes inscritos en este curso o el curso no existe." << endl;
        return;
    }

    system("cls");
    cout << "-----LISTA DE INSCRITOS EN EL  CURSO " << codigoCurso << "-----" << endl;
    cout << "No. \tCI \t\tNOMBRE" << endl;
    for (size_t i = 0; i < estudiantesInscritos.size(); ++i) 
    {
        string nombre = obtenerNombreEstudiante(estudiantesInscritos[i], Archivo_Registro_Estudiantes);
        cout << i + 1 << ". \t" << estudiantesInscritos[i] << " \t" << nombre << endl;
    }

    ofstream archivo_Lista_txt;
    archivo_Lista_txt.open("Lista_Curso" + to_string(codigoCurso) + ".txt");

    if (archivo_Lista_txt.is_open())
    {
        archivo_Lista_txt << "-----LISTA DE INSCRITOS EN EL CURSO " << codigoCurso << "-----" << endl;
        archivo_Lista_txt << "No. \tCI \t\tNOMBRE" << endl;

        for (size_t i = 0; i < estudiantesInscritos.size(); ++i)
        {
            string nombre = obtenerNombreEstudiante(estudiantesInscritos[i], Archivo_Registro_Estudiantes);
            archivo_Lista_txt << i + 1 << ". \t" << estudiantesInscritos[i] << " \t" << nombre << endl;
        }

        archivo_Lista_txt.close();
        cout << "\nLista guardada en txt" << endl;
    }
    else
    {
        cout << "\nNo se pudo crear el archivo de texto." << endl;
    }

    cout << endl;
    system("pause");
}

void Seleccionar_curso(string Archivo_crear_curso, string Archivo_Inscripcion, string Archivo_Registro_Estudiantes, int nivelSeleccionado) 
{
    vector<string> paralelos = {"A", "B"};
    int paralelo;
    mostrar_vec(paralelos); 
    cout << "\nIngrese el paralelo (1 para A, 2 para B): ";
    cin >> paralelo;

    if (paralelo < 1 || paralelo > 2) 
    {
        cout << "Paralelo no válido." << endl;
        return;
    }

    ifstream archivoCursos;
    archivoCursos.open(Archivo_crear_curso, ios::binary);
    if (!archivoCursos)
    {
        cout << "Error al abrir el archivo de cursos." << endl;
        return;
    }

    Curso curso;
    int codigoCursoEncontrado = -1;
    while (archivoCursos.read((char*)&curso, sizeof(Curso))) 
    {
        if (curso.nivel == nivelSeleccionado && curso.paralelo == paralelo) 
        {
            codigoCursoEncontrado = curso.codigoCurso;
            break;
        }
    }
    archivoCursos.close();

    if (codigoCursoEncontrado == -1) 
    {
        cout << "No se encontró un curso con el nivel y paralelo seleccionados." << endl;
        return;
    }

    listarEstudiantesPorCurso(codigoCursoEncontrado, Archivo_Inscripcion, Archivo_Registro_Estudiantes);
}

#endif