#include "Persona.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
Persona::Persona()
{
}

//Funcion que verifica si un cliente existe
bool Persona::verificaCliente(string cedula){

	ifstream cliente_in("clientes.txt");//Abrimos el archivo
	
	string  nombre, apellido, direccion, identificacion, nacionalidad, edad, clave;
	
	cliente_in>>nombre;//Leemos el primer campo de la primera linea
		
    while(!cliente_in.eof()){//Recorremos hasta que llegue no halla lineas
    	
    	cliente_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad;
    	
    	if(cedula == identificacion){
    		//Preguntamos si la cedula a buscar coincide con alguna que este en el archivo clientes.txt
    		return true;
		}
    	
    	nombre="";
    	cliente_in>>nombre;
	}
    return false;
}

Persona::~Persona()
{
}

