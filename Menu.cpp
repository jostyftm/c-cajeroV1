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

// Funcion mustra el menu principal
void Menu::MenuPrincipal(){
	
	//variable para evaluar la opcion elegida
	int opcion;
	
	do{
		
		cout<<"\t\t\t\t\t\tBIENVENIDO AL CAJERO "<<endl;
		cout<<"\t\t\t\t\t\t====================="<<endl;
		cout<<"\t\t\t\t\t\t1. Iniciar session"<<endl;
		cout<<"\t\t\t\t\t\t4. Salir "<<endl;
		
		cin>>opcion;		
		
		//evaluamos la opcion elegida
		switch(opcion){
			
			case 1:
				// mostramos un formulario para iniciar session
				system("CLS");
				MenuIniciarSession();
				break;
			default:
				opcion=4;
				break;
		}
		
	}while(opcion != 4);
}

// Funcion menu para depositos
void Menu::MenuDepositos(string usuario){
	
	
	bool encontrado=false; //Variable que evalua si algun registro fue encontrado por defecto es false
	
	//Variables a utilizar
	int opcion, monto, dinero;
	string numero_cuenta, tipo_cuenta, chequera, identificacion, contrasena, num_cuenta_temp, dinero_temp;
	ifstream cuenta_in;
	ofstream temp;

	cout<<"\t\t\t\t\t\tDepositos"<<endl;
	cout<<"\t\t\t\t\t\t=============="<<endl;
	
	// Abrimos los ficheros
	cuenta_in.open("cuentas.txt");
	temp.open("temp.txt");
	
	//Solicitamos la cuenta a depositar
	cout<<"\t\t\t\t\t\tnumero de la cuenta a depositar : ";
	cin>>num_cuenta_temp;
	
	// Leemos el primer campo del archivo cuenta
	cuenta_in>>numero_cuenta;
	
	// Recorremos el archivos hasta que llegue a la ultima linea
	while(!cuenta_in.eof()){
		
		// Leemos los campos faltantes
		cuenta_in>>tipo_cuenta>>dinero>>chequera>>identificacion>>contrasena;
		
		//Preguntamos si la cuenta a buscar coincide con alguna que este en el archivo cuentas.txt
		if(num_cuenta_temp == numero_cuenta){	
			
			cout<<"\t\t\t\t\t\tMonto a depositar $ "; //Solicitamos el monto a depositar
			cin>>monto;			
			
			// Mostramos en pantalla el monto depositado y el saldo de la cuenta
			cout<<"\n\nNumero de cuenta \tMonto depositado \tSaldo"<<endl;
			cout<<"__________________________________________________________________________"<<endl;
			cout<<numero_cuenta<<" \t\t\t"<<monto<<" \t\t\t "<<(dinero +monto)<<"\n\n"<<endl;
			
			encontrado = true; //Encontrado ahora es true
			
			//Escribimos en el archivo temp
			temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<(dinero + monto)<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
			
			//Actualizamos el saldo del cajero
			this->usuario.actualizarSaldoCajero(usuario, monto, "+");
			
			cout<<"\t\t\t\t\t\tDeposito realizado con exito..... por favor espere"<<endl;
			
		}else{ // Si no se encuentra la cuenta escribimos los datos normales sin modificarlos
			
			temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<dinero<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
		}
		
		numero_cuenta=""; // Limpiamos la variable
		cuenta_in>>numero_cuenta; // Leemos nuevamente el primer campo de la nueva liena
	}
	
	
	//Cerramos el archivo
	cuenta_in.close(); 
	temp.close();
	
	if(!encontrado){ // Si no se encuentra notificamos
		cout<<"\t\t\t\t\t\tla cuenta no existe"<<endl;
	}else{
		remove("cuentas.txt"); // Removemos el archivo
		rename("temp.txt","cuentas.txt"); // Remplazamos el archivo cuentas.txt para que quede con los nuevos registros
		remove("usuarios.txt"); // Removemos el archivo
		rename("temp2.txt", "usuarios.txt"); // Remplazamos el archivo usuarios.txt para que quede con los nuevos registros	
	}
	
	system("CLS");
	
}

void Menu::MenuRetiros(string usuario){
	
	// Variables para el manejo de ficheros
	ifstream cuentas_in;
	ofstream temp;
	
	//Variables a utilizar
	bool encontrado = false, retiro = false;
	
	int opcion, dinero, dinero_temp, dinero_cajero;
	
	// Variable para manejar las cuentas
	string numero_cuenta, tipo_cuenta, chequera, identificacion, contrasena;
	
	//variables temporales
	string num_cuenta_temp;
	
	//Variables para las chequeras
	string num_chequera;
	do{
		
		cout<<"\t\t\t\t\t\tRetiro"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\t1. Numero de cuenta"<<endl;
		cout<<"\t\t\t\t\t\t2. Atras "<<endl;
		
		cin>>opcion;		
		
		switch(opcion){
			case 1:
				system("CLS");
				
				//Abrimos los ficheros
				cuentas_in.open("cuentas.txt");
				temp.open("temp.txt");
				
				cout<<"\t\t\t\t\t\tNumero de cuenta : ";
				cin>>num_cuenta_temp;
				
				cuentas_in>>numero_cuenta; // Leemos el primer campo del aechivo cuentas.txt
				
				while(!cuentas_in.eof()){ //Recorremos hasta que llegue no halla lineas
					cuentas_in>>tipo_cuenta>>dinero>>chequera>>identificacion>>contrasena; //Leemos el resto de los campos
					
					if(num_cuenta_temp == numero_cuenta){ // Preguntamos si el numero de cuenta coincide con linea recorrida
						encontrado = true;
						cout<<"\t\t\t\t\t\tMonto a retirar : $ ";
						cin>>dinero_temp;
						
						//Obtenemos el dinero del cajero
						dinero_cajero = this->usuario.ObtenerSaldoCajero(usuario);
						
						if(dinero_temp>dinero){// Preguntamos si el dinero solicitado es mayor al de la cuenta
							cout<<"\t\t\t\t\t\tNo cuenta con los fondos suficientes para retirar lo solicitado :("<<endl;
							temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<dinero<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
						}else if(dinero_temp > dinero_cajero){
							cout<<"El cajero no cuenta con esta cantidad de dinero por favor vuelve mas tarde o intenta con otro cajero"<<endl;
							temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<dinero<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
						}else{
							//Escribimos los datos con el descuento del retiro
							temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<(dinero-dinero_temp)<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
							
							//Actualizamos el saldo del cajero
							this->usuario.actualizarSaldoCajero(usuario, dinero_temp, "-");
							
							retiro = true;		
						}
						
						if(retiro){// Si se efectua el retiro notificamos
							cout<<"\t\t\t\t\t\tEstamos contando su dinero.........\n"<<endl;
							Pausa(2);
							cout<<"\t\t\t\t\t\tTransacion realizada con exito...... "<<endl;
							Pausa(2);
							cout<<"\t\t\t\t\t\tSaldo disponible : "<<(dinero-dinero_temp)<<"\n\n"<<endl;
						}
						
					}else{
						// Si no se encuentra la cuenta escribimos los datos normales sin modificarlos
						temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<dinero<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
					}
					
					numero_cuenta=""; // Limpiamos la variable
					cuentas_in>>numero_cuenta; // Leemos nuevamente el primer campo de la nueva liena
				}
				
				
				
				//Cerramos los archvos
				cuentas_in.close();
				temp.close();
				if(!encontrado){ // Si no se encuentra notificamos
					cout<<"\t\t\t\t\t\tCuenta no encontrada "<<endl;
				}
				
				if(retiro){
					remove("usuarios.txt");
					rename("temp2.txt","usuarios.txt");
				}
				remove("cuentas.txt");
				rename("temp.txt","cuentas.txt");
				

				break;
			default:
				opcion=2;
				break;
		}
		
	}while(opcion != 2);
	system("CLS");
	
}

