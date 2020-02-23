#ifndef DATA_H
#define DATA_H
#include <string>

using namespace std;

class Data{
	// Descripció: guarda el dia, mes i any d’una data
	// Invariant: dia/mes/any és una data correcta
public:
	// CONSTRUCTORS
	Data();
	// Pre: cert;
	// Post: és la data 1/1/2001
	Data(int d, int m, int a);
	// Pre: cert;
	// Post: és la data d/m/a en cas que sigui correcta i 1/1/2001 en cas contrari
	// CONSULTORS
	void mostrar(int format) const;
	// Pre: format 1 o 2;
	// Post: mostra la data actual en format d/m/a o d–mes–a
	bool es_menor(const Data &d) const;
	// Pre: cert;
	// Post: cert si d és una data posterior a l'actual, fals altrament
	// MODIFICADORS
	void llegir(int format);
	// Pre: format 1 o 2;
	// Post: llegeix dates en format AAAAMMDD o d m a, fins a llegir-ne una	de correcta
private:
	// ATRIBUTS
	int a_dia;
	int a_mes;
	int a_any;
	// CONSTANTS DE CLASSE
	static const int MESOS_ANY = 12;
	static const int DIES_MES[];
	static const string NOM_MES[];
	// FUNCIONS DE CLASSE
	static bool es_data_valida(int dia, int mes, int any);
	// Pre: cert;
	// Post: retorna cert si dia/mes/any formen una data vàlida en el calendari gregorià(entre els any 1600 i 4000)
	static bool aniversari(Data data1,Data data2);
};

#endif // data