#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include "lib_MenuOpciones.h"

using namespace std;

int main()
{
    system("chcp 65001");
    string Archivo_crear_curso = "Crear_Curso.bin";
    string Archivo_Registro_Estudiantes = "Registro_Estudiantes.bin";
    string Archivo_Inscripcion = "Inscripcion.bin";

    Menu(Archivo_Registro_Estudiantes, Archivo_crear_curso, Archivo_Inscripcion);
    
    return 0;
}

