#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Usuario.h"

using namespace std;
Usuario::Usuario()
{
	
}

//Funcion para iniciar session
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

//Funcion para actualizar el saldo del cajero
void Usuario::actualizarSaldoCajero(string clave, int monto, string operacion){
	
	ifstream cajero_in;
	ofstream temp;
	
	bool encontrado;
	
	int dinero;
	
	string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
			sucursal, perfil, correo, contrasena, cliente;
			
	cajero_in.open("usuarios.txt");
	temp.open("temp2.txt");
	
	cajero_in>>nombre;//Leemos el primer campo de la primera linea
	
	while(!cajero_in.eof()){
				
		cajero_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
		if( (clave == identificacion || clave == correo) && perfil== "caja"){
			
			encontrado = true;
			
			if(operacion== "+"){
				temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<(dinero+monto)<<" "<<cliente<<endl;
			}else if(operacion == "-"){
				temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<(dinero-monto)<<" "<<cliente<<endl;
			}
		}else{
			temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
		}
		
		nombre="";
		cajero_in>>nombre;
	}
	
	
	if(!encontrado){
	   	cout<<"\t\t\t\t\t\tUsuario no encontrado "<<endl;
	}
	cajero_in.close();
	temp.close();
	
}

int Usuario::ObtenerSaldoCajero(string usuario){
	
	ifstream cajero_in;
	ofstream temp;
	
	bool encontrado;
	
	int dinero;
	
	string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
			sucursal, perfil, correo, contrasena, cliente, clave;
			
	cajero_in.open("usuarios.txt");
	
	cajero_in>>nombre;//Leemos el primer campo de la primera linea
	
	while(!cajero_in.eof()){
				
		cajero_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
		if( usuario == correo && perfil== "caja"){
			
			return dinero;			
		}
		
		nombre="";
		cajero_in>>nombre;
	}

	cajero_in.close();
	temp.close();
}
Usuario::~Usuario()
{
}
