#include <iostream>
#include <string>
#include <string.h>
#include <vector>
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

struct Curso
{
    int codigoCurso;
    int nivel;
    int paralelo;
    int cupo_maximo;
    int cupos_disponibles;
    char profesor[200];
};

struct Notas_registro
{
    int CI_estudiante;
    int codigoGrado;
    double nota_matematicas;
    double nota_biologia;
    double nota_quimica;
    double nota_fisica;
    double nota_lenguaje;
    double promedio_final;
};

struct Inscripcion
{
    int CI_estudiante;
    int codigoCurso;
    char fecha_inscripcion[11];  
    int estado_inscripcion; // aceptado rechazado pendiente    
};

int main()
{
    system("chcp 65001");
    string Nombre_Archivo = "RegistroEstudiantes.bin";
    vector<string>Parentescos = {"Padre", "Madre", "Otro"};
    return 0;
}

