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
    string Archivo_Registro_Notas = "Registro_Notas_Estudiante.bin";
    string Archivo_Inscritos_txt = "Inscritos.txt";
    string Archivo_Info_Cursos_txt = "Informacion_Cursos.txt";
    string Archivo_Cuadro_Honor_txt = "Cuadro_Honor.txt";
    
    Menu(Archivo_Registro_Estudiantes, Archivo_crear_curso, Archivo_Inscripcion, Archivo_Registro_Notas, Archivo_Inscritos_txt, Archivo_Info_Cursos_txt, Archivo_Cuadro_Honor_txt);
    
    return 0;
}