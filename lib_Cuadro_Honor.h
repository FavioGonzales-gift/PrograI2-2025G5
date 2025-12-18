#ifndef LIB_CUADRO_HONOR_H
#define LIB_CUADRO_HONOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "lib_CrearCurso.h"
#include "lib_Inscripcion.h"
#include "lib_RegistroEstudiante.h"
#include "lib_RegistroNotas.h"

using namespace std;

struct EstudiantePromedio 
{
    string nombre;
    int CI;
    double promedio;
};

void MostrarCuadroDeHonor(string Archivo_crear_curso, string Archivo_Inscripcion, string Archivo_Registro_Estudiantes, string Archivo_Registro_Notas, string Archivo_Cuadro_Honor_txt)
{
    ifstream archivoCursos;
    archivoCursos.open(Archivo_crear_curso, ios::binary);
    if (!archivoCursos) 
    {
        cout << "\nNo se pudo abrir el archivo\n";
        return;
    }

    ofstream archivo_txt;
    archivo_txt.open(Archivo_Cuadro_Honor_txt);
    if (!archivo_txt)
    {
        cout << "\nNo se pudo crear el archivo de texto.\n";
    }

    vector<string> niveles = {"4to de secundaria", "5to de secundaria", "6to de secundaria"};
    vector<string> paralelos = {"A", "B"};

    Curso curse;
    bool ExisteCurso = false;

    while (archivoCursos.read((char*)&curse, sizeof(Curso)))
    {
        ExisteCurso = true;

        string nivel;
        string paralelo;
        if (curse.nivel >= 1 && curse.nivel <= 3)
        {
            nivel = niveles[curse.nivel-1];
        }
        else
        {
            nivel = "Desconocido";
        }

        if (curse.paralelo >= 1 && curse.paralelo <= 2)
        {
            paralelo = paralelos[curse.paralelo-1];
        }
        else
        {
            paralelo = "Error";
        }

        cout << "CURSO: " << curse.codigoCurso << "   Nivel: " << nivel << "   Paralelo " << paralelo << endl;
        cout << endl;

        archivo_txt << "CURSO: " << curse.codigoCurso << "   Nivel: " << nivel << "   Paralelo " << paralelo << endl;
        archivo_txt << endl;

        vector<EstudiantePromedio> estudiantes;

        ifstream archivoInscrip;
        archivoInscrip.open(Archivo_Inscripcion, ios::binary);
        if (archivoInscrip)
        {
            Inscripcion ins;
            while (archivoInscrip.read((char*)&ins, sizeof(Inscripcion)))
            {
                if (ins.codigoCurso == curse.codigoCurso && ins.estado_inscripcion == 1)
                {
                    int ci = ins.CI_estudiante;

                    string nombre = "Desconocido";
                    ifstream archivoEst;
                    archivoEst.open(Archivo_Registro_Estudiantes, ios::binary);
                    if (archivoEst)
                    {
                        Estudiante est;
                        while (archivoEst.read((char*)&est, sizeof(Estudiante)))
                        {
                            if (est.CI_estudiante == ci)
                            {
                                nombre = string(est.nombre_estudiante);
                                break;
                            }
                        }
                        archivoEst.close();
                    }

                    double promedio = 0.0;
                    bool tieneNotas = false;
                    ifstream archivoNotas;
                    archivoNotas.open(Archivo_Registro_Notas, ios::binary);
                    if (archivoNotas)
                    {
                        Notas_estudiante nota;
                        while (archivoNotas.read((char*)&nota, sizeof(Notas_estudiante)))
                        {
                            if (nota.CI_estudiante == ci)
                            {
                                promedio = nota.Promedio;
                                tieneNotas = true;
                                break;
                            }
                        }
                        archivoNotas.close();
                    }

                    if (tieneNotas)
                    {
                        estudiantes.push_back({nombre, ci, promedio});
                    }
                }
            }
            archivoInscrip.close();
        }

        if (estudiantes.size() == 0)
        {
            cout << "   No hay estudiantes con notas registradas en este curso.\n";
            continue;
        }

        for (int i = 0; i < estudiantes.size() - 1 && i < 3; i++)
        {
            for (int j = i + 1; j < estudiantes.size() && j < 3; j++)
            {
                if (estudiantes[i].promedio < estudiantes[j].promedio)
                {
                    EstudiantePromedio temp = estudiantes[i];
                    estudiantes[i] = estudiantes[j];
                    estudiantes[j] = temp;
                }
            }
        }

        int limite;
        if (estudiantes.size() < 3)
        {
            limite = estudiantes.size();
        }
        else
        {
            limite = 3;
        }
        cout << "\t------------------------CUADRO DE HONOR------------------------" << endl;
        cout << "******************************************************************************" << endl;
        cout << "Posición \tCI \t\tNombre \t\t\t\tPromedio" << endl;
        cout << "------------------------------------------------------------------------------" << endl;

        archivo_txt << "\t------------------------CUADRO DE HONOR------------------------" << endl;
        archivo_txt << "******************************************************************************" << endl;
        archivo_txt << "Posición \tCI \t\tNombre \t\t\t\tPromedio" << endl;
        archivo_txt << "------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < limite; i++)
        {
            cout << (i+1) << "° lugar \t" << estudiantes[i].CI << "\t"<< estudiantes[i].nombre << "\t" << (int)(estudiantes[i].promedio + 0.5) << endl;

            archivo_txt << (i+1) << "° lugar \t" << estudiantes[i].CI << "\t"<< estudiantes[i].nombre << "\t" << (int)(estudiantes[i].promedio + 0.5) << endl;
        }

        cout << endl;
        archivo_txt << endl;
    }

    archivoCursos.close();

    if (!ExisteCurso)
    {
        cout << "   No hay cursos registrados.\n";
    }
    if (archivo_txt)
    {
        cout << "\nCuadro de honor guardado en txt" << endl;
    }
    
}

#endif