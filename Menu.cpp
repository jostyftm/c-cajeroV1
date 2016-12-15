#include<iostream>
#include "Menu.h"
#include <conio.h> //getch
#include <fstream> // Libreria para el manejo de archivos
#include<windows.h>

using namespace std;
Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::MenuPrincipal(){
	
	int opcion;
	
	do{
		
		cout<<"BIENVENIDO AL CAJERO "<<endl;
		cout<<"1. Depositos "<<endl;
		cout<<"2. Retiros "<<endl;
		cout<<"3. Iniciar session"<<endl;
		cout<<"4. Salir "<<endl;
		
		cin>>opcion;		
		
		switch(opcion){
			
			case 1:
				//mostrar el menu de depositos
				system("CLS");
				MenuDepositos();
				break;
			case 2:
				//mostrar el menu de retiros
				system("CLS");
				MenuRetiros();
				break;
			case 3:
				// mostramos un formulario para iniciar session
				system("CLS");
				MenuIniciarSession();
				break;
		}
		
	}while(opcion != 4);
}

void Menu::MenuDepositos(){
	
	bool encontrado;
	int opcion, monto, dinero;
	string numero_cuenta, tipo_cuenta, chequera, identificacion, num_cuenta_temp, dinero_temp;
	ifstream cuenta_in;
	ofstream temp;

	cout<<"Depositos"<<endl;
	cout<<"=============="<<endl;
		
	cuenta_in.open("cuentas.txt");
	temp.open("temp.txt");
	
	cout<<"numero de la cuenta a depositar : ";
	cin>>num_cuenta_temp;
	cuenta_in>>numero_cuenta;
	
	while(!cuenta_in.eof()){
		
		cuenta_in>>tipo_cuenta>>dinero>>chequera>>identificacion;
		
		if(num_cuenta_temp == numero_cuenta){	
			
			cout<<"Monto a depositar $ ";
			cin>>monto;
			
			cout<<"monto cuenta : "<<dinero<<" monto depositado : "<<monto<<" Totla : "<<(dinero + monto)<<endl;
			encontrado = true;
			
			temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<(dinero + monto)<<" "<<chequera<<" "<<identificacion<<endl;
		}else{
			temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<dinero<<" "<<chequera<<" "<<identificacion<<endl;
		}
		
		numero_cuenta="";
		cuenta_in>>numero_cuenta;
	}
	
	if(!encontrado){
		cout<<"la cuenta no existe"<<endl;
	}
	cuenta_in.close();
	temp.close();
	remove("cuentas.txt");
	rename("temp.txt","cuentas.txt");
	//system("CLS");
	
}

void Menu::MenuRetiros(){
	
	int opcion;
	
	
	do{
		
		cout<<"Retiro"<<endl;
		cout<<"=========================="<<endl;
		cout<<"Tipo de cuenta"<<endl;
		cout<<"1. C. de Ahorros"<<endl;;
		cout<<"2. C. Corriente"<<endl;
		cout<<"3. Atras "<<endl;
		
		cin>>opcion;		
		
	}while(opcion != 3);
	system("CLS");
	
}

void Menu::MenuIniciarSession(){

	int opcion;
	char caracter;
	string usuario, contra;
	
	do{
		
		cout<<"Inicio de session "<<endl;
		cout<<"=========================="<<endl;
		cout<<"1. Super madministrador "<<endl;
		cout<<"2. Administrador "<<endl;
		cout<<"3. Salir "<<endl;
		
		cin>>opcion;		
		
		switch(opcion){
			
			case 1:
				system("CLS");
				
				cout<<"Usuario : ";
				cin>>usuario;
				
				cout<<"Contrasena : ";
				caracter = getch();
				
				while(caracter != 13){
					contra.push_back(caracter);
					cout<<"*";
					caracter = getch();
				}
				
				if( this->usuario.iniciarSession(usuario, contra, "super") ){
					system("CLS");
					MenuSuperAdministrador();
				}else{
					cout<<"Usuario no encontrado"<<endl;
					usuario ="";
					contra="";
				}
				break;
			case 2:
				system("CLS");
				
				cout<<"Usuario : ";
				cin>>usuario;
				
				cout<<"Contrasena : ";
				
				caracter = getch();
				while(caracter != 13){
					contra.push_back(caracter);
					cout<<"*";
					caracter = getch();
				}
				
				if( this->usuario.iniciarSession(usuario, contra, "admin") ){
					system("CLS");
					MenuAdministrador();
				}else{
					cout<<"Usuario no encontrado"<<endl;
					usuario ="";
					contra="";
				}
				break;
		}
		
	}while(opcion != 3);
	system("CLS");
}

