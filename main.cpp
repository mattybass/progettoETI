#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
    Persona p("output_01-03-2019 10_09_52.json");
//	p.stampa_angoli(2);
	cout << endl;	
//	p.stampa_max(1);
//	p.stampa_max(2);
/*	p.stampa_max(3);
	p.stampa_max(4);
	p.stampa_max(5);*/
	p.kamazenit_lista(2,60,50,200);
	p.kamaazimut_lista(2, 60, 50, 200);
//	p.stampa_angoli(2,);
	p.stampafile_angoli(2,"ciao");
//	p.test_persona(2);


	return 0;
}
