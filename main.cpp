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
	p.processa_angolo(2);
	Persona p2("spallagomitoModello60fps.json");
	p2.processa_angolo(2);
	Valutazione v(&p, &p2);
	v.valutaSingleJoint(2);
	v.stampavalutazione();
    return 0;
}