//Funcion para iniciar session
void Menu::MenuIniciarSession(){
	
	//Variabes a utilizar
	int opcion;
	char caracter;
	string usuario, contra;
	
	do{
		
		cout<<"\t\t\t\t\t\tInicio de session "<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\t1. Super madministrador "<<endl;
		cout<<"\t\t\t\t\t\t2. Administrador "<<endl;
		cout<<"\t\t\t\t\t\t3. Caja"<<endl;
		cout<<"\t\t\t\t\t\t4. Salir "<<endl;
		
		cin>>opcion;		
		
		switch(opcion){
			
			case 1: //Iniciamos session para Super administrador
				system("CLS");
				cout<<"\t\t\t\t\t\tInicio se session | Super administrador "<<endl;
				
				cout<<"\t\t\t\t\t\tUsuario : ";
				cin>>usuario;
				
				cout<<"\t\t\t\t\t\tContrasena : ";
				caracter = getch();
				
				while(caracter != 13){ //Mostramos la contraseña en asteriscos (*) hasta que presione enter
					contra.push_back(caracter);
					cout<<"*";
					caracter = getch();
				}
				
				if( this->usuario.iniciarSession(usuario, contra, "super") ){// Si los datos recolectados son los correctos iniciamos session
					system("CLS");
					MenuSuperAdministrador(); // Mostramos en menu del super adminisrador
				}else{
					cout<<"\t\t\t\t\t\tUsuario no encontrado"<<endl;
					usuario ="";
					contra="";
				}
				break;
			case 2:
				system("CLS");
				cout<<"\t\t\t\t\t\tInicio se session | administrador "<<endl;
				
				cout<<"\t\t\t\t\t\tUsuario : ";
				cin>>usuario;
				
				cout<<"\t\t\t\t\t\tContrasena : ";
				
				caracter = getch();
				while(caracter != 13){
					contra.push_back(caracter);
					cout<<"*";
					caracter = getch();
				}
				
				if( this->usuario.iniciarSession(usuario, contra, "admin") ){
					system("CLS");
					MenuAdministrador();// Mostramos el menu del administrador
				}else{
					cout<<"\t\t\t\t\t\tUsuario no encontrado"<<endl;
					usuario ="";
					contra="";
				}
				break;
			case 3:
				system("CLS");
				cout<<"\t\t\t\t\t\tInicio se session | Cajero "<<endl;
				
				cout<<"\t\t\t\t\t\tUsuario : ";
				cin>>usuario;
				
				cout<<"\t\t\t\t\t\tContrasena : ";
				
				caracter = getch();
				while(caracter != 13){
					contra.push_back(caracter);
					cout<<"*";
					caracter = getch();
				}
				
				if( this->usuario.iniciarSession(usuario, contra, "caja") ){
					system("CLS");
					MenuCaja(usuario); //Mostramos el menu del cajero
				}else{
					cout<<"\t\t\t\t\t\tUsuario no encontrado"<<endl;
					usuario ="";
					contra="";
				}
				break;
			default:
				opcion=4;
				break;
		}
		
	}while(opcion != 4);
	system("CLS");
}

// Funcion que muestra el menu del cajero
void Menu::MenuCaja(string usuario){
	
	int opcion;
	do{
		cout<<"\t\t\t\t\t\tMenu del Cajero | Saldo disponible : $ "<<this->usuario.ObtenerSaldoCajero(usuario)<<endl;
		cout<<"\t\t\t\t\t\t=============================================================="<<endl;
		cout<<"\t\t\t\t\t\t1. Deposito "<<endl;
		cout<<"\t\t\t\t\t\t2. Retiro "<<endl;
		cout<<"\t\t\t\t\t\t3. Cheque "<<endl;
		cout<<"\t\t\t\t\t\t4. atras"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			
			case 1:
				system("CLS");
				MenuDepositos(usuario); //Mostramos el menu de depositos
				break;
			case 2:
				system("CLS");
				MenuRetiros(usuario); //Mostramos en menu de retiros
				break;
			case 3:
				system("CLS");
				MenuCheque(usuario); //Mostramos el menu de cheques
				break;
			default:
				opcion=4;
				break;
		}
		
	}while(opcion!=4);
	system("CLS");
}

