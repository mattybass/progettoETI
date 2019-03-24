#include "valutazioneSJ.h"

vector<pair<double, float>> ValutazioneSJ::get_deltadist_zenit()const {
	return deltadist_zenit;
}

vector<pair<double, float>> ValutazioneSJ::get_deltatime_zenit()const {
	return deltatime_zenit;
}

double ValutazioneSJ::get_media_deltadist_zenit()const {
	return media_deltadist_zenit;
}

float ValutazioneSJ::get_media_deltadist_zenit_percento()const {
	return media_deltadist_zenit_percento;
}

double ValutazioneSJ::get_media_deltatime_zenit()const {
	return media_deltatime_zenit;
}

float ValutazioneSJ::get_media_deltatime_zenit_percento()const {
	return media_deltatime_zenit_percento;
}

vector<pair<double, float>> ValutazioneSJ::get_deltadist_azimut()const {
	return deltadist_azimut;
}

vector<pair<double, float>> ValutazioneSJ::get_deltatime_azimut()const {
	return deltatime_azimut;
}

double ValutazioneSJ::get_media_deltadist_azimut()const {
	return media_deltadist_azimut;
}

float ValutazioneSJ::get_media_deltadist_azimut_percento()const {
	return media_deltadist_azimut_percento;
}

double ValutazioneSJ::get_media_deltatime_azimut()const {
	return media_deltatime_azimut;
}

float ValutazioneSJ::get_media_deltatime_azimut_percento()const {
	return media_deltatime_azimut_percento;
}

void ValutazioneSJ::calcola_accuratezza() {
	accuratezza_azimut = (media_deltadist_azimut_percento + media_deltatime_azimut_percento)/2;
	accuratezza_zenit = (media_deltadist_zenit_percento + media_deltatime_zenit_percento)/2;

	accuratezza = (accuratezza_zenit + accuratezza_azimut) / 2;
}

float ValutazioneSJ::get_accuratezza_azimut()const {
	return accuratezza_azimut;
}

float ValutazioneSJ::get_accuratezza_zenit()const {
	return accuratezza_zenit;
}

float ValutazioneSJ::get_accuratezza()const {
	return accuratezza;
}

ValutazioneSJ::ValutazioneSJ(){
    media_deltadist_zenit=0;
    media_deltadist_azimut=0;
	media_deltatime_zenit = 0;
	media_deltatime_azimut = 0;
	accuratezza_azimut = 0;
    accuratezza_zenit = 0;
	accuratezza = 0;
}

void ValutazioneSJ::media_deltadist() { //valori coerenti
	vector<pair<double, float>>::iterator iterV;
	double somma = 0;
	float percentuale = 0.0;
	int counter = deltadist_zenit.size();
	//ZENIT
	for (iterV = deltadist_zenit.begin(); iterV != deltadist_zenit.end(); ++iterV) {
		somma += abs(iterV->first);
		percentuale += iterV->second;
	}
	media_deltadist_zenit = somma / (double)counter;
	media_deltadist_zenit_percento = percentuale / (float)counter;
	
	//AZIMUT
	somma = 0;
	percentuale = 0.0;
	counter = deltadist_azimut.size();
	for (iterV = deltadist_azimut.begin(); iterV != deltadist_azimut.end(); ++iterV) {
		somma += fabs(iterV->first);
		percentuale += iterV->second;
	}
	
	media_deltadist_azimut = somma / (double)counter;
	media_deltadist_azimut_percento = percentuale / (float)counter;
	}

void ValutazioneSJ::insert_deltadist_zenit(double _n, float _p) {
	deltadist_zenit.push_back(pair<double, float>(_n, _p));
}

void ValutazioneSJ::insert_deltadist_azimut(double _n, float _p) {
	deltadist_azimut.push_back(pair<double, float>(_n, _p));
}

double ValutazioneSJ::get_media_deltadist_zenit() {
	return media_deltadist_zenit;
}

