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

string Cuenta::ObtenerNumeroCuenta(){
	
	int i;
	bool encontrado = false;
	string numeroC, cuenta;
	stringstream convertidor;
	
	srand(time(NULL));
	
	do{	
		for(i=0;i<5;i++){
			int tem = 1 +rand() % (11 - 1);
			
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

string Cuenta::ObtenerNumeroChequera(){
	
	int i;
	bool encontrado = false;
	string numeroC, cuenta;
	stringstream convertidor;
	
	srand(time(NULL));
	
	do{	
		for(i=0;i<5;i++){
			int tem = 1 +rand() % (11 - 1);
			
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

//
bool Cuenta::VerificarNumeroChequera(string Nchequera){
	
	ifstream chequerastxt;
	
    string	numChequera, numCuenta;
	chequerastxt.open("chequeras.txt");
	chequerastxt>>numChequera;	
	
    while(!chequerastxt.eof()){
		
		chequerastxt>>numCuenta;		
		if(Nchequera == numChequera){
			return true;
		}
		
		numChequera="";
		chequerastxt>>numChequera;
    }
    chequerastxt.close();	
    
    return false;
}

//
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
    
    return false;
}

bool Cuenta::VerificarTipoCuenta(string tipo, string cuenta){
	ifstream cuentastxt;
	string	numCuenta, tipo_cuenta, dinero, chequera, identificacion;
	cuentastxt.open("cuentas.txt");
	cuentastxt>>numCuenta;
	
	while(!cuentastxt.eof()){
		
		cuentastxt>>tipo_cuenta>>dinero>>chequera>>identificacion;		
		if(cuenta == numCuenta && tipo_cuenta == "corriente"){
			return true;
		}
		numCuenta="";
		cuentastxt>>numCuenta;
    }
    cuentastxt.close();	
    
    return false;
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
    
    return false;
}
Cuenta::~Cuenta()
{
}