//Funcion que muestra el menu de cheques
void Menu::MenuCheque(string usuario){
	
	//Variables a utilizar
	int opcion;
	
	ofstream cheque_out, temp;
	ifstream cheque_in;
	
	bool encontrado=false, retiro=false;
	
	int monto_cheque, monto_cuenta, dinero_cajero;
	
	string 	num_cuenta, num_cheque, num_chequera, estado,
			num_cheque_temp, num_chequera_temp;
	
	
	do{
		cout<<"\t\t\t\t\t\tMenu del Cajero - Cheques"<<endl;
		cout<<"\t\t\t\t\t\t==================="<<endl;
		cout<<"\t\t\t\t\t\t1. Crear cheque"<<endl;
		cout<<"\t\t\t\t\t\t2. Anular cheque"<<endl;
		cout<<"\t\t\t\t\t\t3. Retitar mediante cheque"<<endl;
		cout<<"\t\t\t\t\t\t4. atras "<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			
			case 1:
				system("CLS");
				cheque_out.open("cheques.txt", ios::app);
				
				cout<<"\t\t\t\t\t\tNumero de chequera : ";
				cin>>num_chequera;
				
				//Verificamos si elm numero de la chequera existe
				if(this->cuenta.VerificarNumeroChequera(num_chequera)){
					//Obtenemos el numero de cuenta de la chequera
					num_cuenta = this->cuenta.ObtenerNumeroCuentaPorChequera(num_chequera);
					//Obtenemos el monto de la cuenta que esta asociada a la chequera
					monto_cuenta = this->cuenta.ObtenerDineroDisponible(num_cuenta);
					
					cout<<"\t\t\t\t\t\tNumero del cheque : ";
					cin>>num_cheque;	
					
					//Verificamos si el cheque existe
					if(this->cuenta.VerificarCheque(num_chequera, num_cheque)){
						cout<<"\t\t\t\t\t\tEste cheque ya esta registrado"<<endl;
					}else{
						
						cout<<"\t\t\t\t\t\tMonto a pagar : ";
						cin>>monto_cheque;
						
						//Verificamos si el monto a retirar es mayor al monto de la cuenta
						if(monto_cheque > monto_cuenta){
							cout<<"\t\t\t\t\t\tEl monto a pagar es superior al monto almacenado :("<<endl;
						}else{
							//Registramos el cheque en el archivo cheques.txt
							cheque_out<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<"activo"<<endl;
							cout<<"\t\t\t\t\t\tsu cheque ha sido registrado con exito"<<endl;
						}
					}
				}
				//Cerramos elarchivo
				cheque_out.close();
				break;
			case 2:
				system("CLS");
				//Abrimos los archivos
				cheque_in.open("cheques.txt");
				temp.open("temp.txt");
				
				
				cout<<"\t\t\t\t\t\tNumero de la chequera :";
				cin>>num_chequera_temp;
				
				//Verificamos el numero de la chequera
				if(this->cuenta.VerificarNumeroChequera(num_chequera_temp)){
					
					cout<<"\t\t\t\t\t\tNumero del cheque : ";
					cin>>num_cheque_temp;
					
					//Verificamos que el cheque este registrado
					if(!this->cuenta.VerificarCheque(num_chequera_temp, num_cheque_temp)){
						cout<<"\t\t\t\t\t\tEste cheque no esta registrado "<<endl;
					}else{
						
						cheque_in>>num_cheque; //Leemos el primer campo de la primera linea
						
						while(!cheque_in.eof()){ //Recorremos hasta que llegue no halla lineas
							cheque_in>>monto_cheque>>num_chequera>>estado; //Leemos los campos faltantes
							
							if(num_cheque_temp == num_cheque){// Preguntamos si el cheque coincide con el cheque de la linea recorrida
								if(estado == "pagado"){
									//Si el cheque a cobrar esta pagado notificamos
									cout<<"\t\t\t\t\t\tNo se pude anular este cheque por que ya se pago"<<endl;
									temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<estado<<endl;
								}else if(estado == "anulado"){
									//Si el cheque a cobrar esta anulado notificamos
									cout<<"\t\t\t\t\t\tNo se pude anular este cheque por que ya esta anulado"<<endl;
									temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<estado<<endl;
								}else{
									//encontrado ahora es true y escribimos los datos pero con el cheque anulado
									encontrado = true;
									temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<"anulado"<<endl;
									cout<<"\t\t\t\t\t\tEstamos anulando el cheque...por favor espere\n"<<endl;
									Pausa(3);
									cout<<"\t\t\t\t\t\tTransacion realizada con exito"<<endl;
								}
							}else{
								// Si no se encuentra el cheque escribimos los datos normales sin modificarlos
								temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<estado<<endl;
							}
							
							num_cheque="";
							cheque_in>>num_cheque;
						}
						
						if(!encontrado){
							cout<<"\t\t\t\t\t\tNo se encontro el cheque "<<endl;
						}
					}
				}else{
					cout<<"\t\t\t\t\t\tChequera no encontrada"<<endl;
				}
				
				cheque_in.close();
				temp.close();
				
				remove("cheques.txt");
				rename("temp.txt","cheques.txt");
				
				Pausa(3);
				system("CLS");
				break;
			case 3:
				system("CLS");
				
				cheque_in.open("cheques.txt");
				temp.open("temp.txt");
				
				cout<<"\t\t\t\t\t\tNumero de la chequera :";
				cin>>num_chequera_temp;
				
				if(this->cuenta.VerificarNumeroChequera(num_chequera_temp)){//Verificamos si la chequera existe
					
					cout<<"\t\t\t\t\t\tNumero del cheque : ";
					cin>>num_cheque_temp;
					
					//Verificamos si el cheque existe, y si existe que pertenesca a la chequera
					if(!this->cuenta.VerificarCheque(num_chequera_temp, num_cheque_temp)){
						cout<<"\t\t\t\t\t\tEste cheque no esta registrado "<<endl;
					}else{
						
						cheque_in>>num_cheque; //leemos el primer campo de la primera linea
						
						while(!cheque_in.eof()){
							cheque_in>>monto_cheque>>num_chequera>>estado;//Leemos el resto de los campos
							
							if(num_cheque_temp == num_cheque){// Preguntamos si el cheque coincide con el cheque de la linea recorrida
								if(estado == "pagado"){
									cout<<"\t\t\t\t\t\tNo se pude cobrar este cheque por que ya se pago"<<endl;
									temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<estado<<endl;
									
								}else if(estado == "anulado"){
									cout<<"\t\t\t\t\t\tNo se pude cobrar este cheque por que esta anulado"<<endl;
									temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<estado<<endl;
									
								}else{
									encontrado = true;
									//Obtenemos el numero de la cuenta
									num_cuenta = this->cuenta.ObtenerNumeroCuentaPorChequera(num_chequera);
									//Obtenemos el saldo de la cuenta
									monto_cuenta = this->cuenta.ObtenerDineroDisponible(num_cuenta);
									//Obtenemos el dinero del cajero
									dinero_cajero = this->usuario.ObtenerSaldoCajero(usuario);
									
									if(monto_cheque > monto_cuenta){//Si el monto a retirar es mayor al saldo de la cuenta notificamos
										cout<<"\t\t\t\t\t\tFondos insificientes" <<endl;
										temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<estado<<endl;
									}else if(monto_cheque > dinero_cajero){
										cout<<"El cajero no cuenta con esta cantidad de dinero por favor vuelve mas tarde o intenta con otro cajero"<<endl;
										temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<estado<<endl;
									}else{
										retiro=true;
										//Actualizamos el saldo de la cuenta
										this->cuenta.ActualizarSaldo(num_cuenta, monto_cheque, "-");
										//Actualizamos el saldo del cajero
										this->usuario.actualizarSaldoCajero(usuario, monto_cheque, "-");
										//Escribimos los datos con el nuevo saldo
										temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<"pagado"<<endl;	
										
										cout<<"\t\t\t\t\t\tEstamos contando su dinero...por favor espere\n"<<endl;
										Pausa(3);
										cout<<"\t\t\t\t\t\tTransacion realizada con exito"<<endl;
									}
								}
							}else{
								temp<<num_cheque<<" "<<monto_cheque<<" "<<num_chequera<<" "<<estado<<endl;
							}
							
							num_cheque="";
							cheque_in>>num_cheque;
						}
						if(!encontrado){
							cout<<"\t\t\t\t\t\tNo se encontro el cheque "<<endl;
						}
					}
				}else{
					cout<<"\t\t\t\t\t\tChequera no encontrada"<<endl;
				}
				
				cheque_in.close();
				temp.close();
				
				if(retiro){
					remove("cheques.txt");
					rename("temp.txt","cheques.txt");
				
					remove("usuarios.txt");
					rename("temp2.txt", "usuarios.txt");
				}
				
	
				Pausa(3);
				system("CLS");
				break;
			default:
				opcion=4;
				break;
		}
		
	}while(opcion!=4);
	system("CLS");
}

