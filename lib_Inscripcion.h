#ifndef LIB_INSCRIPCION_H
#define LIB_INSCRIPCION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "lib_CrearCurso.h"

struct Inscripcion
{
    int CI_estudiante;
    int codigoCurso;
    char fecha_inscripcion[11];  
    int estado_inscripcion; // aceptado rechazado pendiente    
};

using namespace std;

void mostrar_v(vector<string>vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << i+1 << ". " << vec[i] << "\t";
    }
    cout << endl;
}

string paralelos(int paralelo)
{
    return (paralelo == 1) ? "A" : "B";
}

void LlenarInscripcion(string Archivo_Inscripcion, string Archivo_crear_curso)
{
    vector<string> Estado = {"ACEPTADO", "RECHAZADO", "PENDIENTE"};

    ofstream archivo(Archivo_Inscripcion, ios::binary | ios::app);
    
    if (!archivo.is_open() || archivo.fail())
    {
        cout << "Error crítico: No se pudo abrir el archivo de inscripciones para escribir." << endl;
        return;
    }

    Inscripcion Ins;
    
    cout << "Ingrese el CI del estudiante: ";
    cin >> Ins.CI_estudiante;

    cout << "Ingrese el código del curso: ";
    cin >> Ins.codigoCurso;

    cin.ignore(); 
    cout << "Ingrese la fecha de inscripción (DD/MM/AAAA): ";
    cin.getline(Ins.fecha_inscripcion, 11);

    mostrar_v(Estado);
    cout << "Estado de inscripción (1=ACEPTADO, 2=RECHAZADO, 3=PENDIENTE): ";
    cin >> Ins.estado_inscripcion;

    archivo.write((char*)&Ins, sizeof(Inscripcion));
    
    if (archivo.good())
    {
        cout << "Inscripción guardada correctamente." << endl;
    }
    else
    {
        cout << "Error al guardar la inscripción en el archivo." << endl;
    }

    archivo.close();

    if (Ins.estado_inscripcion == 1)
    {
        fstream archivoCursos(Archivo_crear_curso, ios::binary | ios::in | ios::out);
        if (!archivoCursos)
        {
            cout << "Advertencia: No se pudo actualizar cupos (archivo de cursos no accesible)." << endl;
            return;
        }

        bool encontrado = false;
        Curso curso;
        streampos pos = 0;

        while (archivoCursos.read((char*)&curso, sizeof(Curso)))
        {
            if (curso.codigoCurso == Ins.codigoCurso)
            {
                encontrado = true;
                if (curso.cupos_disponibles > 0)
                {
                    curso.cupos_disponibles--;
                    archivoCursos.seekp(pos);
                    archivoCursos.write((char*)&curso, sizeof(Curso));
                    cout << "Cupo reducido. Quedan: " << curso.cupos_disponibles << " plazas." << endl;
                }
                else
                {
                    cout << "No hay cupos disponibles." << endl;
                }
                break;
            }
            pos = archivoCursos.tellg();
        }
        archivoCursos.close();

        if (!encontrado)
            cout << "Curso no encontrado. Cupo no modificado." << endl;
    }
}

