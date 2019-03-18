#include "valutazioneRJ.h"
//CONTROLLATE
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
			sum += (*viter).first;
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
			sum += (*viter).first;
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
	map<int, pair<double,float>>::iterator miter;
	int i = 1;
	//zenit
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
	//azimut
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

void ValutazioneRJ::calcola_accuratezza(){
    map<int, pair<double, float>>::const_iterator iterM;
    map<int,float>::const_iterator iterP;
	float temp = 0.0;
	float sum = 0.0;
	iterM = media_deltadist_zenit.begin();
	iterP = pesired_zenit.begin();
	cout << media_deltadist_zenit.size();
	cout << pesired_zenit.size();
	while (iterM != media_deltadist_zenit.end() && iterP != pesired_zenit.end())
	{
		sum += iterP->second;
		temp += ((iterM->second.second) / 100)*iterP->second;
		++iterM;
		++iterP;
	}
	accuratezza_zenit = temp / sum; //media ponderata accuratezza zenit tra 0 e 1
	temp = 0.0;
	sum = 0.0;
	iterM = media_deltadist_azimut.begin();
	iterP = pesired_azimut.begin();
	while (iterM != media_deltadist_azimut.end() && iterP != pesired_azimut.end())
	{
		sum += iterP->second;
		temp += ((iterM->second.second) / 100)*iterP->second;
		++iterM;
		++iterP;
	}
    accuratezza_azimut = temp / sum; //media ponderata accuratezza zenit tra 0 e 1
	accuratezza = (0.5*accuratezza_zenit) + (0.5*accuratezza_azimut);
}


float ValutazioneRJ::get_accuratezza_azimut()const{
    return accuratezza_azimut;
}

float ValutazioneRJ::get_accuratezza_zenit()const{
    return accuratezza_zenit;
}

void ValutazioneRJ::test() {
	map<int, float>::iterator iter;
	cout << "ZENIT" << endl;
	for (iter = pesired_zenit.begin(); iter != pesired_zenit.end(); ++iter) {
		cout << "Peso joint " << iter->first << " = " << iter->second << endl;
	}
	cout << "Accuratezza zenit " << accuratezza_zenit << endl;
	cout << "AZIMUT" << endl;
	for (iter = pesired_azimut.begin(); iter != pesired_azimut.end(); ++iter) {
		cout << "Peso joint " << iter->first << " = " << iter->second << endl;
	}
	cout << "Accuratezza azimut " << accuratezza_azimut << endl;
}