void Menu::MenuSuperAdministrador(){
	
	int opcion;
	
	
	do{
		
		cout<<"Menu del super administrador"<<endl;
		cout<<"=========================="<<endl;
		cout<<"1. Crear Usuario"<<endl;
		cout<<"2. Editar Usuario"<<endl;
		cout<<"3. Consultar usuario"<<endl;
		cout<<"4. Eliminar usuario"<<endl;
		cout<<"5. Salir"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			case 1:
				// Creamos un usuario
				system("CLS");
				MenuCrearUsuario();
				break;
			case 2:
				//Editamos un usuario
				system("CLS");
				MenuEditarUsuario();
				break;
			case 3:
				//Consultamos un usuario
				system("CLS");
				MenuConsultarUsuario();
				break;
			case 4:
				//Eliminado un usuario
				MenuEliminarUsuario();
				break;
		}		
		
	}while(opcion != 5);
	system("CLS");
}

void Menu::MenuCrearUsuario(){
	
	int opcion;
	string 	perfil;
	
	fstream usuariostxt("usuarios.txt", ios::app);
	ofstream cajero, caja;
	Usuario empleado; // empleado viene de la clase Usuario
	
	/* Creamos un usuario
	*	- Administrador
	*	- Caja
	*	- Cajero
	*/
	cout<<"Menu del super administrador"<<endl;
	cout<<"=========================="<<endl;
	cout<<"Escoger el tipo de usuario a crear "<<endl;
	cout<<"1. Administrador"<<endl;
	cout<<"2. Atras."<<endl;
	
	cin>>opcion;
	
	switch(opcion){
		case 1:
			system("CLS");
			perfil = "admin";
			
			cout<<"Nombre : ";
			cin>>empleado.nombre;
			
			cout<<"Apellido : ";
			cin>>empleado.apellido;
			
			cout<<"Direccion : ";
			cin>>empleado.direccion;
			
			cout<<"Identificacion : ";
			cin>>empleado.identificacion;
			
			cout<<"Nacionalidad : ";
			cin>>empleado.nacionalidad;
			
			cout<<"Edad : ";
			cin>>empleado.edad;
			
			cout<<"Sucursal : ";
			cin>>empleado.sucursal;
			
			empleado.perfil = perfil;
			
			cout<<"Correo : ";
			cin>>empleado.correo;
			
			cout<<"Contrasena : ";
			cin>>empleado.contrasena;
			
			empleado.dineroDisponible = 0;
			
			if(!usuariostxt.is_open()){
				usuariostxt.open("usuarios.txt", ios::app);
			}else{
				usuariostxt<<empleado.nombre<<" "<<empleado.apellido<<" "<<empleado.direccion<<" "<<empleado.identificacion<<" "<<empleado.nacionalidad<<" "<<empleado.edad<<" "<<empleado.sucursal<<" "<<perfil<<" "<<empleado.correo<<" "<<empleado.contrasena<<" "<<0<<" "<<"false"<<endl;
			}
			usuariostxt.close();
			break;
		
		default:
			break;
	}		
}

