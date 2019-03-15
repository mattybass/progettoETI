#ifndef __VALUTAZIONE_H__
#define __VALUTAZIONE_H__
#include <map>
#include <vector>
#include <string>
#include "persona.h"
#include "valutazioneSJ.h"
#include "valutazioneRJ.h"

using namespace std;

class Valutazione {
private:
    //DATA
	Persona* modello;
	Persona* paziente;
    //VARIABILI PESISITICHE
	map<int, pair<float,float>> pesi; //i pesi maggiori di un tot determinano quali joint andremo a prendere in considerazione <Zenit,Azimut>
    vector<int> angoliDiscriminanti_zenit;
    vector<int> angoliDiscriminanti_azimut;
    //VALUTAZIONI VARIE
    float completezzaesercizio;
	map<int, ValutazioneSJ> valutazioneSingleJoint;
public:
    //COSTRUTTORI
	Valutazione(Persona* _paz, Persona* _mod);
    //SET & INSERT
    void insert_angolidiscriminati_zenit(int _angolo);
    void insert_angolidiscriminati_azimut(int _angolo);
    //GET
    map<int, pair<float,float>> get_pesi()const;
    //METODI DI VALUTAZIONE
	void percentualeEsCompletato();
	void valutaSingleJoint(int _joint);
    void popola_pesiRJ(int _angolo);

	//METODI DI TEST
	void stampavalutazione();
};
#endif


