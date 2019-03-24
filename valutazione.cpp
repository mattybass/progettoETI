#include "valutazione.h"


Valutazione::Valutazione(Persona* _paz, Persona* _mod) {
	paziente = _paz;
	modello = _mod;
	//ogni esercizio prevede una map diversa, quindi bisognerebbe prevedere un inserimento iniziale
	//nel sistema da parte del medico.
	pesi[1] = pair<float,float>(0.1,0.05);
	pesi[2] = pair<float,float>(0.5,0.10);
	pesi[3] = pair<float, float>(0.1, 0.05);
	pesi[5] = pair<float, float>(0.05, 0.05);
	pesi[6] = pair<float, float>(0.0, 0.0);
	pesi[8] = pair<float, float>(0.0, 0.0);
	pesi[9] = pair<float, float>(0.0, 0.0);
	pesi[11] = pair<float, float>(0.0, 0.0);
	pesi[12] = pair<float, float>(0.0, 0.0);
	numeri_angoli.insert(1);
	numeri_angoli.insert(2);
	numeri_angoli.insert(3);
	numeri_angoli.insert(5);
	numeri_angoli.insert(6);
	numeri_angoli.insert(8);
	numeri_angoli.insert(9);
	numeri_angoli.insert(11);
	numeri_angoli.insert(12);
}

void Valutazione::percentualeEsCompletato() {
    vector<int>::const_iterator iterV;
    int numero_maxminModello=0;
    int numero_maxminPaziente=0;

	for(iterV=angoliDiscriminanti_zenit.begin();iterV!=angoliDiscriminanti_zenit.end();++iterV){
		numero_maxminModello+=modello->get_numeroMaxMin_zenit(*iterV);
		numero_maxminPaziente+=paziente->get_numeroMaxMin_zenit(*iterV);
	}
	for(iterV=angoliDiscriminanti_azimut.begin();iterV!=angoliDiscriminanti_azimut.end();++iterV){
        numero_maxminModello+=modello->get_numeroMaxMin_azimut(*iterV);
		numero_maxminPaziente+=paziente->get_numeroMaxMin_azimut(*iterV);
    }
    if (numero_maxminModello != 0){
		completezzaesercizio = ((float)numero_maxminPaziente / (float)numero_maxminModello) * 100;
	}
}

void Valutazione::insert_angolidiscriminati_zenit(int _angolo) {
	angoliDiscriminanti_zenit.push_back(_angolo);
}

void Valutazione::insert_angolidiscriminati_azimut(int _angolo) {
	angoliDiscriminanti_azimut.push_back(_angolo);
}

void Valutazione::stampavalutazione(string percorso_file, string name, float peso_stampa) {
	string l = percorso_file + "/" + name + ".txt";
	ofstream file;
	file.open(l);
	map<int, pair<float, float>>::iterator iter;
	file << "Esercizio completato al " << completezzaesercizio <<"%!"<< endl<<endl;
    for (iter = pesi.begin(); iter != pesi.end(); ++iter) {
			if ((iter->second.first + iter->second.second) >= peso_stampa) //peso stampa serve per far capire di quali joint si vuole la relazione approfondita e quali no
			{
				file << "RELAZIONE APPROFONDITA SULL'ARTICOLAZIONE NUMERO " << iter->first << endl;
				valutazioneSingleJoint[iter->first].stampa_file_accurato(file);
				file << endl;
				valutazioneRelazioneJoint[iter->first].stampa_file_accurato(file);
			}
			else {
				file << "RELAZIONE NON APPROFONDITA SULL'ARTICOLAZIONE NUMERO " << iter->first <<endl;
				valutazioneSingleJoint[iter->first].stampa_file_non_accurato(file);
				file << endl;
				valutazioneRelazioneJoint[iter->first].stampa_file_non_accurato(file);
			}
			file << endl;
	}
	file.close();
}

map<int, pair<float,float>> Valutazione::get_pesi()const{
    return pesi;
}

