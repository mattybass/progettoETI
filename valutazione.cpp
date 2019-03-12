#include "valutazione.h"

Valutazione::Valutazione(Persona* _paz, Persona* _mod) {
	paziente = _paz;
	modello = _mod;
	//creo map per l'esercizio che andremo a valutare
	//ogni esercizio prevede una map diversa, quindi bisognerebbe prevedere un inserimento iniziale
	//nel sistema da parte del medico.
	pesi[1] = pair<float,float>(0.05,0.05);
	pesi[2] = pair<float,float>(0.35,0.15);
	pesi[3] = 0.3;
	pesi[5] = 0.1;
	pesi[6] = 0.0;
	pesi[8] = 0.0;
	pesi[9] = 0.0;
	pesi[11] = 0.0;
	pesi[12] = 0.0;
}
void Valutazione::percentualeEsCompletato() {

}