void Menu::MenuEditarUsuario(){
	
	int opcion;
	bool encontrado = false;
	string 	clave;
	
	ifstream usuariostxt;
	ofstream temp;
	
	/* Editar un usuario
	*	- Administrador
	*	- Caja
	*	- Cajero
	*/
	cout<<"Menu del super administrador"<<endl;
	cout<<"=========================="<<endl;
	cout<<"Escoger el tipo de usuario a editar "<<endl;
	cout<<"1. Administrador"<<endl;
	cout<<"2. Atras."<<endl;
	
	cin>>opcion;
	
	switch(opcion){
		case 1:
			system("CLS");

			string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
				 	sucursal, perfil, correo, contrasena, dinero, cliente;
				
			usuariostxt.open("usuarios.txt");
			temp.open("temp.txt");
			
			usuariostxt>>nombre;
			cout<<"Escriba la cedula para editar el usuario : ";
			cin>>clave;
				
			while(!usuariostxt.eof()){
				
				usuariostxt>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
				if(clave == identificacion && perfil=="admin"){
					int opcion2;
					encontrado = true;
					do{

						cout<<"Que campo desea editar "<<endl;
						cout<<"1. Nombre"<<endl;
						cout<<"2. Apellido"<<endl;
						cout<<"3. Direccion"<<endl;
						cout<<"4. Identificacion"<<endl;
						cout<<"5. Nacionalidad"<<endl;
						cout<<"6. Edad"<<endl;
						cout<<"7. Sucursal"<<endl;
						cout<<"8. Correo"<<endl;
						cout<<"9. Contrasena"<<endl;
						cout<<"10. Atras"<<endl;
						
						cin>>opcion2;
						
						switch(opcion2){
							
							case 1:
								//Editamos el nombre
								cout<<"nombre : ";
								cin>>nombre;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							case 2:
								//Editamos el nombre
								cout<<"apellido : ";
								cin>>apellido;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							case 3:
								//Editamos la dirección
								cout<<"direccion : ";
								cin>>direccion;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							case 4:
								//Editamos la cedula
								cout<<"idenetificacion : ";
								cin>>identificacion;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							case 5:
								//Editamos la nacionalidad
								cout<<"nacionalidad : ";
								cin>>nacionalidad;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							case 6:
								//Editamos la edad
								cout<<"edad : ";
								cin>>edad;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							case 7:
								//Editamos la sucursal
								cout<<"sucursal : ";
								cin>>sucursal;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							case 8:
								//Editamos el correo
								cout<<"correo : ";
								cin>>correo;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							case 9:
								//Editamos el correo
								cout<<"Contrasena : ";
								cin>>contrasena;
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
							default:
								temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
								break;
						}
						system("CLS");
						opcion2=10;			
					}while(opcion2 != 10);
				}else{
					temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;	
						
				}
				nombre="";
				usuariostxt>>nombre;
		    }	
		    
		    if(!encontrado){
		    	cout<<"Usuario no encontrado "<<endl;
			}
		    usuariostxt.close();
		    temp.close();
		    remove("usuarios.txt");
		    rename("temp.txt", "usuarios.txt");
		    break;
	}		
		
}

void Menu::MenuConsultarUsuario(){
	
	int opcion;
	bool encontrado = false;
	string 	clave;
	
	ifstream usuariostxt;
	
	/* Consultar un usuario
	*	- Administrador
	*	- Caja
	*	- Cajero
	*/
	cout<<"Menu del super administrador"<<endl;
	cout<<"=========================="<<endl;
	cout<<"Escoger el tipo de usuario a consultar "<<endl;
	cout<<"1. Administrador"<<endl;
	cout<<"2. Atras."<<endl;
	
	cin>>opcion;
	
	switch(opcion){
		case 1:
			system("CLS");

			string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
				 	sucursal, perfil, correo, contrasena, dinero, cliente;
				
			usuariostxt.open("usuarios.txt");
						
			usuariostxt>>nombre;
			cout<<"Escriba la cedula para consultar el usuario : ";
			cin>>clave;
				
			while(!usuariostxt.eof()){
				
				usuariostxt>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
				if(clave == identificacion && perfil=="admin"){
					encontrado=true;
					cout<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
		        }
		        
		        nombre="";
				usuariostxt>>nombre;
		    }
		        
		    if(!encontrado){
		       	cout<<"Usuario no encontrado"<<endl;
			}
		    usuariostxt.close();		
			break;
	}
}

