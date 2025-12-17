#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

struct Curso
{
    int codigoCurso;
    int nivel;
    int paralelo;
    int cupo_maximo;
    int cupos_disponibles;
    char profesor[200];
};

void mostrar_vec(vector<string>vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << i+1 << ". " << vec[i] << "\t";
    }
    cout << endl;
}

void Crear_curso(string Archivo_crear_curso)
{
    vector<string>nivel = {"4to de secundaria", "5to de secundaria", "6to de secundaria"};
    vector<string>paralelo = {"A", "B"};
    ofstream archivo;
    Curso aula;
    archivo.open(Archivo_crear_curso, ios::binary | ios::app);

    if (archivo.fail())
    {
        cout << "El archivo no se pudo abrir correctamente" << endl;
    }
    else
    {
        cout << "Ingrese el código del curso: ";
        cin >> aula.codigoCurso;

        mostrar_vec(nivel);
        cout << "\nIngrese el nivel (1,2,3): ";
        cin >> aula.nivel;

        mostrar_vec(paralelo);
        cout << "\nIngrese el paralelo (1,2): ";
        cin >> aula.paralelo;

        cout << "Ingrese el cupo máximo: ";
        cin >> aula.cupo_maximo;

        aula.cupos_disponibles = aula.cupo_maximo;

        cout << "Ingrese el nombre del profesor: " << endl;
        cin.getline(aula.profesor, 200);

        archivo.write((char *)&aula, sizeof(Curso));
        archivo.close();

        cout << "\nCurso creado correctamente" << endl;
    }
}