double ValutazioneSJ::get_media_deltadist_azimut() {
	return media_deltadist_azimut;
}

void ValutazioneSJ::insert_duratamovimentimodello_zenit(double _n){
        duratamovimentimodello_zenit.push_back(_n);
}

void ValutazioneSJ::insert_duratamovimentipaziente_zenit(double _n) {
	duratamovimentipaziente_zenit.push_back(_n);
}

void ValutazioneSJ::insert_duratamovimentimodello_azimut(double _n){
        duratamovimentimodello_azimut.push_back(_n);
}

void ValutazioneSJ::insert_duratamovimentipaziente_azimut(double _n) {
	duratamovimentipaziente_azimut.push_back(_n);
}

void ValutazioneSJ::insert_deltatime_zenit(){
    vector<double>::iterator iterVM;
    vector<double>::iterator iterVP;
    double differenza;
    float percentuale;
    iterVM=duratamovimentimodello_zenit.begin();
    iterVP=duratamovimentipaziente_zenit.begin();
	if (duratamovimentipaziente_zenit.size() > 1 && duratamovimentimodello_zenit.size()>1) {//non tengo in considerazione il caso in cui l'angolo rimanga fermo 
		while (iterVM != duratamovimentimodello_zenit.end() && iterVP != duratamovimentipaziente_zenit.end()) {
			differenza = (*iterVM) - (*iterVP);
			percentuale = ((float)(*iterVP) / (float)(*iterVM))*100.0;
			percentuale = normalizza_percentuale(percentuale);
			deltatime_zenit.push_back(pair<double, float>(differenza, percentuale));
			++iterVM;
			++iterVP;
		}
	}
	else
	{
		deltatime_zenit.push_back(pair<double,float>(0, 100)); //metto il massimo perchè non posso tenere considerazione di una costante nella valutazione dei movimenti..
	}
	
}

void ValutazioneSJ::insert_deltatime_azimut(){
    vector<double>::const_iterator iterVM;
    vector<double>::const_iterator iterVP;
    double differenza;
    float percentuale;
    iterVM=duratamovimentimodello_azimut.begin();
    iterVP=duratamovimentipaziente_azimut.begin();
	if (duratamovimentipaziente_azimut.size() > 1 && duratamovimentimodello_azimut.size() > 1) {//non tengo in considerazione il caso in cui l'angolo rimanga fermo 
		while (iterVM != duratamovimentimodello_azimut.end() && iterVP != duratamovimentipaziente_azimut.end()) {
			differenza = (*iterVM) - (*iterVP);
			percentuale = ((float)(*iterVP) / (float)(*iterVM))*100.0;
			percentuale = normalizza_percentuale(percentuale);
			deltatime_azimut.push_back(pair<double, float>(differenza, percentuale));
			++iterVM;
			++iterVP;
		}
	}
	else
	{
		deltatime_azimut.push_back(pair<double, float>(0, 100)); //metto il massimo perchè non posso tenere considerazione di una costante nella valutazione dei movimenti..
	}
}

void ValutazioneSJ::media_deltatime(){
    vector<pair<double,float>>::const_iterator iterV;
    double somma=0.0;
    float percentuale=0.0;
    int counter=deltatime_zenit.size();
    //ZENIT
	for(iterV=deltatime_zenit.begin();iterV!=deltatime_zenit.end();++iterV){
        somma+=(*iterV).first; //non uso il valore assoluto perchè voglio avere una media di velocità positiva o negativa
        percentuale+=(*iterV).second;
    }
    if(counter!=0){
		media_deltatime_zenit=somma/(double)counter;
        media_deltatime_zenit_percento=percentuale/ (float)counter;
    }else{
        media_deltatime_zenit=0;
        media_deltatime_zenit_percento=0.0;
    }
    //AZIMUT
	somma = 0;
	percentuale = 0.0;
	counter = deltatime_azimut.size();
    for(iterV=deltatime_azimut.begin();iterV!=deltatime_azimut.end();++iterV){
        somma+=(*iterV).first; //non uso il valore assoluto perchè voglio avere una media di velocità positiva o negativa
        percentuale+=((*iterV).second);
    }
    if(counter!=0){
        media_deltatime_azimut=somma/ (double)counter;
        media_deltatime_azimut_percento=percentuale/ (float)counter;
    }else{
        media_deltatime_azimut=0;
        media_deltatime_azimut_percento=0.0;
    }
}