void Menu::MenuEliminarUsuario(){
	
	int opcion;
	bool encontrado = false;
	string 	clave;
	
	ifstream usuariostxt;
	ofstream temp;
	
	/* Editar un usuario
	*	- Administrador
	*	- Caja
	*	- Cajero
	*/
	cout<<"Menu del super administrador"<<endl;
	cout<<"=========================="<<endl;
	cout<<"Escoger el tipo de usuario a eliminar "<<endl;
	cout<<"1. Administrador"<<endl;
	cout<<"2. Atras."<<endl;
	
	cin>>opcion;
	
	switch(opcion){
		case 1:
			system("CLS");

			string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
				 	sucursal, perfil, correo, contrasena, dinero, cliente;
				
			usuariostxt.open("usuarios.txt");
			temp.open("temp.txt");
			
			usuariostxt>>nombre;
			cout<<"Escriba la cedula para eliminar a el usuario : ";
			cin>>clave;
				
			while(!usuariostxt.eof()){
				
				usuariostxt>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
				if(clave == identificacion && perfil=="admin"){
					encontrado = true;
					cout<<"Se ha eliminado al usuario "<<nombre<<" "<<apellido<<endl;
				}else{
					temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;	
						
				}
				nombre="";
				usuariostxt>>nombre;
		    }	
		    
		    if(!encontrado){
		    	cout<<"Usuario no encontrado "<<endl;
			}
		    usuariostxt.close();
		    temp.close();
		    remove("usuarios.txt");
		    rename("temp.txt", "usuarios.txt");
		    break;
	}		
}


//Funciones del administrador
void Menu::MenuAdministrador(){
	
	int opcion;
	
	do{
		
		cout<<"Menu del Administrador"<<endl;
		cout<<"=========================="<<endl;
		cout<<"1. Cliente"<<endl;
		cout<<"2. Cuenta"<<endl;
		cout<<"3. Chequera"<<endl;
		cout<<"4. Asignar dinero a un cajero"<<endl;
		cout<<"5. Salir"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			case 1:
				// Funciones par los clientes
				system("CLS");
				MenuCliente();
				break;
			case 2:
				// Funciones para las cuentas
				system("CLS");
				MenuCuentas();
				break;
			case 3:
				// Funciones para las chequeras
				system("CLS");
				MenuChequera();
				break;
			case 4:
				// Funcio para asignar dinero a un cajero
				break;
		}		
		
	}while(opcion != 5);
	system("CLS");
}

