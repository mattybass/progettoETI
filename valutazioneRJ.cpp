#include "valutazioneRJ.h"

void ValutazioneRJ::insert_pesiredzenit(int _n, float _p){
    pesired_zenit.insert(pair<int,float> (_n,_p));
}

void ValutazioneRJ::insert_pesiredazimut(int _n, float _p){
    pesired_azimut.insert(pair<int,float> (_n,_p));
}

void ValutazioneRJ::insert_deltadist_zenit(int _joint, double _diff) {
	(deltadistZenitRJ[_joint]).push_back(_diff);
}
void ValutazioneRJ::insert_deltadist_azimut(int _joint, double _diff) {
	(deltadistAzimutRJ[_joint]).push_back(_diff);
}

void ValutazioneRJ::calcola_media_discostamento() {
	map<int, vector<double>>::iterator miter;
	vector<double>::iterator viter;
	int i = 0;
	double sum = 0.0;
	//ZENIT
	for (miter = deltadistZenitRJ.begin(); miter != deltadistZenitRJ.end(); ++miter) {
		for (viter = (miter->second).begin(); viter != (miter->second).end(); ++viter) {
			sum += (*viter);
			++i;
		}
		media_deltadist_zenit[miter->first] = sum / i;
		sum = 0.0;
		i = 0;
	}
	//AZIMUT
	for (miter = deltadistAzimutRJ.begin(); miter != deltadistAzimutRJ.end(); ++miter) {
		for (viter = (miter->second).begin(); viter != (miter->second).end(); ++viter) {
			sum += (*viter);
			++i;
		}
		media_deltadist_azimut[miter->first] = sum / i;
		sum = 0.0;
		i = 0;
	}
}

void ValutazioneRJ::stampa() {
	map<int, vector<double>>::iterator iter;
	vector<double>::iterator viter;
	map<int, double>::iterator miter;
	int i = 1;
	//zenit
	cout <<endl<<endl<< "Lista scostamenti zenit!" <<endl;
	for (iter = deltadistZenitRJ.begin(); iter != deltadistZenitRJ.end(); ++iter) {
		cout << "Joint indagato = " << iter->first << endl;
		for (viter = iter->second.begin(); viter != iter->second.end(); ++viter) {
			if (viter == iter->second.begin())
				cout << "Confronto sulla posizione iniziale " << *viter << endl;
			else if (viter == --(iter->second.end()))
				cout << "Confronto sulla posizione finale " << *viter<<endl;
			else {
				cout << "Posizione " << i << " " << *viter << endl;
				++i;
			}
		}
		cout << "Media scostamento zenit --> " << media_deltadist_zenit[iter->first] << endl;
		i = 1;
		cout << endl << endl;
	}
	//azimut
	cout << endl << "Lista scostamenti azimut!" << endl;
	for (iter = deltadistAzimutRJ.begin(); iter != deltadistAzimutRJ.end(); ++iter) {
		cout << "Joint indagato = " << iter->first << endl;
		for (viter = iter->second.begin(); viter != iter->second.end(); ++viter) {
			if (viter == iter->second.begin())
				cout << "Confronto sulla posizione iniziale " << *viter << endl;
			else if (viter == --(iter->second.end()))
				cout << "Confronto sulla posizione finale " << *viter<<endl;
			else {
				cout << "Posizione " << i << " " << *viter << endl;
				++i;
			}
		}
		cout << "Media scostamento azimut --> " << media_deltadist_azimut[iter->first] << endl;
		i = 1;
		cout << endl << endl;
	}
	
}

void ValutazioneRJ::calcola_mediapesata(){
    
}
