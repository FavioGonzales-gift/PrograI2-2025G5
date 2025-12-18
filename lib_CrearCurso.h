#ifndef LIB_CREARCURSO_H
#define LIB_CREARCURSO_H

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

void mostrar_vec(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << i + 1 << ". " << vec[i] << "\t";
    }
    cout << endl;
}

void Crear_curso(string Archivo_crear_curso)
{
    vector<string> nivel_vec = {"4to de secundaria", "5to de secundaria", "6to de secundaria"};
    vector<string> paralelo_vec = {"A", "B"};

    Curso aula;

    cout << "Ingrese el código del curso: ";
    cin >> aula.codigoCurso;

    mostrar_vec(nivel_vec);
    cout << "\nIngrese el nivel (1,2,3): ";
    cin >> aula.nivel;

    if (aula.nivel < 1 || aula.nivel > 3)
    {
        cout << "\nNivel inválido" << endl;
        return;
    }

    mostrar_vec(paralelo_vec);
    cout << "\nIngrese el paralelo (1,2): ";
    cin >> aula.paralelo;

    if (aula.paralelo < 1 || aula.paralelo > 2)
    {
        cout << "\nParalelo inválido" << endl;
        return;
    }

    cout << "Ingrese el cupo máximo: ";
    cin >> aula.cupo_maximo;

    if (aula.cupo_maximo <= 0)
    {
        cout << "\nEl cupo máximo debe ser mayor que 0." << endl;
        return;
    }

    aula.cupos_disponibles = aula.cupo_maximo;

    cin.ignore();
    cout << "Ingrese el nombre del profesor: ";
    cin.getline(aula.profesor, 200);

    ifstream archivo;
    archivo.open(Archivo_crear_curso, ios::binary);
    if (archivo)
    {
        Curso cursoExistente;
        while (archivo.read((char*)&cursoExistente, sizeof(Curso)))
        {
            if (cursoExistente.nivel == aula.nivel && cursoExistente.paralelo == aula.paralelo)
            {
                cout << "\nYa existe un curso para " << nivel_vec[aula.nivel - 1] << " - Paralelo " << paralelo_vec[aula.paralelo - 1] << " (Código: " << cursoExistente.codigoCurso << ")" << endl;
                cout << "No se creo el curso" << endl;
                archivo.close();
                return;
            }
        }
        archivo.close();
    }

    ofstream archivoB;
    archivoB.open(Archivo_crear_curso, ios::binary | ios::app);
    if (archivoB)
    {
        archivoB.write((char*)&aula, sizeof(Curso));
        archivoB.close();
        cout << "\nCurso creado correctamente: " << nivel_vec[aula.nivel - 1] << " - Paralelo " << paralelo_vec[aula.paralelo - 1] << " - Código: " << aula.codigoCurso << endl;
    }
    else
    {
        cout << "\nError: No se pudo abrir el archivo para guardar el curso." << endl;
    }
}

#endif