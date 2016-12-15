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
		void MenuDepositos();
		void MenuRetiros();
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
		
		//
		void Pausa(int segundo);
		
		~Menu();
	protected:
};

#endif
