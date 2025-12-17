#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Curso
{
    int codigoCurso;
    int nivel;
    int paralelo;
    int cupo_maximo;
    int cupos_disponibles;
    char profesor[200];
};

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

void LlenarInscripcion (string Archivo_Inscripcion)
{
    vector<string>Estado = {"ACEPTADO", "RECHAZADO", "PENDIENTE"};
    ofstream archivo;
    Inscripcion Ins;
    archivo.open(Archivo_Inscripcion, ios::binary | ios::app);
    cout << "Ingrese el CI del estudiante: ";
    cin >> Ins.CI_estudiante;

    cout << "Ingrese el código del curso: ";
    cin >> Ins.codigoCurso;

    cout << "Ingrese la fecha de inscrpción: ";
    cin.getline(Ins.fecha_inscripcion, 11);

    mostrar_v(Estado);
    cout << "Estado de inscripción: ";
    cin >> Ins.estado_inscripcion;

    archivo.close();
}