//Funcion que muestra el menu del super administrador
void Menu::MenuSuperAdministrador(){
	
	int opcion;	
	
	do{
		
		cout<<"\t\t\t\t\t\tMenu del super administrador"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\t1. Crear Usuario"<<endl;
		cout<<"\t\t\t\t\t\t2. Editar Usuario"<<endl;
		cout<<"\t\t\t\t\t\t3. Consultar usuario"<<endl;
		cout<<"\t\t\t\t\t\t4. Eliminar usuario"<<endl;
		cout<<"\t\t\t\t\t\t5. Salir"<<endl;
		
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
				system("CLS");
				MenuEliminarUsuario();
				break;
			default:
				opcion=5;
				break;
		}		
		
	}while(opcion != 5);
	system("CLS");
}

//Funcion que elimina a un usuario
void Menu::MenuCrearUsuario(){
	
	int opcion;
	string 	perfil;
	
	//Abrimos el archivo
	fstream usuariostxt("usuarios.txt", ios::app);
	
	ofstream cajero, caja;
	Usuario empleado; // empleado viene de la clase Usuario
	
	/* Creamos un usuario
	*	- Administrador
	*	- Caja
	*/
	
	do{
	
		cout<<"\t\t\t\t\t\tMenu del super administrador"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\tEscoger el tipo de usuario a crear "<<endl;
		cout<<"\t\t\t\t\t\t1. Administrador"<<endl;
		cout<<"\t\t\t\t\t\t2. caja"<<endl;
		cout<<"\t\t\t\t\t\t3. Atras."<<endl;
		
		cin>>opcion;
		
		//Evaluamos la opcion para escoger el perfil del usuario
		switch(opcion){
			case 1:
				empleado.perfil = "admin";
				break;
			case 2:
				empleado.perfil = "caja";
				break;
			
			default:
				opcion=3;
				break;
		}
		
		system("CLS");
		//Solicitamos los datos
		cout<<"\t\t\t\t\t\tNombre : ";
		cin>>empleado.nombre;
				
		cout<<"\t\t\t\t\t\tApellido : ";
		cin>>empleado.apellido;
				
		cout<<"\t\t\t\t\t\tDireccion : ";
		cin>>empleado.direccion;
				
		cout<<"\t\t\t\t\t\tIdentificacion : ";
		cin>>empleado.identificacion;
				
		cout<<"\t\t\t\t\t\tNacionalidad : ";
		cin>>empleado.nacionalidad;
				
		cout<<"\t\t\t\t\t\tEdad : ";
		cin>>empleado.edad;
				
		cout<<"\t\t\t\t\t\tSucursal : ";
		cin>>empleado.sucursal;
						
		cout<<"\t\t\t\t\t\tCorreo : ";
		cin>>empleado.correo;
				
		cout<<"\t\t\t\t\t\tContrasena : ";
		cin>>empleado.contrasena;
				
		empleado.dineroDisponible = 0;//El saldo por defecto es de $0
				
		if(!usuariostxt.is_open()){//Preguntamos si el archivo no se puede abrir
			usuariostxt.open("usuarios.txt", ios::app);
		}else{
			//Esribimos los datos del usuario registrado
			usuariostxt<<empleado.nombre<<" "<<empleado.apellido<<" "<<empleado.direccion<<" "<<empleado.identificacion<<" "<<empleado.nacionalidad<<" "<<empleado.edad<<" "<<empleado.sucursal<<" "<<empleado.perfil<<" "<<empleado.correo<<" "<<empleado.contrasena<<" "<<0<<" "<<"false"<<endl;
			cout<<"\t\t\t\t\t\tUsuario registrado con exito...."<<endl;
		}
		usuariostxt.close();
		opcion=3;
		Pausa(3);
		system("CLS");
		
	}while(opcion!=3);
}

