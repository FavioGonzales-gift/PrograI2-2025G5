#include <iostream>
#include <string>
#include "lib_RegistroEstudiante.h"
#include "lib_CrearCurso.h"
#include "lib_Inscripcion.h"

using namespace std;

void Menu(string Archivo_Registro_Estudiantes, string Archivo_crear_curso, string Archivo_Inscripcion)
{
    int opcion;
    int subopcion;
    do
    {
        cout<<"\t-----MENÚ DE OPCIONES-----"<<endl;
        cout<<"1. Crear curso"<<endl;
        cout<<"2. Registrar Estudiante"<<endl;
        cout<<"3. Ficha de Inscripción"<<endl;
        cout<<"4. Lista de estudiantes por curso"<<endl;
        cout<<"5. Lista de cupos por curso"<<endl;
        cout<<"6. Registro de notas"<<endl;
        cout<<"7. Libreta escolar"<<endl;
        cout<<"8. Cuadro de honor"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Ingrese una opción del menú: ";
        cin >> opcion;
        switch (opcion)
        {
            case 1:
                Crear_curso(Archivo_crear_curso);
                break;

            case 2:
                registrarEstudiante(Archivo_Registro_Estudiantes);
                break;

            case 3:
                cout << "1. Llenar inscripción" << endl;
                cout << "2. Mostrar inscrpción" << endl;
                cout << "0. Volver" << endl;
                cout << "Seleccione la opción: ";
                cin >> subopcion;
                break;

            case 4:
                cout << "-----SELECCIONAR CURSO-----" << endl;
                cout << "1. Cuarto de secundaria" << endl;
                cout << "2. Quinto de secundaria" << endl;
                cout << "3. Sexto de secundaria" << endl;
                cout << "0. Salir" << endl;
                cout << "Seleccione la opción: ";
                cin >> subopcion;
                switch (subopcion)
                {
                    case 1:
                        /* code */
                        break;
                    case 2:
                        /* code */
                        break;
                    case 3:
                        /* code */
                        break;
                    case 0:
                        /* code */
                        break;
                    
                    default:
                        cout << "Opción no válida intente de nuevo..." << endl;
                        break;
                }
                break;

            case 5:
                /* code */
                break;

            case 6:
                /* code */
                break;

            case 7:
                /* code */
                break;

            case 8:
                /* code */
                break;

            case 0:
                cout << "Saliendo..." << endl;
                break;
            
            default:
                cout << "Opción no válida, intente de nuevo" << endl;
                break;
        }
        cout << endl;
    } while (opcion!=0);
        
}