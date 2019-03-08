#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
    Persona p("output_01-03-2019 10_09_52.json");	
	p.mediamobile_angolo(2, 30);
	p.mediamobile_angolo(2, 30);
	p.maxminFind_angolo(2, 10);
	p.stampaConsole_maxmin(2);
	system("PAUSE");

	return 0;
}
