#include "valutazioneRJ.h"
void ValutazioneRJ::insert_pesiredzenit(int _n, float _p){
    pesired_zenit.insert(pair<int,float> (_n,_p));
}

void ValutazioneRJ::insert_pesiredazimut(int _n, float _p){
    pesired_azimut.insert(pair<int,float> (_n,_p));
}

void ValutazioneRJ::insert_deltadist_zenit(int _joint, double _diff, float _perc) {
	(deltadistZenitRJ[_joint]).push_back(pair<double,float> (_diff,_perc));
}

void ValutazioneRJ::insert_deltadist_azimut(int _joint, double _diff, float _perc) {
	(deltadistAzimutRJ[_joint]).push_back(pair<double, float>(_diff, _perc));
}

void ValutazioneRJ::calcola_media_discostamento() {
	map<int, vector<pair<double, float>>>::iterator miter;
	vector<pair<double, float>>::iterator viter;
	int i = 0;
	double sum = 0.0;
	float sumperc = 0.0;
	//ZENIT
	for (miter = deltadistZenitRJ.begin(); miter != deltadistZenitRJ.end(); ++miter) {
		for (viter = miter->second.begin(); viter !=  miter->second.end(); ++viter) {
			sum += fabs((*viter).first);
			sumperc+= (*viter).second;
			++i;
		}
		if (i != 0) {
			media_deltadist_zenit[miter->first].first = sum / i;
			media_deltadist_zenit[miter->first].second = sumperc / i;
		}
		sum = 0.0;
		sumperc = 0.0;
		i = 0;
	}
	//AZIMUT
	for (miter = deltadistAzimutRJ.begin(); miter != deltadistAzimutRJ.end(); ++miter) {
		for (viter = miter->second.begin(); viter != miter->second.end(); ++viter) {
			sum += fabs((*viter).first);
			sumperc+= (*viter).second;
			++i;
		}
		if (i != 0) {
			media_deltadist_azimut[miter->first].first = sum / i;
			media_deltadist_azimut[miter->first].second = sumperc / i;
		}
		sum = 0.0;
		sumperc = 0.0;
		i = 0;
	}
}

void ValutazioneRJ::stampa() {
	map<int, vector<pair<double, float>>>::iterator iter;
	vector<pair<double, float>>::iterator viter;
	int i = 1;
	//ZENIT
	cout <<endl<<endl<< "Lista scostamenti zenit!" <<endl;
	for (iter = deltadistZenitRJ.begin(); iter != deltadistZenitRJ.end(); ++iter) {
		cout << "Joint indagato = " << iter->first << endl;
		for (viter = iter->second.begin(); viter != iter->second.end(); ++viter) {
			if (viter == iter->second.begin())
				cout << "Confronto sulla posizione iniziale " << (*viter).first << endl;
			else if (viter == --(iter->second.end()))
				cout << "Confronto sulla posizione finale " << (*viter).first <<endl;
			else {
				cout << "Posizione " << i << " " << (*viter).first << endl;
				++i;
			}
		}
		cout << "Media scostamento zenit --> " << media_deltadist_zenit[iter->first].first << endl;
		cout << "Media accuratezza esercizio zenit --> " << media_deltadist_zenit[iter->first].second << endl;
		i = 1;
		cout << endl << endl;
	}
	//AZIMUT
	cout << endl << "Lista scostamenti azimut!" << endl;
	for (iter = deltadistAzimutRJ.begin(); iter != deltadistAzimutRJ.end(); ++iter) {
		cout << "Joint indagato = " << iter->first << endl;
		for (viter = iter->second.begin(); viter != iter->second.end(); ++viter) {
			if (viter == iter->second.begin())
				cout << "Confronto sulla posizione iniziale " << (*viter).first << endl;
			else if (viter == --(iter->second.end()))
				cout << "Confronto sulla posizione finale " << (*viter).first <<endl;
			else {
				cout << "Posizione " << i << " " << (*viter).first << endl;
				++i;
			}
		}
		cout << "Media scostamento azimut --> " << media_deltadist_azimut[iter->first].first << endl;
		cout << "Media accuratezza esercizio azimut --> " << media_deltadist_zenit[iter->first].second << endl;
		i = 1;
		cout << endl << endl;
	}
	
}

