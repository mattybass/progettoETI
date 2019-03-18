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
	vector<pair<double, float>>::iterator viterinizio;
	vector<pair<double, float>>::iterator viterfine;
	int i = 0;
	double sum = 0.0;
	float sumperc = 0.0;
	//ZENIT
	for (miter = deltadistZenitRJ.begin(); miter != deltadistZenitRJ.end(); ++miter) {
		for (viter = miter->second.begin(); viter !=  miter->second.end(); ++viter) {
			sum += (*viter).first;
			sumperc = (*viter).second;
			++i;
		}
		media_deltadist_zenit[miter->first].first = sum / i;
		media_deltadist_zenit[miter->first].second = sumperc / i;
		sum = 0.0;
		i = 0;
	}
	//AZIMUT
	for (miter = deltadistAzimutRJ.begin(); miter != deltadistAzimutRJ.end(); ++miter) {
		for (viter = miter->second.begin(); viter != miter->second.end(); ++viter) {
			sum += (*viter).first;
			sumperc = (*viter).second;
			++i;
		}
		media_deltadist_azimut[miter->first].first = sum / i;
		media_deltadist_azimut[miter->first].second = sumperc / i;
		sum = 0.0;
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
		cout << "Media scostamento zenit percentuale --> " << media_deltadist_zenit[iter->first].second << endl;
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
		cout << "Media scostamento azimut percentuale --> " << media_deltadist_zenit[iter->first].second << endl;
		i = 1;
		cout << endl << endl;
	}
	
}

