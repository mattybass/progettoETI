#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
    Persona p("spallagomitoModello60fps.json");	
	p.mediamobile_angolo(3, 30);
	p.mediamobile_angolo(3, 30);
	p.maxminFind_angolo(3, 50);
	p.maxminClean_angolo(3);
	p.stampaConsole_maxmin(3);
	p.stampaFile_angolo(3,"modello");

	p.stampaFile_maxmin_zenit(3,"zenit");
	p.stampaFile_maxmin_azimut(3, "azimut");
	
	system("PAUSE");

	return 0;
}