void Valutazione::popola_pesiRJ(int _angolo){
    map<int, pair<float,float>>::const_iterator iterM;
	float somma = 0.0;
    float pesoredistribuitoA=0.0;
    float pesoredistribuitoZ=0.0;

	pair<float, float> temp = pesi.find(_angolo)->second;
	pesi.erase(_angolo); //elimino da pesi l'angolo che sto considerando
    
	for(iterM=pesi.begin();iterM!=pesi.end();++iterM){
		somma += iterM->second.second + iterM->second.first;
    }
	for (iterM = pesi.begin(); iterM != pesi.end(); ++iterM) {
		pesoredistribuitoZ = (iterM->second.first) / somma;
		pesoredistribuitoA = (iterM->second.second)/ somma;
		valutazioneRelazioneJoint[_angolo].insert_pesiredzenit(iterM->first, pesoredistribuitoZ);
		valutazioneRelazioneJoint[_angolo].insert_pesiredazimut(iterM->first, pesoredistribuitoA);
	}
	pesi[_angolo] = temp; //riaggiungo l'angolo per eventuali altri calcoli!
}

float Valutazione::valutaTotale(){
	map<int, pair<float, float>>::iterator iter; //serve per scorrere la map di pesi
	double sum_SJ = 0.0;
	double sum_RJ = 0.0;
	float peso_zenit;
	float peso_azimut;
	insert_angolidiscriminati_zenit(2);
	percentualeEsCompletato();
	valutaSingleJoint(1);
	valutaRelationJoint(1);
	valutaSingleJoint(2);
	valutaRelationJoint(2);
	valutaSingleJoint(3);
	valutaRelationJoint(3);
	valutaSingleJoint(5);
	valutaRelationJoint(5);
	valutaSingleJoint(6);
	valutaRelationJoint(6);
	valutaSingleJoint(8);
	valutaRelationJoint(8);
	valutaSingleJoint(9);
	valutaRelationJoint(9);
	valutaSingleJoint(11);
	valutaRelationJoint(11);
	valutaSingleJoint(12);
	valutaRelationJoint(12);
	for (iter = pesi.begin(); iter != pesi.end(); ++iter) {
		peso_zenit = iter->second.first;
		peso_azimut = iter->second.second;
		sum_SJ += valutazioneSingleJoint[iter->first].get_accuratezza_azimut()*peso_azimut + valutazioneSingleJoint[iter->first].get_accuratezza_zenit()*peso_zenit;
		sum_RJ += valutazioneRelazioneJoint[iter->first].get_accuratezza_azimut()*peso_azimut + valutazioneRelazioneJoint[iter->first].get_accuratezza_zenit()*peso_zenit;
	}
	return 0.75*(sum_SJ)+0.25*(sum_RJ);
}

