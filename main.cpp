#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
#include "valutazione.h"

int main(int argc, char** argv) {
	Persona p(60,"Modello.json");
	p.processa_esercizio();
	Persona p2(60,"Paziente_corretto.json");
	p2.processa_esercizio();
	p.stampaFile_maxmin(2,"");
	Valutazione v(&p2, &p);
	v.valutaTotale();
	v.stampavalutazione("output", "valutazioni", 0.3);
	cout << "ELABORAZIONE COMPLETATA!" << endl;
	system("PAUSE");
	return 0;
}

