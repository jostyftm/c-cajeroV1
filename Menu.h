#ifndef MENU_H
#define MENU_H
#include "Usuario.h"
#include "Persona.h"
#include "Cuenta.h"


class Menu
{
	public:
		Usuario usuario;
		Cuenta cuenta;
		Menu();
		
		void MenuPrincipal();
		void MenuIniciarSession();
		
		// Funciones del Super Adminsitrador
		void MenuSuperAdministrador();
		void MenuCrearUsuario();
		void MenuEditarUsuario();
		void MenuConsultarUsuario();
		void MenuEliminarUsuario();
		
		//Funciones del administrador
		void MenuAdministrador();
		void MenuCliente();
		void MenuCuentas();
		void MenuChequera();
		void MenuAsignarDineroCajero();
		
		//Funciones para la caja
		void MenuCaja(string usuario);
		void MenuDepositos(string usuario);
		void MenuRetiros(string usuario);
		void MenuCheque(string usuario);
		
		//Estetica
		void Pausa(int segundo);
		
		~Menu();
	protected:
};

#endif
