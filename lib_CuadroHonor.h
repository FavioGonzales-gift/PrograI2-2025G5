// lib_CuadroHonor.h
#ifndef LIB_CUADROHONOR_H
#define LIB_CUADROHONOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "lib_RegistroEstudiante.h"
#include "lib_Inscripcion.h"
#include "lib_LibretaNotas.h"  // Para la estructura Notas_estudiante

using namespace std;

// Estructura para almacenar datos combinados para el cuadro de honor
struct EstudianteConNota {
    string nombre;
    int CI;
    double promedio;
    int codigoCurso;
};

void CuadroDeHonor(string Archivo_Inscripcion, string Archivo_Registro_Estudiantes, string Archivo_Notas) {
    system("cls");
    cout << "\t=== CUADRO DE HONOR - MEJORES 3 ESTUDIANTES POR CURSO ===\n\n";

    ifstream inscripciones(Archivo_Inscripcion, ios::binary);
    ifstream estudiantes(Archivo_Registro_Estudiantes, ios::binary);
    ifstream notas(Archivo_Notas, ios::binary);

    if (!inscripciones || !estudiantes || !notas) {
        cout << "Error: No se pudieron abrir uno o más archivos necesarios.\n";
        cout << "Asegúrese de haber creado cursos, registrado estudiantes, inscrito y registrado notas.\n";
        system("pause");
        return;
    }

    // Vectores para almacenar datos
    vector<Inscripcion> listaInscripciones;
    vector<Estudiante> listaEstudiantes;
    vector<Notas_estudiante> listaNotas;

    // Leer todos los datos
    Inscripcion ins;
    while (inscripciones.read((char*)&ins, sizeof(Inscripcion))) {
        if (ins.estado_inscripcion == 1) { // 1 = ACEPTADO (según tu vector: 1=ACEPTADO)
            listaInscripciones.push_back(ins);
        }
    }

    Estudiante est;
    while (estudiantes.read((char*)&est, sizeof(Estudiante))) {
        listaEstudiantes.push_back(est);
    }

    Notas_estudiante nota;
    while (notas.read((char*)&nota, sizeof(Notas_estudiante))) {
        listaNotas.push_back(nota);
    }

    inscripciones.close();
    estudiantes.close();
    notas.close();

    if (listaInscripciones.empty()) {
        cout << "No hay inscripciones aceptadas aún.\n";
        system("pause");
        return;
    }

    // Mapa: codigoCurso -> vector de estudiantes con nota
    vector<EstudianteConNota> porCurso[1000]; // Asumimos códigos de curso <1000

    for (const auto& insc : listaInscripciones) {
        if (insc.estado_inscripcion != 1) continue; // Solo aceptados

        // Buscar nombre del estudiante
        string nombre = "Desconocido";
        for (const auto& e : listaEstudiantes) {
            if (e.CI_estudiante == insc.CI_estudiante) {
                nombre = string(e.nombre_estudiante);
                break;
            }
        }

        // Buscar notas
        double promedio = 0.0;
        bool tieneNota = false;
        for (const auto& n : listaNotas) {
            if (n.CI_estudiante == insc.CI_estudiante) {
                promedio = n.Promedio;
                tieneNota = true;
                break;
            }
        }

        if (tieneNota) {
            EstudianteConNota ecn;
            ecn.nombre = nombre;
            ecn.CI = insc.CI_estudiante;
            ecn.promedio = promedio;
            ecn.codigoCurso = insc.codigoCurso;

            porCurso[insc.codigoCurso].push_back(ecn);
        }
    }

    // Ahora mostrar por cada curso que tenga estudiantes con notas
    bool hayDatos = false;
    for (int i = 0; i < 1000; i++) {
        if (porCurso[i].empty()) continue;

        hayDatos = true;

        // Ordenar descendente por promedio
        sort(porCurso[i].begin(), porCurso[i].end(), [](const EstudianteConNota& a, const EstudianteConNota& b) {
            return a.promedio > b.promedio;
        });

        // Extraer nivel y paralelo (asumiendo formato: nivel 4,5,6 y paralelo 1=A,2=B)
        int nivel = i / 10;  // Ej: código 41 -> 4to A
        int paraleloNum = i % 10;
        string paralelo = (paraleloNum == 1) ? "A" : "B";
        string nivelStr = (nivel == 4) ? "4to" : (nivel == 5 ? "5to" : "6to");

        cout << "CURSO: " << nivelStr << " de secundaria - Paralelo " << paralelo << " (Código: " << i << ")\n";
        cout << setw(5) << "Pos" << setw(15) << "CI" << setw(30) << "Nombre" << setw(12) << "Promedio" << endl;
        cout << string(62, '-') << endl;

        int limite = min(3, (int)porCurso[i].size());
        for (int j = 0; j < limite; j++) {
            cout << setw(3) << (j+1) << "º"
                 << setw(15) << porCurso[i][j].CI
                 << setw(30) << porCurso[i][j].nombre
                 << setw(10) << fixed << setprecision(2) << porCurso[i][j].promedio << endl;
        }

        if (limite == 0) {
            cout << "   No hay estudiantes con notas registradas.\n";
        }
        cout << endl;
    }

    if (!hayDatos) {
        cout << "No hay estudiantes con notas en cursos aceptados.\n";
    }

    cout << "\nPresione una tecla para volver al menú...";
    system("pause");
}

#endif