//Funcion para editar a un usuario
void Menu::MenuEditarUsuario(){
	
	
	int opcion;
	bool encontrado = false;
	string 	clave, perfil_temp;
	
	ifstream usuariostxt;
	ofstream temp;
	
	/* Editar un usuario
	*	- Administrador
	*	- Caja
	*/
	do{
		cout<<"\t\t\t\t\t\tMenu del super administrador"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\tEscoger el tipo de usuario a editar "<<endl;
		cout<<"\t\t\t\t\t\t1. Administrador"<<endl;
		cout<<"\t\t\t\t\t\t2. caja"<<endl;
		cout<<"\t\t\t\t\t\t3. Atras."<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			case 1:
				perfil_temp = "admin";
			    break;
			case 2:
				perfil_temp = "caja";
				break;
			default:
				opcion=3;
				break;
		}
	
		system("CLS");

		string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
				sucursal, perfil, correo, contrasena, dinero, cliente;
				
		//Abrimos los archivos
		usuariostxt.open("usuarios.txt");
		temp.open("temp.txt");
			
		usuariostxt>>nombre;//Leemos el primer campo de la primera linea
		
		cout<<"\t\t\t\t\t\tEscriba la cedula para editar el usuario : ";
		cin>>clave;
				
		while(!usuariostxt.eof()){
				
			usuariostxt>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
			//Preguntamos si la cedula del usuario y el perfil coinciden
			if(clave == identificacion && perfil== perfil_temp){
				
				int opcion2;
				encontrado = true;
				
				do{
					//Mostramos que campo dese aeditar
					cout<<"\t\t\t\t\t\tQue campo desea editar "<<endl;
					cout<<"\t\t\t\t\t\t1. Nombre"<<endl;
					cout<<"\t\t\t\t\t\t2. Apellido"<<endl;
					cout<<"\t\t\t\t\t\t3. Direccion"<<endl;
					cout<<"\t\t\t\t\t\t4. Identificacion"<<endl;
					cout<<"\t\t\t\t\t\t5. Nacionalidad"<<endl;
					cout<<"\t\t\t\t\t\t6. Edad"<<endl;
					cout<<"\t\t\t\t\t\t7. Sucursal"<<endl;
					cout<<"\t\t\t\t\t\t8. Correo"<<endl;
					cout<<"\t\t\t\t\t\t9. Contrasena"<<endl;
					cout<<"\t\t\t\t\t\t10. Atras"<<endl;
						
					cin>>opcion2;
						
					switch(opcion2){
							
						case 1:
							//Editamos el nombre
							cout<<"\t\t\t\t\t\tnombre : ";
							cin>>nombre;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						case 2:
							//Editamos el nombre
							cout<<"\t\t\t\t\t\tapellido : ";
							cin>>apellido;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						case 3:
							//Editamos la dirección
							cout<<"\t\t\t\t\t\tdireccion : ";
							cin>>direccion;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						case 4:
							//Editamos la cedula
							cout<<"\t\t\t\t\t\tidenetificacion : ";
							cin>>identificacion;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						case 5:
							//Editamos la nacionalidad
							cout<<"\t\t\t\t\t\tnacionalidad : ";
							cin>>nacionalidad;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						case 6:
							//Editamos la edad
							cout<<"\t\t\t\t\t\tedad : ";
							cin>>edad;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						case 7:
							//Editamos la sucursal
							cout<<"\t\t\t\t\t\tsucursal : ";
							cin>>sucursal;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						case 8:
							//Editamos el correo
							cout<<"\t\t\t\t\t\tcorreo : ";
							cin>>correo;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						case 9:
							//Editamos el correo
							cout<<"\t\t\t\t\t\tContrasena : ";
							cin>>contrasena;
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
						default:
							temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
							break;
					}
					opcion2=10;			
				}while(opcion2 != 10);
			}else{
				temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;	
					
			}
			nombre="";
			usuariostxt>>nombre;
		}	
		    
		if(!encontrado){
			cout<<"\t\t\t\t\t\tUsuario no encontrado ... espere un momento"<<endl;
		}else{
			cout<<"\t\t\t\t\t\tUsuario editado con exito"<<endl;
		}
		
		usuariostxt.close();
		temp.close();
		remove("usuarios.txt");
		rename("temp.txt", "usuarios.txt");	
		
		
		opcion=3;
		Pausa(3);
		system("CLS");
		    
	}while(opcion!=3);
		
}

//Funcion para consultar usuario
void Menu::MenuConsultarUsuario(){
	
	int opcion;
	bool encontrado = false;
	string 	clave, perfil_temp;
	
	ifstream usuariostxt;
	
	/* Consultar un usuario
	*	- Administrador
	*	- Caja
	*	- Cajero
	*/
	do{
		cout<<"\t\t\t\t\t\tMenu del super administrador"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\tEscoger el tipo de usuario a consultar "<<endl;
		cout<<"\t\t\t\t\t\t1. Administrador"<<endl;
		cout<<"\t\t\t\t\t\t2. caja"<<endl;
		cout<<"\t\t\t\t\t\t3. Atras."<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			case 1:
				perfil_temp = "admin";		
				break;
			case 2:
				perfil_temp = "caja";		
				break;
			default:
				opcion=3;
				break;
		}
		
		system("CLS");

		string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
				sucursal, perfil, correo, contrasena, dinero, cliente;
				
		usuariostxt.open("usuarios.txt");
						
		usuariostxt>>nombre;
		
		cout<<"\t\t\t\t\t\tEscriba la cedula para consultar el usuario : ";
		cin>>clave;
				
		while(!usuariostxt.eof()){
				
			usuariostxt>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
			if(clave == identificacion && perfil== perfil_temp){
				encontrado=true;
				cout<<"Nombre \t\tApellido \t\tDireccion\t\tIdentificacion\t\tCorreo electronico\t\tContrasena\t\tDinero \t"<<endl;
				cout<<"______________________________________________________________________________________________________________________________________________________________"<<endl;
				cout<<""<<nombre<<"\t\t"<<apellido<<"\t\t "<<direccion<<" \t\t\t "<<identificacion<<" \t\t\t"<<correo<<" \t\t "<<contrasena<<" \t\t\t$ "<<dinero<<endl;
				cout<<"______________________________________________________________________________________________________________________________________________________________\n\n"<<endl;
		    }
		        
		    nombre="";
			usuariostxt>>nombre;
		}
		        
		if(!encontrado){
		   	cout<<"\t\t\t\t\t\tUsuario no encontrado"<<endl;
		}
		usuariostxt.close();
		
	}while(opcion!=3);
}

