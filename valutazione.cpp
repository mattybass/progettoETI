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
	int nframemodello, nframepaziente;
	nframemodello = (*modello).get_numeroFramePerSecondo();
	nframepaziente = (*paziente).get_numeroFramePerSecondo();
	//ZENIT bisogna fare in modo di inserire punto di inizio e punto di fine
	listaModellozenit = (*modello).get_valorimaxmin_zenit(_joint);
	listaPazientezenit = (*paziente).get_valorimaxmin_zenit(_joint);
	itermodello = listaModellozenit.begin();
	iterpaziente = listaPazientezenit.begin();
	double diff = 0.0;
    float percentuale=0.0;
	
	while (iterpaziente != listaPazientezenit.end()&&itermodello!=listaModellozenit.end()) { //TODO TOGLIERE DOPO CON CONDIZIONE ENTRA SE <=
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
		++itermodello;
	}

	itermodello = listaModellozenit.begin();
	iterpaziente = listaPazientezenit.begin();
	itermodello2 = itermodello;
	iterpaziente2 = iterpaziente;
	++itermodello2;
	++iterpaziente2;

	double secondi_movimento = 0; //conta il numero di secondi che passano tra una posizione chiave e un'altra
    while (iterpaziente2!=listaPazientezenit.end()&&itermodello2!=listaModellozenit.end()) { 
		secondi_movimento = (double)((*itermodello2).get_numeroframe() - (*itermodello).get_numeroframe())/(double)nframemodello;
		valutazioneSingleJoint[_joint].insert_duratamovimentimodello_zenit(secondi_movimento);
		secondi_movimento = (double)((*iterpaziente2).get_numeroframe() - (*iterpaziente).get_numeroframe())/(double)nframepaziente;
		valutazioneSingleJoint[_joint].insert_duratamovimentipaziente_zenit(secondi_movimento);
		++itermodello;
		++itermodello2;
		++iterpaziente;
		++iterpaziente2;
	}

	//AZIMUT
	listaModelloazimut = (*modello).get_valorimaxmin_azimut(_joint);
	listaPazienteazimut = (*paziente).get_valorimaxmin_azimut(_joint);
	itermodello = listaModelloazimut.begin();
	iterpaziente = listaPazienteazimut.begin();
	
	while (iterpaziente != listaPazienteazimut.end()&&itermodello!=listaModelloazimut.end()) {
		diff = (*itermodello).get_azimut() - (*iterpaziente).get_azimut(); //una misura positiva significa non arrivare di diff gradi alla posizione
        percentuale=(((float)(iterpaziente->get_zenit())/(float)(itermodello->get_zenit()))*100.0);
        
            if(percentuale>100.0){
                if(percentuale>200.0){
                    percentuale=0;
                }else{
                    percentuale=200-percentuale;
                }
            }
            valutazioneSingleJoint[_joint].insert_deltadist_azimut(diff,percentuale);      //una negativa significa superarla di diff gradi
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
		++itermodello;
		++itermodello2;
		++iterpaziente;
		++iterpaziente2;
	}
}