//Funcion del administrador para las funciones de los cientes
void Menu::MenuCliente(){
	
	int opcion;
	bool encontrado=false;
	string  nombre, apellido, direccion, identificacion, nacionalidad, edad, clave;
	
	Persona cliente;
	ofstream cliente_out, cuenta_out, temp;
	ifstream cliente_in, cuenta_in;
	
	
	do{
		
		cout<<"Menu del Administrador - Funciones para clientes"<<endl;
		cout<<"=========================="<<endl;
		cout<<"1. Crear cliente"<<endl;
		cout<<"2. Editar cliente"<<endl;
		cout<<"3. Consutar cliente"<<endl;
		cout<<"4. Eliminar cliente"<<endl;
		cout<<"5. Salir"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			case 1:
				// Funcion para crear un cliente
				system("CLS");
				cliente_out.open("clientes.txt", ios::app);
				
				cout<<"Nombre : ";
				cin>>cliente.nombre;
				
				cout<<"Apellido : ";
				cin>>cliente.apellido;
				
				cout<<"Direccion : ";
				cin>>cliente.direccion;
				
				cout<<"Identificacion : ";
				cin>>cliente.identificacion;
				
				cout<<"Nacionalidad : ";
				cin>>cliente.nacionalidad;
				
				cout<<"Edad : ";
				cin>>cliente.edad;
								
				cliente_out<<cliente.nombre<<" "<<cliente.apellido<<" "<<cliente.direccion<<" "<<cliente.identificacion<<" "<<cliente.nacionalidad<<" "<<cliente.edad<<endl;
				cliente_out.close();
				
				cout<<"Cliente registrado exitosamente ..."<<endl;
				Pausa(2);
				system("CLS");
				break;
			case 2:
				// Funcion para editar un cliente
				system("CLS");
					
				cliente_in.open("clientes.txt");
				temp.open("temp.txt");
				
				cliente_in>>nombre;
				cout<<"N° de cedula : ";
				cin>>clave;
				
				while(!cliente_in.eof()){
					
					cliente_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad;
				
					if(clave == identificacion){
						int opcion2;
						encontrado = true;
						do{
							cout<<"Que campo desea editar "<<endl;
							cout<<"1. Nombre"<<endl;
							cout<<"2. Apellido"<<endl;
							cout<<"3. Direccion"<<endl;
							cout<<"4. Identificacion"<<endl;
							cout<<"5. Nacionalidad"<<endl;
							cout<<"6. Edad"<<endl;
							cout<<"7. Atras"<<endl;
						
							cin>>opcion2;
							
							switch(opcion2){
								case 1:
									//Editamos el nombre
									cout<<"nombre : ";
									cin>>nombre;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 2:
									//Editamos el nombre
									cout<<"apellido : ";
									cin>>apellido;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 3:
									//Editamos la dirección
									cout<<"direccion : ";
									cin>>direccion;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 4:
									//Editamos la cedula
									cout<<"idenetificacion : ";
									cin>>identificacion;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 5:
									//Editamos la nacionalidad
									cout<<"nacionalidad : ";
									cin>>nacionalidad;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 6:
									//Editamos la edad
									cout<<"edad : ";
									cin>>edad;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								default:
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
							}
						
							system("CLS");
							opcion2=7;	
						}while(opcion2!=7);
					}else{
						temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
					}
					nombre="";
					cliente_in>>nombre;
				}
				
				if(!encontrado){
			    	cout<<"Cliente no encontrado "<<endl;
				}else{
					cout<<"Se ha actualizado los datos del cliente exitosamente"<<endl;
					Pausa(2);
					system("CLS");
				}
			    cliente_in.close();
			    temp.close();
			    remove("clientes.txt");
			    rename("temp.txt", "clientes.txt");
				break;
			case 3:
				// Funcion para consultar un cliente
				system("CLS");
				cliente_in.open("clientes.txt");
				
				cliente_in>>nombre;
				cout<<"N° de cedula : ";
				cin>>clave;
				
				while(!cliente_in.eof()){
					
					cliente_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad;
				
					if(clave == identificacion){
						int opcion2;
						encontrado = true;
						cout<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
					}
					
					nombre="";
					cliente_in>>nombre;
				}
				if(!encontrado){
			    	cout<<"Cliente no encontrado "<<endl;
				}
			    cliente_in.close();
				break;
			case 4:
				// Funcion para eliminar un cliente
				system("CLS");
				cliente_in.open("clientes.txt");
				temp.open("temp.txt");
				
				cliente_in>>nombre;
				cout<<"N° de cedula : ";
				cin>>clave;
				
				while(!cliente_in.eof()){
					
					cliente_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad;
				
					if(clave == identificacion){
						encontrado = true;
						cout<<"Se ha eliminado al cliente "<<nombre<<" "<<apellido<<" exitosamente"<<endl;
						Pausa(3);
						system("CLS");
					}else{
						temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
					}
					nombre="";
					cliente_in>>nombre;
				}
				
				if(!encontrado){
			    	cout<<"Cliente no encontrado "<<endl;
			    	Pausa(3);
					system("CLS");
				}
			    cliente_in.close();
			    temp.close();
			    remove("clientes.txt");
			    rename("temp.txt", "clientes.txt");
				break;
		}		
	}while(opcion != 5);
	system("CLS");
}

