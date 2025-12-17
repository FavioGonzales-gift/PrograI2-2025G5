#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

struct fecha_nacimiento
{
    int dia;
    int mes;
    int anio;
};

struct Tutor
{
    char nombre_tutor[40];
    int edad_tutor;
    int CI_tutor;
    int telefono_tutor;
    char domicilio_tutor[70];
    int parentesco_tutor;
};

struct Estudiante
{
    char nombre_estudiante[40];
    int edad_estudiante;
    int CI_estudiante;
    char correo_electronico[45];
    Tutor tutor_estudiante;
    fecha_nacimiento nacimiento_estudiante;
};

void mostrar_vector(vector<string>vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << i+1 << ". " << vec[i] << "\t";
    }
}

void registrarEstudiante(string Archivo_Registro_Estudiantes)
{
    vector<string>Parentescos = {"Padre", "Madre", "Otro"};
    ofstream archivo;
    Estudiante student;
    archivo.open(Archivo_Registro_Estudiantes, ios::binary | ios::app);
    if (archivo.fail())
    {
        cout << "El archivo no se pudo abrir" << endl;
    }
    else
    {
        cin.ignore();
        cout << "Ingrese el nombre del estudiante: ";
        cin.getline(student.nombre_estudiante, 40);
        cout << "Ingrese la edad del estudiante: ";
        cin >> student.edad_estudiante;
        cout << "Ingrese el CI del estudiante: ";
        cin >> student.CI_estudiante;
        cin.ignore();
        cout << "Ingrese el correo electronico del estudiante: ";
        cin.getline(student.correo_electronico, 45);  

        cout << "-Datos del tutor-" << endl;  
        cout << "Ingrese el nombre del tutor: ";
        cin.getline(student.tutor_estudiante.nombre_tutor, 40);
        cout << "Ingrese la edad del tutor: ";
        cin >> student.tutor_estudiante.edad_tutor;
        cout << "Ingrese el CI del tutor: ";
        cin >> student.tutor_estudiante.CI_tutor;
        cout << "Ingrese el teléfono del tutor: ";
        cin >> student.tutor_estudiante.telefono_tutor;
        cin.ignore();   
        cout << "Ingrese el domicilio del tutor: ";
        cin.getline(student.tutor_estudiante.domicilio_tutor, 70);

        mostrar_vector(Parentescos);
        cout << "\nSeleccione la opción con el parentesco del tutor: ";
        cin >> student.tutor_estudiante.parentesco_tutor;

        cout << "Ingrese la fecha de nacimiento del estudiante (DD/MM/AA): ";
        cin >> student.nacimiento_estudiante.dia;
        cin >> student.nacimiento_estudiante.mes;
        cin >> student.nacimiento_estudiante.anio;

        archivo.write((char *)&student, sizeof(Estudiante));
        archivo.close();

        cout << "\nEstudiante registrado correctamente";
    }
}