void ValutazioneSJ::stampa() {
	vector<double>::iterator iter;
	vector<pair<double, float>>::iterator iterVP;
	int i = 0;
	cout << endl << endl << "Zenit" << endl;
	cout << "Misure Spaziali" << endl;
	for (iterVP = deltadist_zenit.begin(); iterVP != deltadist_zenit.end(); ++iterVP) {
		++i;
		cout << "Punto chiave " << i << " -->";
		cout << iterVP->first << "Percentuale" << iterVP->second << endl;
	}
	i = 0;
	cout << endl << "Misure di velocita" << endl;
	cout << "Velocita modello" << endl;
	for (iter = duratamovimentimodello_zenit.begin(); iter != duratamovimentimodello_zenit.end(); ++iter) {
		++i;
		cout << "Movimento " << i << " -->";
		cout << *iter << endl;
	}
	i = 0;
	cout << "Velocita paziente" << endl;
	for (iter = duratamovimentipaziente_zenit.begin(); iter != duratamovimentipaziente_zenit.end(); ++iter) {
		++i;
		cout << "Movimento " << i << " -->";
		cout << *iter << endl;
	}
	cout << endl << "Azimut" << endl;
	cout << "Misure Spaziali" << endl;
	i = 0;
	for (iterVP = deltadist_azimut.begin(); iterVP != deltadist_azimut.end(); ++iterVP) {
		++i;
		cout << "Punto chiave " << i << " -->";
		cout << iterVP->first << "Percentuale" << iterVP->second << endl;
	}
	i = 0;
	cout << endl << "Misure di velocita" << endl;
	cout << "Velocita modello" << endl;
	for (iter = duratamovimentimodello_azimut.begin(); iter != duratamovimentimodello_azimut.end(); ++iter) {
		++i;
		cout << "Movimento " << i << " -->";
		cout << *iter << endl;
	}
	i = 0;
	cout << "Velocita paziente" << endl;
	for (iter = duratamovimentipaziente_azimut.begin(); iter != duratamovimentipaziente_azimut.end(); ++iter) {
		++i;
		cout << "Movimento " << i << " -->";
		cout << *iter << endl;
	}
}