void Valutazione::valutaRelationJoint(int _joint) {
	list<Angolo> listaPaziente;
	list<Angolo> listaModello;
	list<Angolo>::iterator itermodello;
	list<Angolo>::iterator itermodello2;
	list<Angolo>::iterator iterpaziente2;
	list<Angolo>::iterator iterpaziente;
	set<int>::iterator siter;
	int sizemod, sizepaz;
	int nframepaziente, nframemodello;
	numeri_angoli.erase(_joint);
	double diff;
	float percentuale;
	//ZENIT
	listaPaziente = (*paziente).get_valorimaxmin_zenit(_joint); //contiene i punti chiave che devo confrontare sugli altri angoli!
	listaModello = (*modello).get_valorimaxmin_zenit(_joint);
	sizemod = listaModello.size();
	sizepaz = listaPaziente.size();
	if(sizemod==2){//significa che nel modello questo è un angolo stazionario! confronto solo angolo iniziale e finale 
		if (sizepaz == 2) {//situazione top! passo al confronto diretto di inizio e fine di tutti gli altri joint
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			while (iterpaziente != listaPaziente.end() && itermodello != listaModello.end()) {//vado avanti finchè ho punti!
				nframepaziente = iterpaziente->get_numeroframe();
				nframemodello = itermodello->get_numeroframe();
				for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
					diff = (*modello).get_angoloMedia_zenit(*siter, nframemodello) - (*paziente).get_angoloMedia_zenit(*siter, nframemodello);
					percentuale = ((float)(*paziente).get_angoloMedia_zenit(*siter, nframemodello) / (float)(*modello).get_angoloMedia_zenit(*siter, nframemodello)) * 100;
					percentuale = normalizza_percentuale(percentuale);
					valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(*siter, diff, percentuale);
				}
				++iterpaziente;
				++itermodello;
			}
		}
		else { //passo alla valutazione solo di punto iniziale e finale 
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			itermodello2 = listaModello.end();
			iterpaziente2 = listaPaziente.end();
			--itermodello2;
			--iterpaziente2;
			nframepaziente = iterpaziente->get_numeroframe();
			nframemodello = itermodello->get_numeroframe();
			for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
				diff = (*modello).get_angoloMedia_zenit(*siter, nframemodello) - (*paziente).get_angoloMedia_zenit(*siter, nframemodello);
				percentuale = ((float)(*paziente).get_angoloMedia_zenit(*siter, nframemodello) / (float)(*modello).get_angoloMedia_zenit(*siter, nframemodello)) * 100;
				percentuale = normalizza_percentuale(percentuale);
				valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(*siter, diff, percentuale);
			}
			nframepaziente = iterpaziente2->get_numeroframe();
			nframemodello = itermodello2->get_numeroframe();
			for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
				diff = (*modello).get_angoloMedia_zenit(*siter, nframemodello) - (*paziente).get_angoloMedia_zenit(*siter, nframemodello);
				percentuale = ((float)(*paziente).get_angoloMedia_zenit(*siter, nframemodello) / (float)(*modello).get_angoloMedia_zenit(*siter, nframemodello)) * 100;
				percentuale = normalizza_percentuale(percentuale);
				valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(*siter, diff, percentuale);
			}
		}
	}
	else {//il modello ha più di due punti chiave
		if (sizepaz == 2) {
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			itermodello2 = listaModello.end();
			iterpaziente2 = listaPaziente.end();
			--itermodello2;
			--iterpaziente2;
			nframepaziente = iterpaziente->get_numeroframe();
			nframemodello = itermodello->get_numeroframe();
			for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
				diff = (*modello).get_angoloMedia_zenit(*siter, nframemodello) - (*paziente).get_angoloMedia_zenit(*siter, nframemodello);
				percentuale = ((float)(*paziente).get_angoloMedia_zenit(*siter, nframemodello) / (float)(*modello).get_angoloMedia_zenit(*siter, nframemodello)) * 100;
				percentuale = normalizza_percentuale(percentuale);
				valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(*siter, diff, percentuale);
			}
			nframepaziente = iterpaziente2->get_numeroframe();
			nframemodello = itermodello2->get_numeroframe();
			for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
				diff = (*modello).get_angoloMedia_zenit(*siter, nframemodello) - (*paziente).get_angoloMedia_zenit(*siter, nframemodello);
				percentuale = ((float)(*paziente).get_angoloMedia_zenit(*siter, nframemodello) / (float)(*modello).get_angoloMedia_zenit(*siter, nframemodello)) * 100;
				percentuale = normalizza_percentuale(percentuale);
				valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(*siter, diff, percentuale);
			}
		}
		else {
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			while (iterpaziente != listaPaziente.end() && itermodello != listaModello.end()) {//vado avanti finchè ho punti!
				nframepaziente = iterpaziente->get_numeroframe();
				nframemodello = itermodello->get_numeroframe();
				for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
					diff = (*modello).get_angoloMedia_zenit(*siter, nframemodello) - (*paziente).get_angoloMedia_zenit(*siter, nframemodello);
					percentuale = ((float)(*paziente).get_angoloMedia_zenit(*siter, nframemodello) / (float)(*modello).get_angoloMedia_zenit(*siter, nframemodello)) * 100;
					percentuale = normalizza_percentuale(percentuale);
					valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(*siter, diff, percentuale);
				}
				++iterpaziente;
				++itermodello;
			}
		}
	}
	//AZIMUT
	listaPaziente = (*paziente).get_valorimaxmin_azimut(_joint); //contiene i punti chiave che devo confrontare sugli altri angoli!
	listaModello = (*modello).get_valorimaxmin_azimut(_joint);
	sizemod = listaModello.size();
	sizepaz = listaPaziente.size();
	if (sizemod == 2) {//significa che nel modello questo è un angolo stazionario! confronto solo angolo iniziale e finale 
		if (sizepaz == 2) {//situazione top! passo al confronto diretto di inizio e fine di tutti gli altri joint
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			while (iterpaziente != listaPaziente.end() && itermodello != listaModello.end()) {//vado avanti finchè ho punti!
				nframepaziente = iterpaziente->get_numeroframe();
				nframemodello = itermodello->get_numeroframe();
				for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
					diff = (*modello).get_angoloMedia_azimut(*siter, nframemodello) - (*paziente).get_angoloMedia_azimut(*siter, nframemodello);
					percentuale = ((float)(*paziente).get_angoloMedia_azimut(*siter, nframemodello) / (float)(*modello).get_angoloMedia_azimut(*siter, nframemodello)) * 100;
					percentuale = normalizza_percentuale(percentuale);
					valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(*siter, diff, percentuale);
				}
				++iterpaziente;
				++itermodello;
			}
		}
		else { //passo alla valutazione solo di punto iniziale e finale 
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			itermodello2 = listaModello.end();
			iterpaziente2 = listaPaziente.end();
			--itermodello2;
			--iterpaziente2;
			nframepaziente = iterpaziente->get_numeroframe();
			nframemodello = itermodello->get_numeroframe();
			for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
				diff = (*modello).get_angoloMedia_azimut(*siter, nframemodello) - (*paziente).get_angoloMedia_azimut(*siter, nframemodello);
				percentuale = ((float)(*paziente).get_angoloMedia_azimut(*siter, nframemodello) / (float)(*modello).get_angoloMedia_azimut(*siter, nframemodello)) * 100;
				percentuale = normalizza_percentuale(percentuale);
				valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(*siter, diff, percentuale);
			}
			nframepaziente = iterpaziente2->get_numeroframe();
			nframemodello = itermodello2->get_numeroframe();
			for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
				diff = (*modello).get_angoloMedia_azimut(*siter, nframemodello) - (*paziente).get_angoloMedia_azimut(*siter, nframemodello);
				percentuale = ((float)(*paziente).get_angoloMedia_azimut(*siter, nframemodello) / (float)(*modello).get_angoloMedia_azimut(*siter, nframemodello)) * 100;
				percentuale = normalizza_percentuale(percentuale);
				valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(*siter, diff, percentuale);
			}
		}
	}
	else {//il modello ha più di due punti chiave
		if (sizepaz == 2) {
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			itermodello2 = listaModello.end();
			iterpaziente2 = listaPaziente.end();
			--itermodello2;
			--iterpaziente2;
			nframepaziente = iterpaziente->get_numeroframe();
			nframemodello = itermodello->get_numeroframe();
			for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
				diff = (*modello).get_angoloMedia_azimut(*siter, nframemodello) - (*paziente).get_angoloMedia_azimut(*siter, nframemodello);
				percentuale = ((float)(*paziente).get_angoloMedia_azimut(*siter, nframemodello) / (float)(*modello).get_angoloMedia_azimut(*siter, nframemodello)) * 100;
				percentuale = normalizza_percentuale(percentuale);
				valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(*siter, diff, percentuale);
			}
			nframepaziente = iterpaziente2->get_numeroframe();
			nframemodello = itermodello2->get_numeroframe();
			for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
				diff = (*modello).get_angoloMedia_azimut(*siter, nframemodello) - (*paziente).get_angoloMedia_azimut(*siter, nframemodello);
				percentuale = ((float)(*paziente).get_angoloMedia_azimut(*siter, nframemodello) / (float)(*modello).get_angoloMedia_azimut(*siter, nframemodello)) * 100;
				percentuale = normalizza_percentuale(percentuale);
				valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(*siter, diff, percentuale);
			}
		}
		else {
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			while (iterpaziente != listaPaziente.end() && itermodello != listaModello.end()) {//vado avanti finchè ho punti!
				nframepaziente = iterpaziente->get_numeroframe();
				nframemodello = itermodello->get_numeroframe();
				for (siter = numeri_angoli.begin(); siter != numeri_angoli.end(); ++siter) {
					diff = (*modello).get_angoloMedia_azimut(*siter, nframemodello) - (*paziente).get_angoloMedia_azimut(*siter, nframemodello);
					percentuale = ((float)(*paziente).get_angoloMedia_azimut(*siter, nframemodello) / (float)(*modello).get_angoloMedia_azimut(*siter, nframemodello)) * 100;
					percentuale = normalizza_percentuale(percentuale);
					valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(*siter, diff, percentuale);
				}
				++iterpaziente;
				++itermodello;
			}
		}
	}
	popola_pesiRJ(_joint);
	valutazioneRelazioneJoint[_joint].calcola_media_discostamento();
	valutazioneRelazioneJoint[_joint].calcola_accuratezza();
	numeri_angoli.insert(_joint);
}

