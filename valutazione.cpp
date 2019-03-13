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

void Valutazione::insert_angolidiscriminati_zenit(int _angolo) {
	angoliDiscriminanti_zenit.push_back(_angolo);
}

void Valutazione::insert_angolidiscriminati_azimut(int _angolo) {
	angoliDiscriminanti_azimut.push_back(_angolo);
}

void Valutazione::valutaSingleJoint(int _joint){
	//in questa funzione bisogna entrare se il numero di max min del paziente è minore o uguale a quello del modello
	list<Angolo> listaModellozenit;
	list<Angolo> listaPazientezenit;
	list<Angolo> listaModelloazimut;
	list<Angolo> listaPazienteazimut;
	list<Angolo>::iterator itermodello; //iteratore che scorre le map di maxmin di zenit e azimut del modello
	list<Angolo>::iterator iterpaziente; //iteratore che scorre le map di maxmin di zenit e azimut del paziente
	
	//ZENIT bisogna fare in modo di inserire punto di inizio e punto di fine
	listaModellozenit = (*modello).get_valorimaxmin_zenit(_joint);
	listaPazientezenit = (*paziente).get_valorimaxmin_zenit(_joint);
	itermodello = listaModellozenit.begin();
	iterpaziente = listaPazientezenit.begin();
	double diff = 0.0;
	int diff_temp = 0;
	if (listaPazientezenit.size() == listaModellozenit.size()) {
		//c'è lo stesso numero di max e min
		while (itermodello != listaModellozenit.end()){ //una vale l'altra in quanto hanno la stessa dimensione
			diff = abs((*itermodello).get_zenit() - (*iterpaziente).get_zenit());
			diff_temp = (*itermodello).get_numeroframe() - (*iterpaziente).get_numeroframe();
			valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff);
			valutazioneSingleJoint[_joint].insert_deltatime_zenit(diff_temp);
			itermodello++;
			iterpaziente++;
		}
	}
	else {  //vuol dire che l'esercizio non è stato completato!
		while (iterpaziente != listaPazientezenit.end()) { //una vale l'altra in quanto hanno la stessa dimensione
			diff = abs((*itermodello).get_zenit() - (*iterpaziente).get_zenit());
			diff_temp = (*itermodello).get_numeroframe() - (*iterpaziente).get_numeroframe();
			valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff);
			valutazioneSingleJoint[_joint].insert_deltatime_zenit(diff_temp);
			itermodello++;
			iterpaziente++;
		}
	}
	//AZIMUT
	listaModelloazimut = (*modello).get_valorimaxmin_azimut(_joint);
	listaPazienteazimut = (*paziente).get_valorimaxmin_azimut(_joint);
	itermodello = listaModelloazimut.begin();
	iterpaziente = listaPazienteazimut.begin();
	if (listaPazienteazimut.size() == listaModelloazimut.size()) {
		//c'è lo stesso numero di max e min
		while (itermodello != listaModelloazimut.end()) { //una vale l'altra in quanto hanno la stessa dimensione
			diff = abs((*itermodello).get_azimut() - (*iterpaziente).get_azimut());
			diff_temp = (*itermodello).get_numeroframe() - (*iterpaziente).get_numeroframe();
			valutazioneSingleJoint[_joint].insert_deltatime_azimut(diff_temp);
			valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff);
			itermodello++;
			iterpaziente++;
		}
	}
	else {
		while (iterpaziente != listaPazienteazimut.end()) { //qua ho imposto che ci siano meno max min nella lista del paziente 
			diff = abs((*itermodello).get_azimut() - (*iterpaziente).get_azimut());
			diff_temp = (*itermodello).get_numeroframe() - (*iterpaziente).get_numeroframe();
			valutazioneSingleJoint[_joint].insert_deltatime_azimut(diff_temp);
			valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff);
			itermodello++;
			iterpaziente++;
		}
	}
}
void Valutazione::stampavalutazione() {
	map<int, ValutazioneSJ>::iterator iter;
	for (iter = valutazioneSingleJoint.begin(); iter != valutazioneSingleJoint.end(); ++iter) {
		(iter->second).stampa();
	}
}
