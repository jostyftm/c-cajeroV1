#ifndef PERSONA_H
#define PERSONA_H
#include <cstdlib>
#include <iostream>

using namespace std;

class Persona
{
	public:
		Persona();
		
		string	nombre,
				apellido,
				direccion,
				identificacion,
				nacionalidad,
				edad,
				sucursal;
		bool cliente;
		
		void setNombre(string nombre);
		void setApellido(string apellido);
		void setDireccion(string direccion);
		void setidenificacion(string cc);
		void setNacionalidad(string nacio);
		void setEdad(string edad);
		void setSucursal(string sucursal);
		
		
		bool verificaCliente(string cedula);
		
		string getNombre();
		string getApellido();
		string getDireccion();
		string getIdentificacion();
		string getEmail();
		string getNaciondalidad();
		string getEdad();
		string getSucursal();
		
		~Persona();
	protected:
};

#endif
