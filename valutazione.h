#ifndef __VALUTAZIONE_H__
#define __VALUTAZIONE_H__
#include <map>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include "persona.h"
#include "valutazioneSJ.h"
#include "valutazioneRJ.h"
#include "utility.h"

using namespace std;

/*
TODO
-fixare bug movimento angolo che ha solo inizio e fine
*/

class Valutazione {
private:
    //DATA
	Persona* modello;
	Persona* paziente;
    //VARIABILI PESISITICHE
	map<int, pair<float,float>> pesi; //i pesi maggiori di un tot determinano quali joint andremo a prendere in considerazione <Zenit,Azimut>
    vector<int> angoliDiscriminanti_zenit; //servono solo per calcolare il completamento dell esercizio
    vector<int> angoliDiscriminanti_azimut; //idem
    //VALUTAZIONI VARIE
    float completezzaesercizio;
	float accuratezzaEsercizio;
	set<int> numeri_angoli;
	map<int, ValutazioneSJ> valutazioneSingleJoint;
	map<int, ValutazioneRJ> valutazioneRelazioneJoint;
public:
    //COSTRUTTORI
	Valutazione(Persona* _paz, Persona* _mod);
    //SET & INSERT
    void insert_angolidiscriminati_zenit(int _angolo);
    void insert_angolidiscriminati_azimut(int _angolo);
	void popola_pesiRJ(int _angolo);
    //GET
    map<int, pair<float,float>> get_pesi()const;
    //METODI DI VALUTAZIONE
	void percentualeEsCompletato();
	void valutaSingleJoint(int _joint);
	void valutaRelationJoint(int _joint); //deve essere passato il joint di cui si vuole fare la valutazione!
	float valutaTotale();
    //METODI DI TEST
	void stampavalutazione(string percorso_file, string name, float peso_stampa); //stampa un file txt contenente tutte le valutazioni
};
#endif


