#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
#include "valutazione.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
	Persona p("spallagomitoModello60fps.json");
	p.mediamobile_angolo(2, 30);
	p.mediamobile_angolo(2, 30);
	p.maxminFind_angolo(2, 50);
	p.maxminClean_angolo(2, 5, 20);
	Persona p2("spallagomitoModello60fps.json");
	p2.mediamobile_angolo(2, 30);
	p2.mediamobile_angolo(2, 30);
	p2.maxminFind_angolo(2, 50);
	p2.maxminClean_angolo(2, 5, 20);
	Valutazione v(&p, &p2);
	v.valutaSingleJoint(2);
	v.stampavalutazione();
    return 0;
}
