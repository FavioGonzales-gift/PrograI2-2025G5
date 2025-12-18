#ifndef LIB_MENUOPCIONES_H
#define LIB_MENUOPCIONES_H

#include <iostream>
#include <string>
#include "lib_RegistroEstudiante.h"
#include "lib_CrearCurso.h"
#include "lib_Inscripcion.h"
#include "lib_ListadoCurso.h"
#include "lib_Informacion_Curso.h"
#include "lib_RegistroNotas.h"
#include "lib_LibretaNotas.h"
#include "lib_Cuadro_Honor.h"

using namespace std;

void Menu(string Archivo_Registro_Estudiantes, string Archivo_crear_curso, string Archivo_Inscripcion, string Archivo_Registro_Notas, string Archivo_Inscritos_txt, string Archivo_Info_Cursos_txt, string Archivo_Cuadro_Honor_txt)
{
    int opcion;
    int subopcion;
    do
    {
        system("cls");
        cout<<"\t-----MENÚ DE OPCIONES-----"<<endl;
        cout<<"1. Crear curso"<<endl;
        cout<<"2. Registrar Estudiante"<<endl;
        cout<<"3. Ficha de Inscripción"<<endl;
        cout<<"4. Lista de estudiantes por curso"<<endl;
        cout<<"5. Información por curso"<<endl;
        cout<<"6. Registro de notas"<<endl;
        cout<<"7. Libreta escolar"<<endl;
        cout<<"8. Cuadro de honor"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Ingrese una opción del menú: ";
        cin >> opcion;
        switch (opcion)
        {
            case 1:
                system("cls");
                Crear_curso(Archivo_crear_curso);
                break;

            case 2:
                system("cls");
                registrarEstudiante(Archivo_Registro_Estudiantes);
                break;

            case 3:
                system("cls");
                cout << "1. Llenar inscripción" << endl;
                cout << "2. Modificar inscripción" << endl;
                cout << "3. Mostrar todas las inscripciones" << endl;
                cout << "0. Volver" << endl;
                cout << "Seleccione la opción: ";
                cin >> subopcion;
                switch (subopcion)
                {
                    case 1:
                        system("cls");
                        LlenarInscripcion(Archivo_Inscripcion, Archivo_crear_curso);
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        ModificarEstadoInscripcion(Archivo_Inscripcion, Archivo_crear_curso);
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        MostrarInscripciones(Archivo_Inscripcion, Archivo_Inscritos_txt);
                        system("pause");
                        break;
                    case 0:
                        break;
                    
                    default:
                        system("cls");
                        cout << "Opción no válida intente de nuevo..." << endl;
                        system("pause");
                        break;
                }
                break;

            case 4:
                system("cls");
                cout << "-----SELECCIONAR CURSO-----" << endl;
                cout << "1. Cuarto de secundaria" << endl;
                cout << "2. Quinto de secundaria" << endl;
                cout << "3. Sexto de secundaria" << endl;
                cout << "0. Volver" << endl;
                cout << "Seleccione la opción: ";
                cin >> subopcion;
                switch (subopcion)
                {
                    case 1:
                        Seleccionar_curso(Archivo_crear_curso, Archivo_Inscripcion, Archivo_Registro_Estudiantes, 1);
                        break;
                    case 2:
                        Seleccionar_curso(Archivo_crear_curso, Archivo_Inscripcion, Archivo_Registro_Estudiantes, 2);
                        break;
                    case 3:
                        Seleccionar_curso(Archivo_crear_curso, Archivo_Inscripcion, Archivo_Registro_Estudiantes, 3);
                        break;
                    case 0:
                        break;
                    
                    default:
                        cout << "Opción no válida intente de nuevo..." << endl;
                        break;
                }
                break;

            case 5:
                system("cls");
                Mostrar_Inf_Por_Curso(Archivo_crear_curso, Archivo_Info_Cursos_txt);
                system("pause");
                break;

            case 6:
                system("cls");
                cout << "\t---MENU---" << endl;
                cout << "1. Ingresar notas" << endl;
                cout << "2. Modificar notas" << endl;
                cout << "0. Volver" << endl;
                cout << "Ingrese una opcion: ";
                cin >> subopcion;
                switch (subopcion)
                {
                case 1:
                    system("cls");
                    Registrar_Nota(Archivo_Registro_Notas);
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    Modificar_Nota(Archivo_Registro_Notas);
                    system("pause");
                    break;
                case 0:
                    break;
                default:
                    break;
                }
                break;

            case 7:
                system("cls");
                MostrarLibretaEscolar(Archivo_Registro_Estudiantes, Archivo_Inscripcion, Archivo_crear_curso, Archivo_Registro_Notas);
                system("pause");
                break;

            case 8:
                system("cls");
                MostrarCuadroDeHonor(Archivo_crear_curso, Archivo_Inscripcion, Archivo_Registro_Estudiantes, Archivo_Registro_Notas, Archivo_Cuadro_Honor_txt);
                system("pause");
                break;

            case 0:
                system("cls");
                cout << "Saliendo..." << endl;
                break;
            
            default:
                cout << "Opción no válida, intente de nuevo" << endl;
                break;
        }
        cout << endl;
    } while (opcion!=0);
}

#endif