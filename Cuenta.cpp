#include "Cuenta.h"

#include <stdlib.h>
#include <time.h>
#include<iostream>
#include<string>
#include<sstream>
#include <fstream> 

using namespace std;

Cuenta::Cuenta()
{
}

//Funcion para actualizar el saldo de una cuenta ya sea deposito o retiro
void Cuenta::ActualizarSaldo(string cuenta,int monto, string operacion){
	
	//Variables a utilizar
	ifstream cuenta_in;
	ofstream temp;
	
	bool encontrado=false;
	int dinero;
	string numero_cuenta, tipo_cuenta, chequera, identificacion, contrasena;
	
	//Abrimos los ficheros
	cuenta_in.open("cuentas.txt");
	temp.open("temp_cuentas.txt");
	
	cuenta_in>>numero_cuenta;//Leemos el primer campo de la primera linea
	
	while(!cuenta_in.eof()){//Recorremos hasta que llegue no halla lineas
		
		cuenta_in>>tipo_cuenta>>dinero>>chequera>>identificacion>>contrasena;//Leemos los campos faltantes
		
		if(cuenta == numero_cuenta){//Preguntamos si la cuenta a buscar coincide con alguna que este en el archivo cuentas.txt
			
			encontrado = true;
			if(operacion == "+"){//Preguntamos que operacion es
				//Si es suma sumamos el saldo y el monto recibido
				temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<(dinero + monto)<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
			}else{
				//Si es resta restamos en saldo por el monto recibido
				temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<(dinero - monto)<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
			}

		}else{// Si no se encuentra la cuenta escribimos los datos normales sin modificarlos
			temp<<numero_cuenta<<" "<<tipo_cuenta<<" "<<dinero<<" "<<chequera<<" "<<identificacion<<" "<<contrasena<<endl;
		}
		
		numero_cuenta=""; //Limpiamos la variable
		cuenta_in>>numero_cuenta; // Leemos nuevamente el primer campo de la nueva liena
	}
	
	//cerramos los archivos
	cuenta_in.close();
	temp.close();
	
	remove("cuentas.txt");// Removemos el archivo
	rename("temp_cuentas.txt","cuentas.txt");// Remplazamos en archivo cuentax.txt para que quede con los nuevos registros
	
}

//Funcon que genera un valor aleatorio para el numero de la cuenta
string Cuenta::ObtenerNumeroCuenta(){
	
	//Variables a utilizar
	int i;
	bool encontrado = false;
	string numeroC, cuenta;
	
	stringstream convertidor;//Auxiliar q nos ayuda a convertir de int a string
	
	srand(time(NULL));
	
	do{	//Generamos un numero hasta que sea unico del resto
		for(i=0;i<5;i++){//Iteramos en 5 repeticiones para crear un numerode 5
		
			int tem = 1 +rand() % (9 - 1);//Generamos un numero aleatorio
			
			convertidor << tem;//le asignamos el valor del int al auxiliar
			numeroC = convertidor.str();//conertimos de int a string
			cuenta = numeroC; //almacenamos el valos
		}
		
		if(VerificarNumeroCuenta(cuenta)){// Preguntamos si el numero generado es igual a otro que este registrado
			encontrado = true;
		}
	}while(encontrado);//Repetimos este ciclo mientras sea verdadero
		
	return cuenta;//retornamos el numero de 5 digitos
}


//Es similar a la de arriba pero lo que cambia es que el numero es para la chequera
string Cuenta::ObtenerNumeroChequera(){
	
	int i;
	bool encontrado = false;
	string numeroC, cuenta;
	stringstream convertidor;
	
	srand(time(NULL));
	
	do{	
		for(i=0;i<5;i++){
			int tem = 1 +rand() % (9 - 1);
			
			convertidor << tem;
			numeroC = convertidor.str();
			cuenta = numeroC; 		
		}
		
		if(VerificarNumeroCuenta(cuenta)){
			encontrado = true;
		}
	}while(encontrado);
		
	return cuenta;
}

//Funcion para obtener el numero de la cuenta desde la chequera
string Cuenta::ObtenerNumeroCuentaPorChequera(string chequera){
	
	//Variables a utilizar
	ifstream chequerastxt;
	
    string	numChequera, numCuenta;
    
	chequerastxt.open("chequeras.txt");//Abrimos el archivo
	
	chequerastxt>>numChequera;	
	
    while(!chequerastxt.eof()){
		
		chequerastxt>>numCuenta;
				
		if(chequera == numChequera){//Preguntamos si la chequera a buscar coincide con alguna que este en el archivo chequeras.txt
			return numCuenta;
		}
		
		numChequera="";
		chequerastxt>>numChequera;
    }
    chequerastxt.close();	
    
    return "";
    
}

