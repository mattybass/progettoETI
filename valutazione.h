#ifndef __VALUTAZIONE_H__
#define __VALUTAZIONE_H__
#include <map>
#include <string>
using namespace std;

class Valutazione {
private:
	Persona* modello;
	Persona* paziente;
	map<int, float> pesi; //i pesi maggiori di un tot determinano quali joint andremo a prendere in considerazione
public:
	Valutazione(Persona* _paz, Persona* _mod);
	void percentualeEsCompletato();
};
#endif

