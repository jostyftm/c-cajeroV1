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
		
		bool verificaCliente(string cedula);

		~Persona();
	protected:
};

#endif
