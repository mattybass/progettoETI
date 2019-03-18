#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
#include "valutazione.h"


int main(int argc, char** argv) {
	
    Persona p(60,"modellomattyspalla.json");
	p.processa_esercizio();
	Persona p2(60,"B2movim.json");
	p2.processa_esercizio();
	Valutazione v(&p2, &p);
	v.test();
	system("PAUSE");

    return 0;
}