// Función del administrador para las cuentas
void Menu::MenuCuentas(){
	
	int opcion, dinero_disponible;
	bool encontrado = false;
	ifstream cuentas_in;
	ofstream cuentas_out;
	
	string num_cuenta, tipo_cuenta, chequera, identificacion
			, cedula_temp;
	do{
		cout<<"Menu del Administrador - Funciones para las cuentas"<<endl;
		cout<<"=========================="<<endl;
		cout<<"1. Crear cuenta"<<endl;
		cout<<"2. Consutar cuenta"<<endl;
		cout<<"3. Salir"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			
			case 1:
				system("CLS");
				cout<<"Cedula del clinete : ";
				cin>>identificacion;
				
				cuentas_out.open("cuentas.txt", ios::app);
				if(!this->usuario.verificaCliente(identificacion)){
					cout<<"El cliente no esta registrado en la base de datos "<<endl;
				}else{
					string tipo_cuenta_temp;
					cout<<"Tipo de cuenta "<<endl;
					cout<<"1. Ahorro \t\t\t\t 2. Coriente : ";
					cin>>tipo_cuenta_temp;
					if(tipo_cuenta_temp == "2"){
						tipo_cuenta = "corriente";
						chequera = "si";
					}else{
						tipo_cuenta = "ahorro";
						chequera = "no";
					}
					cout<<"\n Dinero disponible : $ ";
					cin>>dinero_disponible;
					
					num_cuenta = this->cuenta.ObtenerNumeroCuenta();
					
					cuentas_out<<num_cuenta<<" "<<tipo_cuenta<<" "<<dinero_disponible<<" "<<chequera<<" "<<identificacion<<endl;
				}
				break;
			case 2:
				system("CLS");
				cout<<"Cedula del clinete : ";
				cin>>cedula_temp;
				
				cuentas_in.open("cuentas.txt");
				cuentas_in>>num_cuenta;
				if(!this->usuario.verificaCliente(cedula_temp)){
					cout<<"El cliente no esta registrado en la base de datos "<<endl;
				}else{
					while(!cuentas_in.eof()){
						cuentas_in>>tipo_cuenta>>dinero_disponible>>chequera>>identificacion;
						
						if(cedula_temp == identificacion){
							cout<<num_cuenta<<" "<<tipo_cuenta<<" "<<dinero_disponible<<" "<<chequera<<" "<<identificacion<<endl;
						}
						num_cuenta="";
						cuentas_in>>num_cuenta;
					}
				}
				break;
			default:
				break;
		}
		
		cuentas_in.close();
	
	}while(opcion=!3);
}


void Menu::MenuChequera(){
	
	int opcion, num_cuentas=0;
	string num_cuenta_temp, num_chequera_temp, num_chequera, num_cedula;
	bool encontrado=false;
	
	ofstream chequeras_out;
	ifstream chequeras_in;
	do{
		cout<<"Menu del Administrador - Funciones para clientes"<<endl;
		cout<<"=========================="<<endl;
		cout<<"1. Crear chequera"<<endl;
		cout<<"2. Consutar chequera"<<endl;
		cout<<"3. Salir"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			
			case 1:
				system("CLS");
				cout<<"No. de cuenta  : ";
				cin>>num_cuenta_temp;
				chequeras_out.open("chequeras.txt", ios::app);
				
				if(!this->cuenta.VerificarTipoCuenta("ahorro", num_cuenta_temp)){
					cout<<"Las chequeras solo son para cuentas de tipo corriente"<<endl;	
				}else{
					cout<<"No. de cedula  : ";
					cin>>num_cedula;
					
					if(!this->cuenta.VerificarCuentaCliente(num_cuenta_temp, num_cedula)){
						cout<<"El numero de cuenta no se asocia con la cedula";
					}else{
						num_chequera = this->cuenta.ObtenerNumeroChequera();
						chequeras_out<<num_chequera<<" "<<num_cuenta_temp<<endl;	
						cout<<"Chequera registrada con exito... por favor espere"<<endl;
						Pausa(3);
						system("CLS");
					}
				}
				break;
			case 2:
				system("CLS");
				cout<<"No. de la chequera  : ";
				cin>>num_chequera_temp;
				chequeras_in.open("chequeras.txt");
				
				chequeras_in>>num_chequera;
				
				while(!chequeras_in.eof()){
					chequeras_in>>num_cuenta_temp;
					
					if(num_chequera_temp == num_chequera){
						cout<<num_chequera<<" "<<num_cuenta_temp<<endl;
						encontrado = true;
					}
					
					num_chequera="";
					chequeras_in>>num_chequera;
				}
				
				if(!encontrado){
					cout<<"Esta chequera no esta registrada "<<endl;
					Pausa(3);
					system("CLS");
				}
				opcion = 3;
				break;
			
			default:
				break;
		}
		
	}while(opcion !=3);
}
// Funciones para estetica
void Menu::Pausa(int segundo){
	Sleep(segundo*1000);
}
