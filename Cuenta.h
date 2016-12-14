#ifndef CUENTA_H
#define CUENTA_H
#include <cstdlib>
#include <iostream>

using namespace std;
class Cuenta
{
	public:
		Cuenta();
		string ObtenerNumeroCuenta();
		string ObtenerNumeroChequera();
		
		bool VerificarNumeroCuenta(string Ncuenta);
		bool VerificarNumeroChequera(string Nchequera);
		bool VerificarTipoCuenta(string tipo, string cuenta);
		bool VerificarCuentaCliente(string cuenta, string cedula);
		
		~Cuenta();
	protected:
};

#endif
