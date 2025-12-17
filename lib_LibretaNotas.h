#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Notas_estudiante
{
    int CI_estudiante;;
    double Matematica;
    double Fisica;
    double Quimica;
    double Biologia;
    double Lenguaje;
    double Promedio;
    char Estado[15];
};

void Menu_opciones(string ArchivoBin, string ArchivoTxt);
void Registrar_Nota(string ArchivoBin, string ArchivoTxt);
void Lista_notas(string ArchivoBin, string ArchivoTxt);
void Eliminar_estudiante(string ArchivoBin);

int main()
{
    system("chcp 65001");
    string ArchivoBin = "Notas_Estudiante.bin";
    string ArchivoTxt = "Notas_Estudiante.txt";
    Menu_opciones(ArchivoBin, ArchivoTxt);
    return 0;
}

void Menu_opciones(string ArchivoBin, string ArchivoTxt)
{
    int opcion = 0;
    do
    {
        system("cls");
        cout << "\t---MENU---" << endl;
        cout << "1. Ingresar notas" << endl;
        cout << "2. Listar notas" << endl;
        cout << "3. Eliminar nota" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
            case 1:
                system("cls");
                Registrar_Nota(ArchivoBin, ArchivoTxt);
                system("pause");
                break;
            case 2:
                system("cls");
                Lista_notas(ArchivoBin, ArchivoTxt);
                system("pause");
                break;
            case 3:
                system("cls");
                Eliminar_estudiante(ArchivoBin);
                break;
            case 0:
                system("cls");
                cout << "Saliendo...";
                break;
            
            default:
                system("cls");
                cout << "Opcion no valida, intente de nuevo" << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
    
}

void Registrar_Nota(string ArchivoBin, string ArchivoTxt)
{
    Notas_estudiante nota;

    ofstream binario(ArchivoBin, ios::binary | ios::app);
    ofstream texto(ArchivoTxt, ios::app);

    if (!binario || !texto)
    {
        cout << "Error al abrir archivos\n";
        return;
    }

    cout << "Ingrese el nombre del estudiante: ";
    cin >> nota.CI_estudiante;

    cout << "Ingrese la nota de Matemáticas: ";
    cin >> nota.Matematica;

    cout << "Ingrese la nota de Física: ";
    cin >> nota.Fisica;

    cout << "Ingrese la nota de Química: ";
    cin >> nota.Quimica;

    cout << "Ingrese la nota de Biología: ";
    cin >> nota.Biologia;

    cout << "Ingrese la nota de Lenguaje: ";
    cin >> nota.Lenguaje;

    nota.Promedio = (nota.Matematica + nota.Fisica + nota.Quimica + nota.Biologia + nota.Lenguaje) / 5;
    
    if (nota.Promedio < 51)
    {
        strcpy(nota.Estado, "REPROBADO");
    }
    
    if (nota.Promedio >= 51 && nota.Promedio <= 100);
    {
        strcpy(nota.Estado, "APROBADO");
    }
    
    binario.write((char*)&nota, sizeof(Notas_estudiante));

    texto << nota.CI_estudiante << " ";
    texto << nota.Matematica << " ";
    texto << nota.Fisica << " ";
    texto << nota.Quimica << " ";
    texto << nota.Promedio << " ";
    texto << nota.Estado << endl;
    
    binario.close();
    texto.close();
    
}

void Lista_notas(string ArchivoBin, string ArchivoTxt)
{
    Notas_estudiante nota;
    ifstream binario(ArchivoBin, ios::binary);
    ofstream texto(ArchivoTxt); 

    if (!binario || !texto)
    {
        cout << "Error al abrir archivos" << endl;
        return;
    }

    cout << "CI\tMAT\tFIS\tQUI\tBIO\tLEN\tPROM\tESTADO\n";

    while (binario.read((char*)&nota, sizeof(Notas_estudiante)))
    {
        cout << nota.CI_estudiante << "\t";
        cout << nota.Matematica << "\t";
        cout << nota.Fisica << "\t";
        cout << nota.Quimica << "\t";
        cout << nota.Biologia << "\t";
        cout << nota.Lenguaje << "\t";
        cout << nota.Promedio << "\t";
        cout << nota.Estado << endl;

        texto << nota.CI_estudiante << " ";
        texto << nota.Matematica << " ";
        texto << nota.Fisica << " ";
        texto << nota.Quimica << " ";
        texto << nota.Biologia << " ";
        texto << nota.Lenguaje << " ";
        texto << nota.Promedio << " ";
        texto << nota.Estado << endl;
    }

    binario.close();
    texto.close();
}

void Eliminar_estudiante(string ArchivoBin)
{
    int ci;
    Notas_estudiante nota;
    fstream archivo;
    archivo.open(ArchivoBin,ios::binary|ios::app);
    if (archivo.good())
    {
        cout << "Ingrese el CI del estudiante a elminar: ";
        cin >> nota.CI_estudiante;
        while (archivo.read((char*)&nota, sizeof(Notas_estudiante)))
        {
            if (nota.CI_estudiante == ci)
            {
                archivo.seekp(-sizeof(Notas_estudiante), ios::cur);
            }
        }
    }
    else
    {
        cout << "Archivo no encontrado" << endl;
    }
    
    archivo.close();
}