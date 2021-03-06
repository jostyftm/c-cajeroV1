#ifndef USUARIO_H
#define USUARIO_H

#include <fstream>

#include "Persona.h"

class Usuario : public Persona
{
	public:
		Usuario();
		
		ifstream fichero;
		string 	perfil,
				correo,
				contrasena;
		long dineroDisponible;
		
		bool iniciarSession(string cor, string con, string per);
		void actualizarSaldoCajero(string clave, int monto, string operacion);
		int ObtenerSaldoCajero(string usuario);
		
		~Usuario();
	protected:
};

#endif
