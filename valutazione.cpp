#include "valutazione.h"


Valutazione::Valutazione(Persona* _paz, Persona* _mod) {
	paziente = _paz;
	modello = _mod;
	//creo map per l'esercizio che andremo a valutare
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
		numero_maxminModello+=modello->get_numeroMaxMin_zenit((*iterV));
		numero_maxminPaziente+=paziente->get_numeroMaxMin_zenit((*iterV));
	}
	for(iterV=angoliDiscriminanti_azimut.begin();iterV!=angoliDiscriminanti_azimut.end();++iterV){
        numero_maxminModello+=modello->get_numeroMaxMin_azimut((*iterV));
		numero_maxminPaziente+=paziente->get_numeroMaxMin_azimut((*iterV));
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

void Valutazione::valutaSingleJoint(int _joint){
	//in questa funzione bisogna entrare se il numero di max min del paziente � minore o uguale a quello del modello
	list<Angolo> listaModellozenit;
	list<Angolo> listaPazientezenit;
	list<Angolo> listaModelloazimut;
	list<Angolo> listaPazienteazimut;
	list<Angolo>::iterator itermodello; //iteratore che scorre le map di maxmin di zenit e azimut del modello
	list<Angolo>::iterator iterpaziente; //iteratore che scorre le map di maxmin di zenit e azimut del paziente
	list<Angolo>::iterator itermodello2;
	list<Angolo>::iterator iterpaziente2;
	list<Angolo>::iterator itermodellofine;
	map<int, ValutazioneSJ>::iterator miter;
	int nframemodello, nframepaziente;
	nframemodello = (*modello).get_numeroFramePerSecondo();
	nframepaziente = (*paziente).get_numeroFramePerSecondo();
	listaModellozenit = (*modello).get_valorimaxmin_zenit(_joint);
	listaPazientezenit = (*paziente).get_valorimaxmin_zenit(_joint);
	itermodello = listaModellozenit.begin();
	iterpaziente = listaPazientezenit.begin();
	itermodellofine = listaModellozenit.end();
	itermodellofine--;
	double diff = 0.0;
    float percentuale=0.0;
	while (iterpaziente != listaPazientezenit.end()) { 
		diff = (*itermodello).get_zenit() - (*iterpaziente).get_zenit();
        percentuale=(((float)(iterpaziente->get_zenit())/(float)(itermodello->get_zenit()))*100.0);
        
        if(percentuale>100.0){
            if(percentuale>200.0){
                percentuale=0;
            }else{
				percentuale = 200 - percentuale;
            }
        }
		valutazioneSingleJoint[_joint].insert_deltadist_zenit(diff,percentuale);
		++iterpaziente;
		if(itermodello!=itermodellofine)//se arriva alla fine resta sul punto finale
		++itermodello;
	}

	itermodello = listaModellozenit.begin();
	iterpaziente = listaPazientezenit.begin();
	itermodello2 = itermodello;
	iterpaziente2 = iterpaziente;
	++itermodello2;
	++iterpaziente2;

	double secondi_movimento = 0; //conta il numero di secondi che passano tra una posizione chiave e un'altra
    while (iterpaziente2!=listaPazientezenit.end()) { 
		secondi_movimento = (double)((*itermodello2).get_numeroframe() - (*itermodello).get_numeroframe())/(double)nframemodello;
		valutazioneSingleJoint[_joint].insert_duratamovimentimodello_zenit(secondi_movimento);
		secondi_movimento = (double)((*iterpaziente2).get_numeroframe() - (*iterpaziente).get_numeroframe())/(double)nframepaziente;
		valutazioneSingleJoint[_joint].insert_duratamovimentipaziente_zenit(secondi_movimento);
		if (itermodello2 != itermodellofine) {//si blocca sull'ultimo movimento
			++itermodello;
			++itermodello2;
		}
		++iterpaziente;
		++iterpaziente2;
	}

	//AZIMUT
	listaModelloazimut = (*modello).get_valorimaxmin_azimut(_joint);
	listaPazienteazimut = (*paziente).get_valorimaxmin_azimut(_joint);
	itermodello = listaModelloazimut.begin();
	iterpaziente = listaPazienteazimut.begin();
	itermodellofine = listaModelloazimut.end();
	--itermodellofine;
	
	while (iterpaziente != listaPazienteazimut.end()&&itermodello!=listaModelloazimut.end()) {
		diff = (*itermodello).get_azimut() - (*iterpaziente).get_azimut(); //una misura positiva significa non arrivare di diff gradi alla posizione
        percentuale=(((float)(iterpaziente->get_azimut())/(float)(itermodello->get_azimut()))*100.0);
        
            if(percentuale>100.0){
                if(percentuale>200.0){
                    percentuale=0;
                }else{
                    percentuale=200-percentuale;
                }
            }
            valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff,percentuale);      //una negativa significa superarla di diff gradi
			if (itermodello != itermodellofine)//se arriva alla fine resta sul punto finale
				++itermodello;
            ++iterpaziente;

    }
	itermodello = listaModelloazimut.begin();
	iterpaziente = listaPazienteazimut.begin();
	itermodello2 = itermodello;
	iterpaziente2 = iterpaziente;
	++itermodello2;
	++iterpaziente2;

	while (iterpaziente2 != listaPazienteazimut.end()&&itermodello2!=listaModelloazimut.end()) {
		secondi_movimento = (double)((*itermodello2).get_numeroframe() - (*itermodello).get_numeroframe())/(double)nframemodello;
		valutazioneSingleJoint[_joint].insert_duratamovimentimodello_azimut(secondi_movimento);
		secondi_movimento = (double)((*iterpaziente2).get_numeroframe() - (*iterpaziente).get_numeroframe())/(double)nframepaziente;
		valutazioneSingleJoint[_joint].insert_duratamovimentipaziente_azimut(secondi_movimento);
		if (itermodello2 != itermodellofine) {//si blocca sull'ultimo movimento
			++itermodello;
			++itermodello2;
		}
		++iterpaziente;
		++iterpaziente2;
	}
	valutazioneSingleJoint[_joint].media_deltadist();//calcola la media di scostamenti
	valutazioneSingleJoint[_joint].insert_deltatime_azimut();
	valutazioneSingleJoint[_joint].insert_deltatime_zenit();
	valutazioneSingleJoint[_joint].media_deltatime();
	valutazioneSingleJoint[_joint].calcola_accuratezza();
}

