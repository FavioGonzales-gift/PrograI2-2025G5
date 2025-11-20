#include <iostream>
#include "lib_Belen.h"
#include "lib_Favio.h"
using namespace std;

int main()
{
    system("chcp 65001");
    cout<<"El resultado de la suma es: "<<sumar(4,5)<<endl;
    cout<<"El resultado del producto es: "<< producto(3,2)<<endl;
    cout<<"El resultado de la división es: "<< division(8,4)<<endl;
    return 0;
}

