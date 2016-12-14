#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Usuario.h"

using namespace std;
Usuario::Usuario()
{
	
}

bool Usuario::iniciarSession(string cor, string con, string per){
	
	//bool error= false;
	ifstream fichero("usuarios.txt", ios::in);
	
	if(!fichero) {
    	cout << "No se puede abrir el fichero" <<endl;
    }            
    else{
        string nombre, apellido, direccion, 
		 		identificacion, nacionalidad, edad, 
				sucursal, perfil, correo, contrasena, dinero, cliente;
				
        while(fichero>>nombre>> apellido>> direccion
		 		>> identificacion >> nacionalidad>>edad
				>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente){
								
			if(cor == correo && con == contrasena && per==perfil){
				return true;
			}	
        }
    }
    fichero.close();	
    
    return false;
}


Usuario::~Usuario()
{
}