map<int, vector<pair<double,float>>> ValutazioneRJ::get_deltadistZenitRJ()const{
    return deltadistZenitRJ;
}

map<int, pair<double, float>> ValutazioneRJ::get_media_deltadist_zenit()const{
    return media_deltadist_zenit;
}

map<int, float> ValutazioneRJ::get_pesired_zenit()const{
    return pesired_zenit;
}

map<int, vector<pair<double, float>>> ValutazioneRJ::get_deltadistAzimutRJ()const{
    return deltadistAzimutRJ;
}

map<int, pair<double, float>> ValutazioneRJ::get_media_deltadist_azimut()const{
    return media_deltadist_azimut;
}

map<int,float> ValutazioneRJ::get_pesired_azimut()const{
    return pesired_azimut;
}

float ValutazioneRJ::get_accuratezza()const{
    return accuratezza;
}

void ValutazioneRJ::calcola_accuratezza(){  //DA CONTROLLAREEEEE
    map<int, pair<double, float>>::const_iterator iterM;
    map<int,float>::const_iterator iterP;
	float temp = 0.0;
	float sum = 0.0;
	iterM = media_deltadist_zenit.begin();
	iterP = pesired_zenit.begin();
	while (iterM != media_deltadist_zenit.end() && iterP != pesired_zenit.end())
	{
		sum += iterP->second;
		temp += (iterM->second.second)*iterP->second;
		++iterM;
		++iterP;
	}
	accuratezza_zenit = temp / sum ; //media ponderata accuratezza zenit tra 0 e 1
	temp = 0.0;
	sum = 0.0;
	iterM = media_deltadist_azimut.begin();
	iterP = pesired_azimut.begin();
	while (iterM != media_deltadist_azimut.end() && iterP != pesired_azimut.end())
	{
		sum += iterP->second;
		temp += (iterM->second.second)*iterP->second;
		++iterM;
		++iterP;
	}
    accuratezza_azimut = temp / sum; //media ponderata accuratezza zenit tra 0 e 1
	accuratezza = (0.75*accuratezza_zenit) + (0.25*accuratezza_azimut);
}

float ValutazioneRJ::get_accuratezza_azimut()const{
    return accuratezza_azimut;
}

float ValutazioneRJ::get_accuratezza_zenit()const{
    return accuratezza_zenit;
}

void ValutazioneRJ::test() {
	map<int, float>::iterator iter;
	cout << "Accuratezza generale " << accuratezza << endl;
}