void ValutazioneSJ::stampa_file_accurato(ofstream& file) {
	vector<pair<double, float>>::iterator iter;
	int i = 0;
	file << "METRICHE RELATIVE ALLA SINGOLA ARTICOLAZIONE" << endl;

	file << "ZENIT" << endl;
	if (diffpuntizenit < 0) {
		file << "Su questa articolazione, per quanto riguarda lo zenit, sono stati effettuati meno movimenti di quelli previsti dall'esercizio!" << endl;
	}
	else if (diffpuntizenit > 0) {
		file << "Su questa articolazione, per quanto riguarda lo zenit, sono stati effettuati più movimenti di quelli previsti dall'esercizio!" << endl;
	}
	else
		file << "Su questa articolazione, per quanto riguarda lo zenit, è stato effettuato il corretto numero di movimenti!" << endl;
	file << "Media discostamento da angolo modello --> " << media_deltadist_zenit << " percentuale accuratezza media --> " << media_deltadist_zenit_percento << endl<<endl;
	file << "Valutazione approfondita scostamenti" << endl;
	for (iter = deltadist_zenit.begin(); iter != deltadist_zenit.end(); ++iter) {
		if (iter == deltadist_zenit.begin()) {//considerazione su punto iniziale
			if ((*iter).second < 50)//Da controllare il 50!!
				file << "La posizione iniziale non è stata raggiunta correttamente!" << endl;
			else if ((*iter).second < 90)
				file << "La posizione iniziale è sbagliata ma l'errore è contenuto!" << endl;
			else
				file << "La posizione iniziale è corretta!" << endl;
			++i;
		}
		else if (iter == --(deltadist_zenit.end())) {//considerazione su punto finale
			if ((*iter).second < 50)//Da controllare il 50!!
				file << "La posizione finale non è stata raggiunta correttamente!" << endl;
			else if ((*iter).second < 90)
				file << "La posizione finale è sbagliata ma l'errore è contenuto!" << endl;
			else
				file << "La posizione finale è corretta!" << endl;
			++i;
		}
		else {//punti interni
			if ((*iter).second < 50)//Da controllare il 50!!
				file << "La posizione "<<i<<" non è stata raggiunta correttamente!" << endl;
			else if ((*iter).second < 90)
				file << "La posizione " << i << " è sbagliata ma l'errore è contenuto!" << endl;
			else
				file << "La posizione " << i << " è corretta!" << endl;
			++i;
		}
	}
	file << endl;
	i = 1;
	if (media_deltatime_zenit < -0.5)
		file << "L'esercizio è stato svolto complessivamente in modo più lento rispetto al modello!" << endl;
	else if (media_deltatime_zenit > 0.5)
		file << "L'esercizio è stato svolto complessivamente in modo più veloce rispetto al modello!" << endl;
	else
		file <<endl<< "La velocità di esecuzione dell'esercizio è corretta!" << endl;
	file <<endl<< "Valutazione approfondita velocità" << endl;
	for (iter = deltatime_zenit.begin(); iter != deltatime_zenit.end(); ++iter) {
		if ((*iter).first < -0.5)
			file << "Il movimento " << i << " è stato effettuato in maniera leggermente lenta!" << endl;
		else if ((*iter).first < -1)
			file << "Il movimento " << i << " è stato effettuato in maniera molto lenta!" << endl;
	    else if ((*iter).first > 0.5)
			file << "Il movimento " << i << " è stato eseguito in maniera leggermente veloce" << endl;
		else if ((*iter).first > 1)
			file << "Il movimento " << i << " è stato eseguito in maniera molto veloce" << endl;
		else
			file << "Il movimento " << i << " è stato effettuato con la corretta velocità!" << endl;
		++i;
	}
	file << endl<<endl;
	i = 0;
	file << "AZIMUT" << endl;
	if (diffpuntiazimut < 0) {
		file << "Su questa articolazione, per quanto riguarda l'azimut, sono stati effettuati meno movimenti di quelli previsti dall'esercizio!" << endl;
	}
	else if (diffpuntiazimut > 0) {
		file << "Su questa articolazione, per quanto riguarda l'azimut, sono stati effettuati più movimenti di quelli previsti dall'esercizio!" << endl;
	}
	else
		file << "Su questa articolazione, per quanto riguarda l'azimut, è stato effettuato il corretto numero di movimenti!" << endl;
	file << "Media discostamento da angolo modello --> " << media_deltadist_azimut << " percentuale accuratezza media --> " << media_deltadist_azimut_percento << endl << endl;
	file << "Valutazione approfondita scostamenti" << endl;
	for (iter = deltadist_azimut.begin(); iter != deltadist_azimut.end(); ++iter) {
		if (iter == deltadist_azimut.begin()) {//considerazione su punto iniziale
			if ((*iter).second < 50)//Da controllare il 50!!
				file << "La posizione iniziale non è stata raggiunta correttamente!" << endl;
			else if ((*iter).second < 90)
				file << "La posizione iniziale è sbagliata ma l'errore è contenuto!" << endl;
			else
				file << "La posizione iniziale è corretta!" << endl;
			++i;
		}
		else if (iter == --(deltadist_azimut.end())) {//considerazione su punto finale
			if ((*iter).second < 50)//Da controllare il 50!!
				file << "La posizione finale non è stata raggiunta correttamente!" << endl;
			else if ((*iter).second < 90)
				file << "La posizione finale è sbagliata ma l'errore è contenuto!" << endl;
			else
				file << "La posizione finale è corretta!" << endl;
			++i;
		}
		else {//punti interni
			if ((*iter).second < 50)//Da controllare il 50!!
				file << "La posizione " << i << " non è stata raggiunta correttamente!" << endl;
			else if ((*iter).second < 90)
				file << "La posizione " << i << " è sbagliata ma l'errore è contenuto!" << endl;
			else
				file << "La posizione " << i << " è corretta!" << endl;
			++i;
		}
	}
	file << endl;
	i = 1;
	if (media_deltatime_azimut < -0.5)
		file << "L'esercizio è stato svolto complessivamente in modo più lento rispetto al modello!" << endl;
	else if (media_deltatime_azimut > 0.5)
		file << "L'esercizio è stato svolto complessivamente in modo più veloce rispetto al modello!" << endl;
	else
		file << endl << "La velocità di esecuzione dell'esercizio è corretta!" << endl;
	file << endl << "Valutazione approfondita velocità" << endl;
	for (iter = deltatime_azimut.begin(); iter != deltatime_azimut.end(); ++iter) {
		if ((*iter).first < -0.5)
			file << "Il movimento " << i << " è stato effettuato in maniera leggermente lenta!" << endl;
		else if ((*iter).first < -1)
			file << "Il movimento " << i << " è stato effettuato in maniera molto lenta!" << endl;
		else if ((*iter).first > 0.5)
			file << "Il movimento " << i << " è stato eseguito in maniera leggermente veloce" << endl;
		else if ((*iter).first > 1)
			file << "Il movimento " << i << " è stato eseguito in maniera molto veloce" << endl;
		else
			file << "Il movimento " << i << " è stato effettuato con la corretta velocità!" << endl;
		++i;
	}
	file << endl;

}

