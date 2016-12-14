#include "Persona.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
Persona::Persona()
{
}

// Funciones Settters -> para asignar valores a las variables de la clase
void Persona::setNombre(string nombre){
	this->nombre = nombre;
}
void Persona::setApellido(string apellido){
	this->apellido = apellido;
}
void Persona::setDireccion(string direccion){
	this->direccion = direccion;
}
void Persona::setidenificacion(string identificacion){
	this->identificacion = identificacion;
}
void Persona::setNacionalidad(string nacionalidad){
	this->nacionalidad = nacionalidad;
}
void Persona::setEdad(string edad){
	this->edad = edad;
}
void Persona::setSucursal(string sucursal){
	this->sucursal = sucursal;
}


// Funciones Gettters -> para retornar el valor de una variable de la clase
string Persona::getNombre(){
	return this->nombre;
}

bool Persona::verificaCliente(string cedula){

	ifstream cliente_in("clientes.txt");
	string  nombre, apellido, direccion, identificacion, nacionalidad, edad, clave;
	
	
	cliente_in>>nombre;
		
    while(!cliente_in.eof()){
    	
    	cliente_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad;
    	
    	if(cedula == identificacion){
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
