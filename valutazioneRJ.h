#ifndef __valutazioneRJ_h__
#define __valutazioneRJ_h__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

class ValutazioneRJ {

private:
	//ZENIT
	map<int, vector<pair<double,float>>> deltadistZenitRJ; //chiave tutti i joint meno quello indagato e vettori di scostamento tra max e min
	map<int, pair<double, float>> media_deltadist_zenit; //chiave numero joint, secondo elemento media discostamenti modello/paziente
	map<int, float> pesired_zenit; //Map che sarà popolata con la i pesi redistibuiti per ogni angolo. 
    //AZIMUT
	map<int, vector<pair<double, float>>> deltadistAzimutRJ;
	map<int, pair<double, float>> media_deltadist_azimut;
    map<int,float> pesired_azimut;
    float mediapesata;
public:
    //INSERT
    void insert_pesiredzenit(int _n, float _p);
    void insert_pesiredazimut(int _n, float _p);
	void insert_deltadist_zenit(int _joint, double _diff, float _perc);
	void insert_deltadist_azimut(int _joint, double _diff, float _perc);
    void calcola_mediapesata();
	//PROCESS
	void calcola_media_discostamento();
	void calcola_mediapesata();
	//TEST
	void stampa();
};


#endif