void ValutazioneSJ::stampa_file_non_accurato(ofstream& file) {
	file << "METRICHE RELATIVE ALLA SINGOLA ARTICOLAZIONE" << endl;
	file << "ZENIT" << endl;
	file << "Media discostamento da angolo modello --> " << media_deltadist_zenit << " percentuale accuratezza media --> " << media_deltadist_zenit_percento << endl;
	if (media_deltatime_zenit < -0.5)
		file << "L'esercizio è stato svolto complessivamente in modo più lento rispetto al modello!" << endl;
	else if (media_deltatime_zenit > 0.5)
		file << "L'esercizio è stato svolto complessivamente in modo più veloce rispetto al modello!" << endl;
	else
		file << endl << "La velocità di esecuzione dell'esercizio è corretta!" << endl;
	file << "AZIMUT" << endl;
	file << "Media discostamento da angolo modello --> " << media_deltadist_azimut << " percentuale accuratezza media --> " << media_deltadist_azimut_percento << endl;
	if (media_deltatime_azimut < -0.5)
		file << "L'esercizio è stato svolto complessivamente in modo più lento rispetto al modello!" << endl;
	else if (media_deltatime_azimut > 0.5)
		file << "L'esercizio è stato svolto complessivamente in modo più veloce rispetto al modello!" << endl;
	else
		file << "La velocità di esecuzione dell'esercizio è corretta!" << endl;
}

void ValutazioneSJ::set_diffpunti_azimut(int _diff) {
	diffpuntiazimut = _diff;
}

void ValutazioneSJ::set_diffpunti_zenit(int _diff) {
	diffpuntizenit = _diff;
}