//Funcion para obtener el dinero de una cuenta
int Cuenta::ObtenerDineroDisponible(string cuenta){
	
	ifstream cuentastxt;
	
	int dinero;
    string	numCuenta, tipo_cuenta, chequera, identificacion;
    
	cuentastxt.open("cuentas.txt"); //abrimos el archivo
	
	cuentastxt>>numCuenta;	
	
    while(!cuentastxt.eof()){
		
		cuentastxt>>tipo_cuenta>>dinero>>chequera>>identificacion;	
			
		if(cuenta == numCuenta){
			
			return dinero;//si se ecuentra la cuenta retornamos el dinero que esta contiene
		}
		numCuenta="";
		cuentastxt>>numCuenta;
    }
    cuentastxt.close();	
    
    return 0;
    
}

//funcion que verifica si un cheque pertenece a una chequera
bool Cuenta::VerificarCheque(string chequera, string cheque){
	
	ifstream chequestxt;
	string numero_cheque, monto, num_chequera, estado;
	
	chequestxt.open("cheques.txt");
	chequestxt>>numero_cheque;
	
	while(!chequestxt.eof()){
		
		chequestxt>>monto>>num_chequera>>estado;
		
		if(chequera == num_chequera && cheque == numero_cheque){
			//si el cheque pertenece retornamos true
			return true;
		}
		
		numero_cheque="";
		chequestxt>>numero_cheque;
	}
	
	return false;//Si no hay coincidencia retornamos false
}

//funcion que verifica si una chequera existe
bool Cuenta::VerificarNumeroChequera(string Nchequera){
	
	ifstream chequerastxt;
	
    string	numChequera, numCuenta;
	chequerastxt.open("chequeras.txt");
	chequerastxt>>numChequera;	
	
    while(!chequerastxt.eof()){
		
		chequerastxt>>numCuenta;		
		if(Nchequera == numChequera){
			//si la chequera existe retornamos true
			return true;
		}
		
		numChequera="";
		chequerastxt>>numChequera;
    }
    chequerastxt.close();	
    
    return false;//Si no hay coincidencia retornamos false
}

//funcion que verifica si una cuenta exite
bool Cuenta::VerificarNumeroCuenta(string Ncuenta){
	
	ifstream cuentastxt;
	
    string	numCuenta, tipo_cuenta, dinero, chequera, identificacion;
	cuentastxt.open("cuentas.txt");
	cuentastxt>>numCuenta;	
	
    while(!cuentastxt.eof()){
		
		cuentastxt>>tipo_cuenta>>dinero>>chequera>>identificacion;		
		if(Ncuenta == numCuenta){
			return true;
		}
		numCuenta="";
		cuentastxt>>numCuenta;
    }
    cuentastxt.close();	
    
    return false;//Si no hay coincidencia retornamos false
}


//funcion que verifica si una cuente pertenece a su tipo
bool Cuenta::VerificarTipoCuenta(string tipo, string cuenta){
	
	ifstream cuentastxt;
	string	numCuenta, tipo_cuenta, dinero, chequera, identificacion;
	cuentastxt.open("cuentas.txt");
	
	cuentastxt>>numCuenta;
	
	while(!cuentastxt.eof()){
		
		cuentastxt>>tipo_cuenta>>dinero>>chequera>>identificacion;
				
		if(cuenta == numCuenta && tipo_cuenta == "corriente"){
			//si la cuenta pertenece retornamos true
			return true;
		}
		numCuenta="";
		cuentastxt>>numCuenta;
    }
    cuentastxt.close();	
    
    return false;//Si no hay coincidencia retornamos false
}

bool Cuenta::VerificarCuentaCliente(string cuenta, string cedula){
	
	ifstream cuentastxt;
	string	numCuenta, tipo_cuenta, dinero, chequera, identificacion;
	cuentastxt.open("cuentas.txt");
	cuentastxt>>numCuenta;
	
	while(!cuentastxt.eof()){
		
		cuentastxt>>tipo_cuenta>>dinero>>chequera>>identificacion;	
			
		if(cuenta == numCuenta && identificacion == cedula){
			
			return true;
		}
		numCuenta="";
		cuentastxt>>numCuenta;
    }
    cuentastxt.close();	
    
    return false;//Si no hay coincidencia retornamos false
}
Cuenta::~Cuenta()
{
}

