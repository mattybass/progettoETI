#include "valutazione.h"

Valutazione::Valutazione(Persona* _paz, Persona* _mod) {
	paziente = _paz;
	modello = _mod;
	//creo map per l'esercizio che andremo a valutare
	//ogni esercizio prevede una map diversa, quindi bisognerebbe prevedere un inserimento iniziale
	//nel sistema da parte del medico.
	pesi[1] = pair<float,float>(0.05,0.05);
	pesi[2] = pair<float,float>(0.35,0.15);
	pesi[3] = pair<float, float>(0.15, 0.15);
	pesi[5] = pair<float, float>(0.05, 0.05);
	pesi[6] = pair<float, float>(0.0, 0.0);
	pesi[8] = pair<float, float>(0.0, 0.0);
	pesi[9] = pair<float, float>(0.0, 0.0);
	pesi[11] = pair<float, float>(0.0, 0.0);
	pesi[12] = pair<float, float>(0.0, 0.0);
}
void Valutazione::percentualeEsCompletato() {
    vector<int>::const_iterator iterV;
    int numero_maxminModello=0;
    int numero_maxminPaziente=0;

	for(iterV=angoliDiscriminanti_zenit.begin();iterV!=angoliDiscriminanti_zenit.end();++iterV){
        numero_maxminModello=numero_maxminModello+ modello->get_numeroMaxMin_zenit((*iterV));
		numero_maxminPaziente=numero_maxminPaziente+paziente->get_numeroMaxMin_zenit((*iterV));
	}

	for(iterV=angoliDiscriminanti_azimut.begin();iterV!=angoliDiscriminanti_azimut.end();++iterV){
        numero_maxminModello=numero_maxminModello+ modello->get_numeroMaxMin_azimut((*iterV));
		numero_maxminPaziente=numero_maxminPaziente+paziente->get_numeroMaxMin_azimut((*iterV));
    }
    completezzaesercizio=(float)(numero_maxminPaziente/numero_maxminModello)*100;
}

void Valutazione::valutaSingleJoint(int _joint){
	list<Angolo> listaModellozenit;
	list<Angolo> listaPazientezenit;
	list<Angolo> listaModelloazimut;
	list<Angolo> listaPazienteazimut;
	list<Angolo>::iterator itermodello; //iteratore che scorre le map di maxmin di zenit e azimut del modello
	list<Angolo>::iterator iterpaziente; //iteratore che scorre le map di maxmin di zenit e azimut del paziente
		listaModellozenit = (*modello).get_valorimaxmin_zenit(_joint);
		listaPazientezenit = (*paziente).get_valorimaxmin_zenit(_joint);
		listaModelloazimut = (*modello).get_valorimaxmin_azimut(_joint);
		listaPazienteazimut = (*paziente).get_valorimaxmin_azimut(_joint);
		//VALUTAZIONE ZENIT
		itermodello = listaModellozenit.begin();
		iterpaziente = listaPazientezenit.begin();
	
}

void Valutazione::insert_angolidiscriminati_zenit(int _angolo){
    angoliDiscriminanti_zenit.push_back(_angolo);
}

void Valutazione::insert_angolidiscriminati_azimut(int _angolo){
    angoliDiscriminanti_azimut.push_back(_angolo);
}