//Funcion para elimnar usuario
void Menu::MenuEliminarUsuario(){
	
	int opcion;
	bool encontrado = false;
	string 	clave, perfil_temp;
	
	ifstream usuariostxt;
	ofstream temp;
	
	/* Editar un usuario
	*	- Administrador
	*	- Caja
	*	- Cajero
	*/
	do{
		cout<<"\t\t\t\t\t\tMenu del super administrador"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\tEscoger el tipo de usuario a eliminar "<<endl;
		cout<<"\t\t\t\t\t\t1. Administrador"<<endl;
		cout<<"\t\t\t\t\t\t2. caja"<<endl;
		cout<<"\t\t\t\t\t\t3. Atras."<<endl;
		
		cin>>opcion;
	
		switch(opcion){
			case 1:
				perfil_temp = "admin";		
				break;
			case 2:
				perfil_temp = "caja";		
				break;
			default:
				opcion=3;
				break;
		}
	
		system("CLS");

		string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
				 	sucursal, perfil, correo, contrasena, dinero, cliente;
				
		usuariostxt.open("usuarios.txt");
		temp.open("temp.txt");
			
		usuariostxt>>nombre;
		cout<<"\t\t\t\t\t\tEscriba la cedula para eliminar a el usuario : ";
		cin>>clave;
				
		while(!usuariostxt.eof()){
				
			usuariostxt>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
			if(clave == identificacion && perfil== perfil_temp){
				encontrado = true;
				cout<<"\t\t\t\t\t\tSe ha eliminado al usuario "<<nombre<<" "<<apellido<<endl;
			}else{
				temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;	
					
			}
			nombre="";
			usuariostxt>>nombre;
		}	
		    
		if(!encontrado){
		   	cout<<"\t\t\t\t\t\tUsuario no encontrado "<<endl;
		}
		usuariostxt.close();
		temp.close();
		remove("usuarios.txt");
		rename("temp.txt", "usuarios.txt");
		
		opcion=3;
		Pausa(3);
		system("CLS");
	}while(opcion!=3);
}