void Valutazione::valutaRelationJoint(int _joint) {
	list<Angolo> listaPaziente;
	list<Angolo> listaModello;
	list<Angolo>::iterator itermodello;
	list<Angolo>::iterator itermodello2;
	list<Angolo>::iterator iterpazienteinizio;
	list<Angolo>::iterator iterpazientefine;
	list<Angolo>::iterator iterpaziente;
	set<int>::iterator iter; //lo uso per scorrere il set contenente i numeri di angoli da elaborare
	double diff;
	int frame_iniz_modello, frame_fin_modello;
	int n_frame, n_joint;
	float percentuale = 0.0;
	int n_frame_mod, n_frame_paz;
	listaPaziente = (*paziente).get_valorimaxmin_zenit(_joint);
	listaModello = (*modello).get_valorimaxmin_zenit(_joint);
	frame_iniz_modello = (*(listaModello.begin())).get_numeroframe();
	itermodello2 = listaModello.end();
	--itermodello2;
	frame_fin_modello = (*itermodello2).get_numeroframe();
	numeri_angoli.erase(_joint); //elimino il joint sul quale mi sono focalizzato
	//ZENIT
	itermodello = listaModello.begin();
	for (iterpaziente = listaPaziente.begin(); iterpaziente != listaPaziente.end(); ++iterpaziente) {
		    n_frame_paz = (*iterpaziente).get_numeroframe();  //frame del primo punto chiave
			if (itermodello != listaModello.end()) {
				n_frame_mod = (*itermodello).get_numeroframe();
				++itermodello;
			}
		else //se esco tengo il punto finale ! sarebbe da non entrarci proprio in questa funzione!
			n_frame_mod = frame_fin_modello;
		if (n_frame_paz > frame_iniz_modello&&n_frame_paz < frame_fin_modello) {
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, n_frame_mod); //angolo del modello corrispondente al punto chiave del paziente
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame_paz); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_zenit() - ang_paziente.get_zenit());
				percentuale = (((float)(ang_paziente.get_zenit() / (float)(ang_modello.get_zenit())))*100.0);
				if (percentuale > 100.0) {
					if (percentuale > 200.0) {
						percentuale = 0;
					}
					else {
						percentuale = 200 - percentuale;
					}
				}
				valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(n_joint, diff,percentuale);
			}
		}
		else if (n_frame_paz < frame_iniz_modello) { //vuol dire che il frame di inizio del paziente è antecedente a quello del modello
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, frame_iniz_modello); //confronto con il punto iniziale del modello
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame_paz); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_zenit() - ang_paziente.get_zenit());
				percentuale = (((float)(ang_paziente.get_zenit() / (float)(ang_modello.get_zenit())))*100.0);
				if (percentuale > 100.0) {
					if (percentuale > 200.0) {
						percentuale = 0;
					}
					else {
						percentuale = 200 - percentuale;
					}
				}
				valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(n_joint, diff,percentuale);
			}
		}
		else if (n_frame_paz > frame_fin_modello) {
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, frame_fin_modello); //angolo del modello corrispondente al punto chiave del paziente
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame_paz); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_zenit() - ang_paziente.get_zenit());
				percentuale = (((float)(ang_paziente.get_zenit() / (float)(ang_modello.get_zenit())))*100.0);
				if (percentuale > 100.0) {
					if (percentuale > 200.0) {
						percentuale = 0;
					}
					else {
						percentuale = 200 - percentuale;
					}
				}
				valutazioneRelazioneJoint[_joint].insert_deltadist_zenit(n_joint, diff,percentuale);
			}
		}

	}
	listaPaziente = (*paziente).get_valorimaxmin_azimut(_joint);
	listaModello = (*modello).get_valorimaxmin_azimut(_joint);
	frame_iniz_modello = (*(listaModello.begin())).get_numeroframe();
	itermodello2 = listaModello.end();
	--itermodello2;
	frame_fin_modello = (*itermodello2).get_numeroframe();
	itermodello = listaModello.begin();
	//AZIMUT
	for (iterpaziente = listaPaziente.begin(); iterpaziente != listaPaziente.end(); ++iterpaziente) {
			n_frame_paz = (*iterpaziente).get_numeroframe(); //frame del primo punto chiave
		if (itermodello != listaModello.end()){
			n_frame_mod = (*itermodello).get_numeroframe();
			++itermodello;
		}
		else //se esco tengo il punto finale ! sarebbe da non entrarci proprio in questa funzione!
			n_frame_mod = frame_fin_modello;
		//devo passare alla valutazione degli angoli restanti!
		if (n_frame_paz > frame_iniz_modello&&n_frame_paz < frame_fin_modello) {
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, n_frame_mod); //angolo del modello corrispondente al punto chiave del paziente
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame_paz); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_azimut() - ang_paziente.get_azimut());
				percentuale = (((float)(ang_paziente.get_azimut() / (float)(ang_modello.get_azimut())))*100.0);
				if (percentuale > 100.0) {
					if (percentuale > 200.0) {
						percentuale = 0;
					}
					else {
						percentuale = 200 - percentuale;
					}
				}
				valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(n_joint, diff, percentuale);
			}
		}
		else if (n_frame_paz < frame_iniz_modello) { //vuol dire che il frame di inizio del paziente è antecedente a quello del modello
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, frame_iniz_modello); //confronto con il punto iniziale del modello
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame_paz); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_azimut() - ang_paziente.get_azimut());
				percentuale = (((float)(ang_paziente.get_azimut() / (float)(ang_modello.get_azimut())))*100.0);
				if (percentuale > 100.0) {
					if (percentuale > 200.0) {
						percentuale = 0;
					}
					else {
						percentuale = 200 - percentuale;
					}
				}
				valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(n_joint, diff,percentuale);
			}
		}
		else if (n_frame_paz > frame_fin_modello) {
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, frame_fin_modello); //angolo del modello corrispondente al punto chiave del paziente
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame_paz); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_azimut() - ang_paziente.get_azimut());
				percentuale = (((float)(ang_paziente.get_azimut() / (float)(ang_modello.get_azimut())))*100.0);
				if (percentuale > 100.0) {
					if (percentuale > 200.0) {
						percentuale = 0;
					}
					else {
						percentuale = 200 - percentuale;
					}
				}
				valutazioneRelazioneJoint[_joint].insert_deltadist_azimut(n_joint, diff,percentuale);
			}
		}

	}
	popola_pesiRJ(_joint);
	valutazioneRelazioneJoint[_joint].calcola_media_discostamento();
	valutazioneRelazioneJoint[_joint].calcola_accuratezza();
	//a questo punto ho finito le liste di max e min per il mio joint, quindi lo riaggiungo al set cosi che possa essere riutilizzata
	numeri_angoli.insert(_joint);

}

void Valutazione::stampavalutazione(string percorso_file, string name) {
	string l = percorso_file + "/" + name + ".txt";
	ofstream file;
	file.open(l);
	map<int, pair<float, float>>::iterator iter;
    for (iter = pesi.begin(); iter != pesi.end(); ++iter) {
			if ((iter->second.first + iter->second.second) > 0.3) //stampo la valutazione approfondita anche considerazioni su velocità
			{
				file << "Relazione approfondita sull'articolazione numero " << iter->first << endl;
				valutazioneSingleJoint[iter->first].stampa_file_accurato(file);
				valutazioneRelazioneJoint[iter->first].stampa_file_accurato(file);
			}
			else {//stampo la valutazione non approfondita solo accuratezze SJ e RJ
				file << "Relazione non approfondita sull'articolazione numero " << iter->first << endl;
				valutazioneSingleJoint[iter->first].stampa_file_non_accurato(file);
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

