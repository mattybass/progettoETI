#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
    Persona p("output_01-03-2019 10_09_52.json");	

	
/*	p.kamazenit_lista(2, 40, 10, 200);
	p.kamaazimut_lista(2, 40, 10, 100);//10,2,30
	p.stampafile_angoli(2, "k2");*/
	
	/*p.kamazenit_lista(2, 80, 16, 240);
	p.kamaazimut_lista(2, 80, 16, 240);//10,2,30
	p.stampafile_angoli(2, "k3");*/

	p.mediamobile_angolo(2, 30);
	p.mediamobile_angolo(2, 30);
	p.stampaFile_angolo(2, "m1");
//	p.maxminFind_angolo(2, 30);



//	p.stampa_angoli(2,);
//	p.stampafile_angoli(2,"beckmatty");
//	p.test_persona(2);
//	p.popola_max_min_angolo_zenit(2, 5);
//	p.popola_max_min_angolo_azimut(2, 5);
//	p.stampa_max(2);

	return 0;
}
