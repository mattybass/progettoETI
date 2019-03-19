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
	Persona p2(60,"Bprova2.json");
	p2.processa_esercizio();
	Valutazione v(&p2, &p);
	v.valutaTotale();
	v.stampavalutazione("matlab","valutazioni");
	system("PAUSE");

    return 0;
}