void ValutazioneRJ::stampa_file_accurato(ofstream& file) {
	file << "METRICHE RELATIVE AI MOVIMENTI CONGIUNTI DELLE ALTRE ARTICOLAZIONI " << endl;
	file << "ZENIT" << endl;
	map<int, pair<double, float>>::iterator miter;
	vector<pair<double, float>>::iterator viter;
	int i = 0;
	for (miter = media_deltadist_zenit.begin(); miter != media_deltadist_zenit.end(); ++miter) {
		file << "Articolazione " << miter->first << " -- > Media discostamento da angolo modello = " << media_deltadist_zenit[miter->first].first << " || Percentuale accuratezza media --> " << media_deltadist_zenit[miter->first].second << endl;
		file << "Valutazione approfondita scostamenti" << endl;
		for (viter = deltadistZenitRJ[miter->first].begin(); viter != deltadistZenitRJ[miter->first].end(); ++viter) {
			if (viter == deltadistZenitRJ[miter->first].begin()) {//considerazione su punto iniziale
				if ((*viter).second < 50)//Da controllare il 50!!
					file << "La posizione iniziale non è stata raggiunta correttamente!" << endl;
				else if ((*viter).second < 90)
					file << "La posizione iniziale è sbagliata ma l'errore è contenuto!" << endl;
				else
					file << "La posizione iniziale è corretta!" << endl;
				++i;
			}
			else if (viter == --(deltadistZenitRJ[miter->first].end())) {//considerazione su punto finale
				if ((*viter).second < 50)//Da controllare il 50!!
					file << "La posizione finale non è stata raggiunta correttamente!" << endl;
				else if ((*viter).second < 90)
					file << "La posizione finale è sbagliata ma l'errore è contenuto!" << endl;
				else
					file << "La posizione finale è corretta!" << endl;
			}
			else {//punti interni
				if ((*viter).second < 50)//Da controllare il 50!!
					file << "La posizione " << i << " non è stata raggiunta correttamente!" << endl;
				else if ((*viter).second < 90)
					file << "La posizione " << i << " è sbagliata ma l'errore è contenuto!" << endl;
				else
					file << "La posizione " << i << " è corretta!" << endl;
				++i;
			}
		}
		i = 0;
		file << endl;
	}

	file << "AZIMUT" << endl;
	for (miter = media_deltadist_azimut.begin(); miter != media_deltadist_azimut.end(); ++miter) {
		file << "Articolazione " << miter->first << " -- > Media discostamento da angolo modello = " << media_deltadist_azimut[miter->first].first << " || Percentuale accuratezza media --> " << media_deltadist_azimut[miter->first].second << endl;
		file << "Valutazione approfondita scostamenti" << endl;
		for (viter = deltadistAzimutRJ[miter->first].begin(); viter != deltadistAzimutRJ[miter->first].end(); ++viter) {
			if (viter == deltadistAzimutRJ[miter->first].begin()) {//considerazione su punto iniziale
				if ((*viter).second < 50)//Da controllare il 50!!
					file << "La posizione iniziale non è stata raggiunta correttamente!" << endl;
				else if ((*viter).second < 90)
					file << "La posizione iniziale è sbagliata ma l'errore è contenuto!" << endl;
				else
					file << "La posizione iniziale è corretta!" << endl;
				++i;
			}
			else if (viter == --(deltadistAzimutRJ[miter->first].end())) {//considerazione su punto finale
				if ((*viter).second < 50)//Da controllare il 50!!
					file << "La posizione finale non è stata raggiunta correttamente!" << endl;
				else if ((*viter).second < 90)
					file << "La posizione finale è sbagliata ma l'errore è contenuto!" << endl;
				else
					file << "La posizione finale è corretta!" << endl;
			}
			else {//punti interni
				if ((*viter).second < 50)//Da controllare il 50!!
					file << "La posizione " << i << " non è stata raggiunta correttamente!" << endl;
				else if ((*viter).second < 90)
					file << "La posizione " << i << " è sbagliata ma l'errore è contenuto!" << endl;
				else
					file << "La posizione " << i << " è corretta!" << endl;
				++i;
			}
		}
		i = 0;
		file << endl;
	}
}

void ValutazioneRJ::stampa_file_non_accurato(ofstream& file) {
	file << "METRICHE RELATIVE AI MOVIMENTI CONGIUNTI DELLE ALTRE ARTICOLAZIONI " << endl;
	file << "ZENIT" << endl;
	map<int, pair<double, float>>::iterator miter;
	for (miter = media_deltadist_zenit.begin(); miter != media_deltadist_zenit.end(); ++miter) {
		file << "Articolazione " << miter->first << " -- > Media discostamento da angolo modello = " << media_deltadist_zenit[miter->first].first << " || Percentuale accuratezza media --> " << media_deltadist_zenit[miter->first].second << endl;
	}
	file << "AZIMUT" << endl;
	for (miter = media_deltadist_azimut.begin(); miter != media_deltadist_azimut.end(); ++miter) {
		file << "Articolazione " << miter->first << " -- > Media discostamento da angolo modello = " << media_deltadist_azimut[miter->first].first << " || Percentuale accuratezza media --> " << media_deltadist_azimut[miter->first].second << endl;
	}
}