void Valutazione::valutaRelationJoint(int _joint) {
	//NB! questa funzione deve essere eseguita se il numero di max min del paziente è <= del numero max min del modello!
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
	listaPaziente = (*paziente).get_valorimaxmin_zenit(_joint);
	listaModello = (*modello).get_valorimaxmin_zenit(_joint);
	frame_iniz_modello = (*(listaModello.begin())).get_numeroframe();
	itermodello2 = listaModello.end();
	--itermodello2;
	frame_fin_modello = (*itermodello2).get_numeroframe();
	numeri_angoli.erase(_joint); //elimino il joint sul quale mi sono focalizzato
	//ZENIT
	for (iterpaziente = listaPaziente.begin(); iterpaziente != listaPaziente.end(); ++iterpaziente) {
		int n_frame = (*iterpaziente).get_numeroframe(); //frame del primo punto chiave
		
		if (n_frame > frame_iniz_modello&&n_frame < frame_fin_modello) {
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, n_frame); //angolo del modello corrispondente al punto chiave del paziente
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_zenit() - ang_paziente.get_zenit());
				percentuale = (((float)(ang_modello.get_zenit() / (float)(ang_paziente.get_zenit()))*100.0));
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
		else if (n_frame < frame_iniz_modello) { //vuol dire che il frame di inizio del paziente è antecedente a quello del modello
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, frame_iniz_modello); //confronto con il punto iniziale del modello
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_zenit() - ang_paziente.get_zenit());
				percentuale = (((float)(ang_modello.get_zenit() / (float)(ang_paziente.get_zenit()))*100.0));
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
		else if (n_frame > frame_fin_modello) {
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, frame_fin_modello); //angolo del modello corrispondente al punto chiave del paziente
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_zenit() - ang_paziente.get_zenit());
				percentuale = (((float)(ang_modello.get_zenit() / (float)(ang_paziente.get_zenit()))*100.0));
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
	//AZIMUT
	for (iterpaziente = listaPaziente.begin(); iterpaziente != listaPaziente.end(); ++iterpaziente) {
		int n_frame = (*iterpaziente).get_numeroframe(); //frame del primo punto chiave
		//devo passare alla valutazione degli angoli restanti!
		if (n_frame > frame_iniz_modello&&n_frame < frame_fin_modello) {
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, n_frame); //angolo del modello corrispondente al punto chiave del paziente
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_azimut() - ang_paziente.get_azimut());
				percentuale = (((float)(ang_modello.get_zenit() / (float)(ang_paziente.get_zenit()))*100.0));
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
		else if (n_frame < frame_iniz_modello) { //vuol dire che il frame di inizio del paziente è antecedente a quello del modello
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, frame_iniz_modello); //confronto con il punto iniziale del modello
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_azimut() - ang_paziente.get_azimut());
				percentuale = (((float)(ang_modello.get_zenit() / (float)(ang_paziente.get_zenit()))*100.0));
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
		else if (n_frame > frame_fin_modello) {
			for (iter = numeri_angoli.begin(); iter != numeri_angoli.end(); ++iter) {
				n_joint = *iter;
				Angolo ang_modello = (*modello).return_angolo(n_joint, frame_fin_modello); //angolo del modello corrispondente al punto chiave del paziente
				Angolo ang_paziente = (*paziente).return_angolo(n_joint, n_frame); //angolo del paziente corrispondente al punto chiave del paziente
				diff = abs(ang_modello.get_azimut() - ang_paziente.get_azimut());
				percentuale = (((float)(ang_modello.get_zenit() / (float)(ang_paziente.get_zenit()))*100.0));
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
	//a questo punto ho finito le liste di max e min per il mio joint, quindi lo riaggiungo al set cosi che possa essere riutilizzata
	numeri_angoli.insert(_joint);

}

void Valutazione::stampavalutazione() {
	map<int, ValutazioneSJ>::iterator iterSJ;
	map<int, ValutazioneRJ>::iterator iterRJ;
	percentualeEsCompletato();
	cout << "Esercizio completato al " << completezzaesercizio << "%!"<<endl;
	for (iterSJ = valutazioneSingleJoint.begin(); iterSJ != valutazioneSingleJoint.end(); ++iterSJ) {
		(iterSJ->second).stampa();
	}
	cout << endl<<endl<<"Valutazione posizione altri joint rispetto al modello!"<<endl;
	for (iterRJ = valutazioneRelazioneJoint.begin(); iterRJ != valutazioneRelazioneJoint.end(); ++iterRJ) {
		cout << "Relazione del joint " << iterRJ->first << " con gli altri" << endl;
		(iterRJ->second).calcola_media_discostamento();
		(iterRJ->second).stampa();
	}

}

map<int, pair<float,float>> Valutazione:: get_pesi()const{
    return pesi;
}

void Valutazione::popola_pesiRJ(int _angolo){
    map<int, pair<float,float>>::const_iterator iterM;
    float sommaazimut=0.0;
    float sommazenit=0.0;
    float sommacalcoloZ=0.0;
    float sommacalcoloA=0.0;
    float pesoprecZ=0.0;
    float pesoprecA=0.0;
    float pesoredistribuitoA=0.0;
    float pesoredistribuitoZ=0.0;
    //Calcolo sommaazimut;
    for(iterM=pesi.begin();iterM!=pesi.end();++iterM){
        sommaazimut=sommaazimut+iterM->second.second;
    }
    //Calcolo sommazenit;
    for(iterM=pesi.begin();iterM!=pesi.end();++iterM){
        sommazenit=sommazenit+iterM->second.first;
    }
    
    iterM=pesi.find(_angolo);
    if(iterM!=pesi.end()){
        pesoprecZ=iterM->second.first;
        pesoprecA=iterM->second.second;
        sommacalcoloZ=sommazenit-pesoprecZ;
        sommacalcoloA=sommaazimut-pesoprecA;
    }
    
    for(iterM=pesi.begin();iterM!=pesi.end();++iterM){
        pesoprecZ=iterM->second.first;
        pesoprecA=iterM->second.second;
        pesoredistribuitoA=pesoprecA/sommacalcoloA;
        pesoredistribuitoZ=pesoprecZ/sommacalcoloZ;
        map<int, ValutazioneRJ>::iterator iterM1;
        iterM1=valutazioneRelazioneJoint.find(_angolo);
        if(iterM1!=valutazioneRelazioneJoint.end()){
            iterM1->second.insert_pesiredazimut(iterM->first, pesoredistribuitoA);
            iterM1->second.insert_pesiredazimut(iterM->first, pesoredistribuitoZ);
        }
    }
    
}