//Funciones del administrador
void Menu::MenuAdministrador(){
	
	int opcion;
	
	do{
		
		cout<<"\t\t\t\t\t\tMenu del Administrador"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\t1. Cliente"<<endl;
		cout<<"\t\t\t\t\t\t2. Cuenta"<<endl;
		cout<<"\t\t\t\t\t\t3. Chequera"<<endl;
		cout<<"\t\t\t\t\t\t4. Asignar dinero a un cajero"<<endl;
		cout<<"\t\t\t\t\t\t5. Salir"<<endl;
		
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
				MenuAsignarDineroCajero();
				break;
			default:
				opcion=5;
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
		
		cout<<"\t\t\t\t\t\tMenu del Administrador - Funciones para clientes"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\t1. Crear cliente"<<endl;
		cout<<"\t\t\t\t\t\t2. Editar cliente"<<endl;
		cout<<"\t\t\t\t\t\t3. Consutar cliente"<<endl;
		cout<<"\t\t\t\t\t\t4. Eliminar cliente"<<endl;
		cout<<"\t\t\t\t\t\t5. Salir"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			case 1:
				// Funcion para crear un cliente
				system("CLS");
				cliente_out.open("clientes.txt", ios::app);
				
				cout<<"\t\t\t\t\t\tIdentificacion : ";
				cin>>cliente.identificacion;
				
				if(this->usuario.verificaCliente(cliente.identificacion)){
					cout<<"Esta cedula ya esta registrada "<<endl;
				}else{
					cout<<"\t\t\t\t\t\tNombre : ";
					cin>>cliente.nombre;
					
					cout<<"\t\t\t\t\t\tApellido : ";
					cin>>cliente.apellido;
					
					cout<<"\t\t\t\t\t\tDireccion : ";
					cin>>cliente.direccion;
					
					cout<<"\t\t\t\t\t\tIdentificacion : "<<cliente.identificacion<<endl;
					
					cout<<"\t\t\t\t\t\tNacionalidad : ";
					cin>>cliente.nacionalidad;
					
					cout<<"\t\t\t\t\t\tEdad : ";
					cin>>cliente.edad;
									
					cliente_out<<cliente.nombre<<" "<<cliente.apellido<<" "<<cliente.direccion<<" "<<cliente.identificacion<<" "<<cliente.nacionalidad<<" "<<cliente.edad<<endl;
					cliente_out.close();
					
					cout<<"\t\t\t\t\t\tCliente registrado exitosamente ..."<<endl;
					Pausa(2);
					system("CLS");	
				}
				
				break;
			case 2:
				// Funcion para editar un cliente
				system("CLS");
					
				cliente_in.open("clientes.txt");
				temp.open("temp.txt");
				
				cliente_in>>nombre;
				cout<<"\t\t\t\t\t\tN° de cedula : ";
				cin>>clave;
				
				while(!cliente_in.eof()){
					
					cliente_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad;
				
					if(clave == identificacion){
						int opcion2;
						encontrado = true;
						do{
							cout<<"\t\t\t\t\t\tQue campo desea editar "<<endl;
							cout<<"\t\t\t\t\t\t1. Nombre"<<endl;
							cout<<"\t\t\t\t\t\t2. Apellido"<<endl;
							cout<<"\t\t\t\t\t\t3. Direccion"<<endl;
							cout<<"\t\t\t\t\t\t4. Identificacion"<<endl;
							cout<<"\t\t\t\t\t\t5. Nacionalidad"<<endl;
							cout<<"\t\t\t\t\t\t6. Edad"<<endl;
							cout<<"\t\t\t\t\t\t7. Atras"<<endl;
						
							cin>>opcion2;
							
							switch(opcion2){
								case 1:
									//Editamos el nombre
									cout<<"\t\t\t\t\t\tnombre : ";
									cin>>nombre;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 2:
									//Editamos el nombre
									cout<<"\t\t\t\t\t\tapellido : ";
									cin>>apellido;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 3:
									//Editamos la dirección
									cout<<"\t\t\t\t\t\tdireccion : ";
									cin>>direccion;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 4:
									//Editamos la cedula
									cout<<"\t\t\t\t\t\tidenetificacion : ";
									cin>>identificacion;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 5:
									//Editamos la nacionalidad
									cout<<"\t\t\t\t\t\tnacionalidad : ";
									cin>>nacionalidad;
									temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
									break;
								case 6:
									//Editamos la edad
									cout<<"\t\t\t\t\t\tedad : ";
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
			    	cout<<"\t\t\t\t\t\tCliente no encontrado "<<endl;
				}else{
					cout<<"\t\t\t\t\t\tSe ha actualizado los datos del cliente exitosamente"<<endl;
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
				cout<<"\t\t\t\t\t\tN° de cedula : ";
				cin>>clave;
				
				while(!cliente_in.eof()){
					
					cliente_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad;
				
					if(clave == identificacion){
						int opcion2;
						encontrado = true;
						cout<<"Nombre \t\tApellido\tDireccion\t\tNacionalidad\t\tIdentificacion\t\tEdad "<<endl;
						cout<<"_________________________________________________________________________________________________________________"<<endl;
						cout<<""<<nombre<<"\t\t"<<apellido<<"\t\t"<<direccion<<" \t\t\t"<<nacionalidad<<"\t\t\t"<<identificacion<<" \t\t "<<edad<<endl;
						cout<<"_________________________________________________________________________________________________________________"<<endl;
					}
					
					nombre="";
					cliente_in>>nombre;
				}
				if(!encontrado){
			    	cout<<"\t\t\t\t\t\tCliente no encontrado "<<endl;
				}
			    cliente_in.close();
				break;
			case 4:
				// Funcion para eliminar un cliente
				system("CLS");
				cliente_in.open("clientes.txt");
				temp.open("temp.txt");
				
				cliente_in>>nombre;
				cout<<"\t\t\t\t\t\tN° de cedula : ";
				cin>>clave;
				
				while(!cliente_in.eof()){
					
					cliente_in>>apellido>>direccion>> identificacion >> nacionalidad>>edad;
				
					if(clave == identificacion){
						encontrado = true;
						cout<<"\t\t\t\t\t\tSe ha eliminado al cliente "<<nombre<<" "<<apellido<<" exitosamente"<<endl;
						Pausa(3);
						system("CLS");
					}else{
						temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<endl;
					}
					nombre="";
					cliente_in>>nombre;
				}
				
				if(!encontrado){
			    	cout<<"\t\t\t\t\t\tCliente no encontrado "<<endl;
			    	Pausa(3);
					system("CLS");
				}
			    cliente_in.close();
			    temp.close();
			    remove("clientes.txt");
			    rename("temp.txt", "clientes.txt");
				break;
			default:
				opcion=5;
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
	
	string num_cuenta, tipo_cuenta, chequera, identificacion, contrasena, confirm, cedula_temp;
	
	do{
		cout<<"\t\t\t\t\t\tMenu del Administrador - Funciones para las cuentas"<<endl;
		cout<<"\t\t\t\t\t\t=========================="<<endl;
		cout<<"\t\t\t\t\t\t1. Crear cuenta"<<endl;
		cout<<"\t\t\t\t\t\t2. Consutar cuenta"<<endl;
		cout<<"\t\t\t\t\t\t3. Salir"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			
			case 1:
				system("CLS");
				cout<<"\t\t\t\t\t\tCedula del clinete : ";
				cin>>identificacion;
				
				cuentas_out.open("cuentas.txt", ios::app);
				
				//Preguntamos si la cedula del cliente esta registrada
				if(!this->usuario.verificaCliente(identificacion)){
					cout<<"\t\t\t\t\t\tEl cliente no esta registrado en la base de datos "<<endl;
				}else{
					
					string tipo_cuenta_temp;
					cout<<"\t\t\t\t\t\tTipo de cuenta "<<endl;
					cout<<"\t\t\t\t\t\t1. Ahorro \t\t\t\t 2. Coriente : ";
					cin>>tipo_cuenta_temp;
					
					if(tipo_cuenta_temp == "2"){//preguntado si el tipo de cuenta es corriente
						tipo_cuenta = "corriente";
						chequera = "si";
					}else{
						tipo_cuenta = "ahorro";
						chequera = "no";
					}		
					
					dinero_disponible = 0;
					
					do{
						system("CLS");
						
						cout<<"\t\t\t\t\t\tContrasena : ";
						cin>>contrasena;
						
						cout<<"\t\t\t\t\t\tConfirmar contrasena : ";
						cin>>confirm;
						
						if(contrasena != confirm){
							cout<<"\t\t\t\t\t\tLas contrasenas no coinciden "<<endl;
							confirm="";
							contrasena="";
						}else{
							encontrado = true;
						}
					}while(!encontrado);
					
					num_cuenta = this->cuenta.ObtenerNumeroCuenta();
					
					cuentas_out<<num_cuenta<<" "<<tipo_cuenta<<" "<<dinero_disponible<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
					
					cout<<"\n\n\t\t\t\t\t\tLa cuenta ha sido creada exitosamente"<<endl;
					cout<<"N° cuenta \t\tTipo de cuenta\t\tSaldo disponible\tChequera\tCedula titula"<<endl;
							cout<<"_________________________________________________________________________________________________________________"<<endl;
							cout<<num_cuenta<<"\t\t\t"<<tipo_cuenta<<"\t\t $."<<dinero_disponible<<"\t\t\t  "<<chequera<<"\t\t"<<identificacion<<endl;
							cout<<"_________________________________________________________________________________________________________________\n\n"<<endl;
				}
				break;
			case 2:
				system("CLS");
				cout<<"\t\t\t\t\t\tCedula del clinete : ";
				cin>>cedula_temp;
				
				cuentas_in.open("cuentas.txt");
				cuentas_in>>num_cuenta;
				if(!this->usuario.verificaCliente(cedula_temp)){
					cout<<"\t\t\t\t\t\tEl cliente no esta registrado en la base de datos "<<endl;
				}else{
					
					cout<<"N° cuenta \tTipo de cuenta\t\tSaldo disponible\tChequera\tCedula titula"<<endl;
					cout<<"_________________________________________________________________________________________________________________"<<endl;
					
					while(!cuentas_in.eof()){
						cuentas_in>>tipo_cuenta>>dinero_disponible>>chequera>>identificacion>>contrasena;
						
						if(cedula_temp == identificacion){
							cout<<num_cuenta<<"\t\t"<<tipo_cuenta<<"\t\t $."<<dinero_disponible<<"\t\t"<<chequera<<"\t\t"<<identificacion<<endl;
							cout<<"_________________________________________________________________________________________________________________\n\n"<<endl;
						}
						num_cuenta="";
						cuentas_in>>num_cuenta;
					}
				}
				break;
			default:
				opcion=3;
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
		cout<<"\t\t\t\t\t\tMenu del Administrador - Funciones para clientes"<<endl;
		cout<<"\t\t\t\t\t\t================================================="<<endl;
		cout<<"\t\t\t\t\t\t1. Crear chequera"<<endl;
		cout<<"\t\t\t\t\t\t2. Consutar chequera"<<endl;
		cout<<"\t\t\t\t\t\t3. Salir"<<endl;
		
		cin>>opcion;
		
		switch(opcion){
			
			case 1:
				system("CLS");
				cout<<"\t\t\t\t\t\tNo. de cuenta  : ";
				cin>>num_cuenta_temp;
				chequeras_out.open("chequeras.txt", ios::app);
				
				if(!this->cuenta.VerificarTipoCuenta("ahorro", num_cuenta_temp)){
					cout<<"\t\t\t\t\t\tLas chequeras solo son para cuentas de tipo corriente"<<endl;	
				}else{
					cout<<"\t\t\t\t\t\tNo. de cedula  : ";
					cin>>num_cedula;
					
					
					if(!this->cuenta.VerificarCuentaCliente(num_cuenta_temp, num_cedula)){
						cout<<"\t\t\t\t\t\tEl numero de cuenta no se asocia con la cedula";
					}else{
						num_chequera = this->cuenta.ObtenerNumeroChequera();
						chequeras_out<<num_chequera<<" "<<num_cuenta_temp<<endl;
						
						cout<<"\n\n\t\t\t\t\t\tChequera registrada con exito"<<endl;
						cout<<"\n\t\t\t\t\t\tN° chequera\t\tN° de cuenta"<<endl;
						cout<<"\t\t\t\t\t\t____________________________________"<<endl;
						cout<<"\t\t\t\t\t\t"<<num_chequera<<"\t\t\t"<<num_cuenta_temp<<endl;
						cout<<"\t\t\t\t\t\t____________________________________\n\n"<<endl;
						
					}
				}
				break;
			case 2:
				system("CLS");
				cout<<"\t\t\t\t\t\tNo. de la chequera  : ";
				cin>>num_chequera_temp;
				chequeras_in.open("chequeras.txt");
				
				chequeras_in>>num_chequera;
				
				while(!chequeras_in.eof()){
					chequeras_in>>num_cuenta_temp;
					
					cout<<"\n\n\t\t\t\t\t\tN° chequera\t\tN° de cuenta"<<endl;
					cout<<"\t\t\t\t\t\t____________________________________"<<endl;
					if(num_chequera_temp == num_chequera){
						
						cout<<"\t\t\t\t\t\t"<<num_chequera<<"\t\t\t"<<num_cuenta_temp<<endl;
						cout<<"\t\t\t\t\t\t____________________________________"<<endl;
						encontrado = true;
					}
					
					num_chequera="";
					chequeras_in>>num_chequera;
				}
				
				if(!encontrado){
					cout<<"\t\t\t\t\t\tEsta chequera no esta registrada "<<endl;
					Pausa(3);
					system("CLS");
				}
				cout<<"\n\n"<<endl;
				break;
			
			default:
				opcion=3;
				break;
		}
		
	}while(opcion !=3);
	system("CLS");
}

//Funcion para agregar dinero a un cajero
void Menu::MenuAsignarDineroCajero(){
	
	system("CLS");
	
	ifstream usuariostxt;
	ofstream temp;
	
	bool encontrado;
	
	int dinero, monto_adicion;
	
	string  nombre, apellido, direccion, identificacion, nacionalidad, edad, 
				 	sucursal, perfil, correo, contrasena, cliente, clave;
				
	usuariostxt.open("usuarios.txt");
			
	usuariostxt>>nombre;
	cout<<"\t\t\t\t\t\tEscriba la cedula del cajero : ";
	cin>>clave;
				
	while(!usuariostxt.eof()){
				
		usuariostxt>>apellido>>direccion>> identificacion >> nacionalidad>>edad>>sucursal>>perfil>>correo>>contrasena>>dinero>>cliente;
				
		if(clave == identificacion && perfil== "caja"){
			
			encontrado = true;
			cout<<"\t\t\t\t\t\tMonto a adicionar : $ ";
			cin>>monto_adicion;
			
			this->usuario.actualizarSaldoCajero(identificacion, monto_adicion, "+");
			cout<<"\t\t\t\t\t\tPor favor espere ..."<<endl;
			Pausa(3);
			cout<<"\t\t\t\t\t\tTransacion creada con exito"<<endl;
			Pausa(3);
			system("CLS");
		}else{
			temp<<nombre<<" "<<apellido<<" "<<direccion<<" "<<identificacion<<" "<<nacionalidad<<" "<<edad<<" "<<sucursal<<" "<<perfil<<" "<<correo<<" "<<contrasena<<" "<<dinero<<" "<<cliente<<endl;
		}
		
		nombre="";
		usuariostxt>>nombre;
	}	
		    
	if(!encontrado){
	   	cout<<"\t\t\t\t\t\tUsuario no encontrado "<<endl;
	}else{
		usuariostxt.close();
		remove("usuarios.txt");
		rename("temp2.txt", "usuarios.txt");
	}
	
}

// Funciones para estetica
void Menu::Pausa(int segundo){
	Sleep(segundo*1000);
}