void Valutazione::valutaSingleJoint(int _joint) {
	list<Angolo> listaModello;
	list<Angolo> listaPaziente;
	list<Angolo>::iterator itermodello; 
	list<Angolo>::iterator iterpaziente; 
	list<Angolo>::iterator itermodello2;
	list<Angolo>::iterator iterpaziente2;
	int fpsmodello, fpspaziente; //numero frame per secondo di modello e paziente
	fpsmodello = (*modello).get_numeroFramePerSecondo();
	fpspaziente = (*paziente).get_numeroFramePerSecondo();
	listaModello = (*modello).get_valorimaxmin_zenit(_joint);
	listaPaziente = (*paziente).get_valorimaxmin_zenit(_joint);
	double diff = 0.0;
    float percentuale=0.0;
	int nframepaziente, nframemodello;
	//ZENIT
	if (listaModello.size() == 2) {//significa che quell'angolo è stazionario nel modello!
		if (listaPaziente.size() == 2) {//passo a considerare punto iniziale e finale
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			while (iterpaziente != listaPaziente.end() && itermodello != listaModello.end()) {  //confronta solo tanti punti chiave quanti sono quelli del modello
				nframepaziente = iterpaziente->get_numeroframe();
				nframemodello = itermodello->get_numeroframe();
				diff = modello->get_angoloMedia_zenit(_joint, nframemodello) - paziente->get_angoloMedia_zenit(_joint, nframepaziente);
				percentuale = (((float)(modello->get_angoloMedia_zenit(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_zenit(_joint, nframepaziente)))*100.0);
				percentuale = normalizza_percentuale(percentuale);
				valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff, percentuale);
				++iterpaziente;
				++itermodello;
			}
			
		}
		else {
			int n = listaPaziente.size() - listaModello.size();
			itermodello = listaModello.begin(); //contiene il punto iniziale modello
			iterpaziente = listaPaziente.begin(); //contiene il punto iniziale paziente
			itermodello2 = listaModello.end();
			--itermodello2; //contiene il punto finale modello
			iterpaziente2 = listaPaziente.end();
			--iterpaziente2; //contiene il punto finale paziente
			nframepaziente = iterpaziente->get_numeroframe();
			nframemodello = itermodello->get_numeroframe();
			diff = modello->get_angoloMedia_zenit(_joint, nframemodello) - paziente->get_angoloMedia_zenit(_joint, nframepaziente);
			percentuale = (((float)(modello->get_angoloMedia_zenit(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_zenit(_joint, nframepaziente)))*100.0);
			percentuale = normalizza_percentuale(percentuale);
			valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff, percentuale);

			nframepaziente = iterpaziente2->get_numeroframe();
			nframemodello = itermodello2->get_numeroframe();
			diff = modello->get_angoloMedia_zenit(_joint, nframemodello) - paziente->get_angoloMedia_zenit(_joint, nframepaziente);
			percentuale = (((float)(modello->get_angoloMedia_zenit(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_zenit(_joint, nframepaziente)))*100.0);
			percentuale = normalizza_percentuale(percentuale);

			valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff, percentuale);
			valutazioneSingleJoint[_joint].set_diffpunti_zenit(n); //setto il valore di punti in più sul paziente
		}
    }
	else {
		if (listaPaziente.size() == 2) {
			int n = listaPaziente.size() - listaModello.size();
			itermodello = listaModello.begin(); //contiene il punto iniziale modello
			iterpaziente = listaPaziente.begin(); //contiene il punto iniziale paziente
			itermodello2 = listaModello.end();
			--itermodello2; //contiene il punto finale modello
			iterpaziente2 = listaPaziente.end();
			--iterpaziente2; //contiene il punto finale paziente

			nframepaziente = iterpaziente->get_numeroframe();
			nframemodello = itermodello->get_numeroframe();
			diff = modello->get_angoloMedia_zenit(_joint, nframemodello) - paziente->get_angoloMedia_zenit(_joint, nframepaziente);
			percentuale = (((float)(modello->get_angoloMedia_zenit(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_zenit(_joint, nframepaziente)))*100.0);
			percentuale = normalizza_percentuale(percentuale);
			valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff, percentuale);

			nframepaziente = iterpaziente2->get_numeroframe();
			nframemodello = itermodello2->get_numeroframe();
			diff = modello->get_angoloMedia_zenit(_joint, nframemodello) - paziente->get_angoloMedia_zenit(_joint, nframepaziente);
			percentuale = (((float)(modello->get_angoloMedia_zenit(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_zenit(_joint, nframepaziente)))*100.0);
			percentuale = normalizza_percentuale(percentuale);
			valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff, percentuale);

			valutazioneSingleJoint[_joint].set_diffpunti_zenit(n); //setto il valore di punti in meno sul paziente
		}
		else {
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			int n = listaPaziente.size() - listaModello.size();
			while (iterpaziente != listaPaziente.end() && itermodello != listaModello.end()) {  //confronta solo tanti punti chiave quanti sono quelli del modello
				nframepaziente = iterpaziente->get_numeroframe();
				nframemodello = itermodello->get_numeroframe();
				diff = modello->get_angoloMedia_zenit(_joint, nframemodello) - paziente->get_angoloMedia_zenit(_joint, nframepaziente);
				percentuale = (((float)(modello->get_angoloMedia_zenit(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_zenit(_joint, nframepaziente)))*100.0);
				percentuale = normalizza_percentuale(percentuale);
				valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff, percentuale);
				++iterpaziente;
				++itermodello;
			}
			valutazioneSingleJoint[_joint].set_diffpunti_zenit(n); //setto il valore di punti in più o in meno sul paziente
		}
	}
	//passo a calcolare le velocità con lo stesso metodo di prima per ora
	itermodello = listaModello.begin();
	iterpaziente = listaPaziente.begin();
	itermodello2 = itermodello;
	iterpaziente2 = iterpaziente;
	++itermodello2;
	++iterpaziente2;
	double secondi_movimento = 0; //conta il numero di secondi che passano tra una posizione chiave e un'altra
    while (iterpaziente2!=listaPaziente.end()&&itermodello2!=listaModello.end()) { 
		secondi_movimento = (double)((*itermodello2).get_numeroframe() - (*itermodello).get_numeroframe())/(double)fpsmodello;
		valutazioneSingleJoint[_joint].insert_duratamovimentimodello_zenit(secondi_movimento);
		secondi_movimento = (double)((*iterpaziente2).get_numeroframe() - (*iterpaziente).get_numeroframe())/(double)fpspaziente;
		valutazioneSingleJoint[_joint].insert_duratamovimentipaziente_zenit(secondi_movimento);
		++itermodello;
		++itermodello2;
		++iterpaziente;
		++iterpaziente2;
	}

	//AZIMUT
	listaModello = (*modello).get_valorimaxmin_azimut(_joint);
	listaPaziente = (*paziente).get_valorimaxmin_azimut(_joint);
	if (listaModello.size() == 2) {//significa che quell'angolo è stazionario nel modello!
		if (listaPaziente.size() == 2) {//passo a considerare punto iniziale e finale
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			while (iterpaziente != listaPaziente.end() && itermodello != listaModello.end()) {  //confronta solo tanti punti chiave quanti sono quelli del modello
				nframepaziente = iterpaziente->get_numeroframe();
				nframemodello = itermodello->get_numeroframe();
				diff = modello->get_angoloMedia_azimut(_joint, nframemodello) - paziente->get_angoloMedia_azimut(_joint, nframepaziente);
				percentuale = (((float)(modello->get_angoloMedia_azimut(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_azimut(_joint, nframepaziente)))*100.0);
				percentuale = normalizza_percentuale(percentuale);
				valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff, percentuale);
				++iterpaziente;
				++itermodello;
			}
		}
		else {
			int n = listaPaziente.size() - listaModello.size();
			itermodello = listaModello.begin(); //contiene il punto iniziale modello
			iterpaziente = listaPaziente.begin(); //contiene il punto iniziale paziente
			itermodello2 = listaModello.end();
			--itermodello2; //contiene il punto finale modello
			iterpaziente2 = listaPaziente.end();
			--iterpaziente2; //contiene il punto finale paziente

			nframepaziente = iterpaziente->get_numeroframe();
			nframemodello = itermodello->get_numeroframe();
			diff = modello->get_angoloMedia_azimut(_joint, nframemodello) - paziente->get_angoloMedia_azimut(_joint, nframepaziente);
			percentuale = (((float)(modello->get_angoloMedia_azimut(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_azimut(_joint, nframepaziente)))*100.0);
			percentuale = normalizza_percentuale(percentuale);
			valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff, percentuale);

			nframepaziente = iterpaziente2->get_numeroframe();
			nframemodello = itermodello2->get_numeroframe();
			diff = modello->get_angoloMedia_azimut(_joint, nframemodello) - paziente->get_angoloMedia_azimut(_joint, nframepaziente);
			percentuale = (((float)(modello->get_angoloMedia_azimut(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_azimut(_joint, nframepaziente)))*100.0);
			percentuale = normalizza_percentuale(percentuale);
			valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff, percentuale);
			valutazioneSingleJoint[_joint].set_diffpunti_azimut(n); //setto il valore di punti in più sul paziente
		}
	}
	else {
		if (listaPaziente.size() == 2) {
			int n = listaPaziente.size() - listaModello.size();
			itermodello = listaModello.begin(); //contiene il punto iniziale modello
			iterpaziente = listaPaziente.begin(); //contiene il punto iniziale paziente
			itermodello2 = listaModello.end();
			--itermodello2; //contiene il punto finale modello
			iterpaziente2 = listaPaziente.end();
			--iterpaziente2; //contiene il punto finale paziente

			nframepaziente = iterpaziente->get_numeroframe();
			nframemodello = itermodello->get_numeroframe();
			diff = modello->get_angoloMedia_azimut(_joint, nframemodello) - paziente->get_angoloMedia_azimut(_joint, nframepaziente);
			percentuale = (((float)(modello->get_angoloMedia_azimut(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_azimut(_joint, nframepaziente)))*100.0);
			percentuale = normalizza_percentuale(percentuale);
			valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff, percentuale);

			nframepaziente = iterpaziente2->get_numeroframe();
			nframemodello = itermodello2->get_numeroframe();
			diff = modello->get_angoloMedia_azimut(_joint, nframemodello) - paziente->get_angoloMedia_azimut(_joint, nframepaziente);
			percentuale = (((float)(modello->get_angoloMedia_azimut(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_azimut(_joint, nframepaziente)))*100.0);
			percentuale = normalizza_percentuale(percentuale);
			valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff, percentuale);

			valutazioneSingleJoint[_joint].set_diffpunti_azimut(n); //setto il valore di punti in meno sul paziente
		}
		else {
			itermodello = listaModello.begin();
			iterpaziente = listaPaziente.begin();
			int n = listaPaziente.size() - listaModello.size();
			while (iterpaziente != listaPaziente.end() && itermodello != listaModello.end()) {  //confronta solo tanti punti chiave quanti sono quelli del modello
				nframepaziente = iterpaziente->get_numeroframe();
				nframemodello = itermodello->get_numeroframe();
				diff = modello->get_angoloMedia_azimut(_joint, nframemodello) - paziente->get_angoloMedia_azimut(_joint, nframepaziente);
				percentuale = (((float)(modello->get_angoloMedia_azimut(_joint, nframemodello)) / (float)(paziente->get_angoloMedia_azimut(_joint, nframepaziente)))*100.0);
				percentuale = normalizza_percentuale(percentuale);
				valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff, percentuale);
				++iterpaziente;
				++itermodello;
			}
			valutazioneSingleJoint[_joint].set_diffpunti_azimut(n); //setto il valore di punti in più o in meno sul paziente
		}
	}
	//per ora la velocita la calcolo come prima
	itermodello = listaModello.begin();
	iterpaziente = listaPaziente.begin();
	itermodello2 = itermodello;
	iterpaziente2 = iterpaziente;
	++itermodello2;
	++iterpaziente2;
	while (iterpaziente2 != listaPaziente.end()&&itermodello2!=listaModello.end()) {
		secondi_movimento = (double)((*itermodello2).get_numeroframe() - (*itermodello).get_numeroframe())/(double)fpsmodello;
		valutazioneSingleJoint[_joint].insert_duratamovimentimodello_azimut(secondi_movimento);
		secondi_movimento = (double)((*iterpaziente2).get_numeroframe() - (*iterpaziente).get_numeroframe())/(double)fpspaziente;
		valutazioneSingleJoint[_joint].insert_duratamovimentipaziente_azimut(secondi_movimento);
		++itermodello;
		++itermodello2;
		++iterpaziente;
		++iterpaziente2;
	}
	valutazioneSingleJoint[_joint].media_deltadist();
	valutazioneSingleJoint[_joint].insert_deltatime_azimut();
	valutazioneSingleJoint[_joint].insert_deltatime_zenit();
	valutazioneSingleJoint[_joint].media_deltatime();
	valutazioneSingleJoint[_joint].calcola_accuratezza();
}
