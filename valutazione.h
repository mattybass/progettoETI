#ifndef __VALUTAZIONE_H__
#define __VALUTAZIONE_H__
#include <map>
#include <vector>
#include <string>
#include "persona.h"
using namespace std;

class Valutazione {
private:
	Persona* modello;
	Persona* paziente;
	map<int, pair<float,float>> pesi; //i pesi maggiori di un tot determinano quali joint andremo a prendere in considerazione
    float completezzaesercizio;
	vector<int> angoliDiscriminanti_zenit;
    vector<int> angoliDiscriminanti_azimut;
	map<int, ValutazioneSJ> valutazioneSingleJoint;
public:
	Valutazione(Persona* _paz, Persona* _mod);
	void percentualeEsCompletato();
	void valutaSingleJoint(int _joint);
};
#endif

