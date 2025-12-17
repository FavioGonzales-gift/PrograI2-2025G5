#ifndef LIB_LISTADOCURSO_H
#define LIB_LISTADOCURSO_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Incluir estructuras necesarias de otros headers
// Asumiendo que estos headers definen las structs, los incluimos
#include "lib_CrearCurso.h"       // Para struct Curso
#include "lib_RegistroEstudiante.h" // Para struct Estudiante
#include "lib_Inscripcion.h"      // Para struct Inscripcion

using namespace std;

// Función auxiliar para obtener el nombre del estudiante por CI
string obtenerNombreEstudiante(int CI_estudiante, const string& Archivo_Registro_Estudiantes) {
    ifstream archivo(Archivo_Registro_Estudiantes, ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo de estudiantes." << endl;
        return "";
    }

    Estudiante student;
    while (archivo.read((char*)&student, sizeof(Estudiante))) {
        if (student.CI_estudiante == CI_estudiante) {
            archivo.close();
            return string(student.nombre_estudiante);
        }
    }
    archivo.close();
    return "Estudiante no encontrado";
}

// Función para listar estudiantes inscritos en un curso específico por código de curso
void listarEstudiantesPorCurso(int codigoCurso, const string& Archivo_Inscripcion, const string& Archivo_Registro_Estudiantes) {
    ifstream archivoInscrip(Archivo_Inscripcion, ios::binary);
    if (!archivoInscrip) {
        cout << "Error al abrir el archivo de inscripciones." << endl;
        return;
    }

    vector<int> estudiantesInscritos;
    Inscripcion ins;
    bool encontrado = false;
    while (archivoInscrip.read((char*)&ins, sizeof(Inscripcion))) {
        if (ins.codigoCurso == codigoCurso && ins.estado_inscripcion == 1) { // Asumiendo 1 = ACEPTADO
            estudiantesInscritos.push_back(ins.CI_estudiante);
            encontrado = true;
        }
    }
    archivoInscrip.close();

    if (!encontrado) {
        cout << "No hay estudiantes inscritos en este curso o el curso no existe." << endl;
        return;
    }

    cout << "Lista de estudiantes inscritos en el curso " << codigoCurso << ":" << endl;
    for (size_t i = 0; i < estudiantesInscritos.size(); ++i) {
        string nombre = obtenerNombreEstudiante(estudiantesInscritos[i], Archivo_Registro_Estudiantes);
        cout << i + 1 << ". " << nombre << " (CI: " << estudiantesInscritos[i] << ")" << endl;
    }
}

// Función para seleccionar curso por nivel y paralelo, y luego listar estudiantes
// Esto se puede llamar desde el menú con el subopción de nivel
void Seleccionar_curso(const string& Archivo_crear_curso, const string& Archivo_Inscripcion, const string& Archivo_Registro_Estudiantes, int nivelSeleccionado) {
    vector<string> paralelos = {"A", "B"};
    int paralelo;
    mostrar_vec(paralelos); // Reutilizando la función mostrar_vec de lib_CrearCurso.h
    cout << "\nIngrese el paralelo (1 para A, 2 para B): ";
    cin >> paralelo;

    if (paralelo < 1 || paralelo > 2) {
        cout << "Paralelo no válido." << endl;
        return;
    }

    // Buscar el código del curso basado en nivel y paralelo
    ifstream archivoCursos(Archivo_crear_curso, ios::binary);
    if (!archivoCursos) {
        cout << "Error al abrir el archivo de cursos." << endl;
        return;
    }

    Curso curso;
    int codigoCursoEncontrado = -1;
    while (archivoCursos.read((char*)&curso, sizeof(Curso))) {
        if (curso.nivel == nivelSeleccionado && curso.paralelo == paralelo) {
            codigoCursoEncontrado = curso.codigoCurso;
            break;
        }
    }
    archivoCursos.close();

    if (codigoCursoEncontrado == -1) {
        cout << "No se encontró un curso con el nivel y paralelo seleccionados." << endl;
        return;
    }

    // Ahora listar los estudiantes para ese código de curso
    listarEstudiantesPorCurso(codigoCursoEncontrado, Archivo_Inscripcion, Archivo_Registro_Estudiantes);
}

#endif