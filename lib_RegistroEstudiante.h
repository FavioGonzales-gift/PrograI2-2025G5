#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

struct Estudiante
{
    char nombre_estudiante[40];
    int edad_estudiante;
    int CI_estudiante;
    char correo_electronico[45];
    Tutor tutor_estudiante;
    fecha_nacimiento nacimiento_estudiante;
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

struct fecha_nacimiento
{
    int dia;
    int mes;
    int anio;
};

Estudiante registrarEstudiante()
{
    ifstream archivo;
    Estudiante student;
    archivo.open("RegistroEstudiantes.bin", ios::binary | ios::app);
    
    cout << "Ingrese el nombre del estudiante: ";
    cin.getline(student.nombre_estudiante, 40);
    cout << "Ingrese la edad del estudiante: ";
    cin >> student.edad_estudiante;
    cout << "Ingrese el CI del estudiante: ";
    cin >> student.CI_estudiante;   
    cin.ignore();
    cout << "Ingrese el correo electronico del estudiante: ";
    cin.getline(student.correo_electronico, 45);    
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
    cout << "Ingrese el parentesco del tutor: ";
}