void ModificarEstadoInscripcion(string Archivo_Inscripcion, string Archivo_crear_curso)
{
    int CI_buscar;
    cout << "Ingrese el CI del estudiante cuya inscripción quiere modificar: ";
    cin >> CI_buscar;

    fstream archivoIns(Archivo_Inscripcion, ios::binary | ios::in | ios::out);
    if (!archivoIns)
    {
        cout << "Error al abrir el archivo de inscripciones." << endl;
        return;
    }

    vector<string> Estado = {"ACEPTADO", "RECHAZADO", "PENDIENTE"};
    Inscripcion ins;
    bool encontrado = false;
    streampos pos = 0;

    while (archivoIns.read((char*)&ins, sizeof(Inscripcion)))
    {
        // Guardar posición actual antes de avanzar
        pos = archivoIns.tellg() - sizeof(Inscripcion);

        cout << "Leyendo registro: CI " << ins.CI_estudiante 
             << " | Curso: " << ins.codigoCurso 
             << " | Estado: " << Estado[ins.estado_inscripcion - 1] << endl;

        if (ins.CI_estudiante == CI_buscar)
        {
            encontrado = true;

            cout << "\nInscripción encontrada:" << endl;
            cout << "CI: " << ins.CI_estudiante << endl;
            cout << "Código Curso: " << ins.codigoCurso << endl;
            cout << "Fecha: " << ins.fecha_inscripcion << endl;
            cout << "Estado actual: " << Estado[ins.estado_inscripcion - 1] << endl << endl;

            mostrar_v(Estado);
            cout << "Ingrese nuevo estado (1=ACEPTADO, 2=RECHAZADO, 3=PENDIENTE): ";
            int nuevo_estado;
            cin >> nuevo_estado;

            if (nuevo_estado < 1 || nuevo_estado > 3)
            {
                cout << "Opción inválida. No se modificó." << endl;
                archivoIns.close();
                return;
            }

            bool fue_pendiente_a_aceptado = (ins.estado_inscripcion == 3 && nuevo_estado == 1);

            // Actualizar estado
            ins.estado_inscripcion = nuevo_estado;

            // Volver a la posición guardada y sobrescribir
            archivoIns.seekp(pos);
            archivoIns.write((char*)&ins, sizeof(Inscripcion));

            // Volver a posición de lectura para continuar correctamente
            archivoIns.seekg(pos + sizeof(Inscripcion));

            cout << "Estado actualizado a: " << Estado[nuevo_estado - 1] << endl;

            // === REDUCIR CUPO SI PASÓ DE PENDIENTE A ACEPTADO ===
            if (fue_pendiente_a_aceptado)
            {
                // (Código de reducción de cupo que ya tienes, con mensajes de depuración si quieres)
                fstream archivoCursos(Archivo_crear_curso, ios::binary | ios::in | ios::out);
                if (archivoCursos)
                {
                    Curso curso;
                    streampos posCurso = 0;
                    bool curso_encontrado = false;

                    while (archivoCursos.read((char*)&curso, sizeof(Curso)))
                    {
                        posCurso = archivoCursos.tellg() - sizeof(Curso);

                        if (curso.codigoCurso == ins.codigoCurso)
                        {
                            curso_encontrado = true;
                            if (curso.cupos_disponibles > 0)
                            {
                                curso.cupos_disponibles--;
                                archivoCursos.seekp(posCurso);
                                archivoCursos.write((char*)&curso, sizeof(Curso));
                                cout << "Cupo reducido. Quedan: " << curso.cupos_disponibles << " plazas." << endl;
                            }
                            else
                            {
                                cout << "No hay cupos disponibles." << endl;
                            }
                            break;
                        }
                    }
                    archivoCursos.close();
                    if (!curso_encontrado) cout << "Curso no encontrado para reducir cupo." << endl;
                }
                else
                {
                    cout << "No se pudo abrir archivo de cursos para reducir cupo." << endl;
                }
            }

            // Puedes agregar break; si solo quieres modificar la primera coincidencia
            // O quitarlo si un estudiante puede tener múltiples inscripciones
        }
    }

    archivoIns.close();

    if (!encontrado)
    {
        cout << "No se encontró ninguna inscripción con el CI " << CI_buscar << "." << endl;
    }
}


void MostrarInscripciones(const string& Archivo_Inscripcion, const string& Archivo_Txt_Salida = "Lista_Inscripciones.txt")
{
    ifstream archivo_bin(Archivo_Inscripcion, ios::binary);
    ofstream archivo_txt(Archivo_Txt_Salida);

    if (!archivo_bin)
    {
        cout << "Error: No se pudo abrir el archivo binario de inscripciones.\n";
        system("pause");
        return;
    }

    if (!archivo_txt)
    {
        cout << "Error: No se pudo crear el archivo de texto de salida.\n";
        archivo_bin.close();
        system("pause");
        return;
    }

    Inscripcion ins;
    vector<string> Estados = {"", "ACEPTADO", "RECHAZADO", "PENDIENTE"};  // índice 1,2,3
    bool hayInscripciones = false;

    system("cls");
    cout << "\n\t\t===== LISTA COMPLETA DE INSCRIPCIONES =====\n\n";

    cout << left 
         << setw(15) << "CI ESTUDIANTE"
         << setw(15) << "CÓDIGO CURSO"
         << setw(15) << "FECHA"
         << setw(15) << "ESTADO" << endl;
    cout << string(60, '-') << endl;

    archivo_txt << "===== LISTA COMPLETA DE INSCRIPCIONES =====\n\n";
    archivo_txt << left
                << setw(15) << "CI ESTUDIANTE"
                << setw(15) << "CODIGO CURSO"
                << setw(15) << "FECHA"
                << setw(15) << "ESTADO" << endl;
    archivo_txt << string(60, '-') << endl;

    while (archivo_bin.read((char*)&ins, sizeof(Inscripcion)))
    {
        hayInscripciones = true;

        string estado_str = (ins.estado_inscripcion >= 1 && ins.estado_inscripcion <= 3)
                            ? Estados[ins.estado_inscripcion]
                            : "DESCONOCIDO";

        cout << left
             << setw(15) << ins.CI_estudiante
             << setw(15) << ins.codigoCurso
             << setw(15) << ins.fecha_inscripcion
             << setw(15) << estado_str << endl;

        archivo_txt << left
                    << setw(15) << ins.CI_estudiante
                    << setw(15) << ins.codigoCurso
                    << setw(15) << ins.fecha_inscripcion
                    << setw(15) << estado_str << endl;
    }

    cout << string(60, '-') << endl;
    archivo_txt << string(60, '-') << endl;

    if (!hayInscripciones)
    {
        cout << "No hay inscripciones registradas en el sistema.\n";
        archivo_txt << "No hay inscripciones registradas en el sistema.\n";
    }
    else
    {
        cout << "Total de inscripciones encontradas: " 
             << (archivo_bin ? "varias" : "0") << endl;  // Mejor contar antes, pero simplificado
        cout << "\nReporte guardado exitosamente en: " << Archivo_Txt_Salida << endl;
    }

    cout << "\n";
    system("pause");

    archivo_bin.close();
    archivo_txt.close();
}

#endif