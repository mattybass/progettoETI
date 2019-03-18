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
	float accuratezza_zenit;
    //AZIMUT
	map<int, vector<pair<double, float>>> deltadistAzimutRJ;
	map<int, pair<double, float>> media_deltadist_azimut;
    map<int,float> pesired_azimut;
    float accuratezza_azimut;
	//GENERALI
    float accuratezza;

public:
    //INSERT
    void insert_pesiredzenit(int _n, float _p);
    void insert_pesiredazimut(int _n, float _p);
	void insert_deltadist_zenit(int _joint, double _diff, float _perc);
	void insert_deltadist_azimut(int _joint, double _diff, float _perc);
	//PROCESS
	void calcola_media_discostamento();
	void calcola_accuratezza();
    //GET
    map<int, vector<pair<double,float>>> get_deltadistZenitRJ()const;
    map<int, pair<double, float>> get_media_deltadist_zenit()const;
    map<int, float> get_pesired_zenit()const;
    map<int, vector<pair<double, float>>> get_deltadistAzimutRJ()const;
    map<int, pair<double, float>> get_media_deltadist_azimut()const;
    map<int,float> get_pesired_azimut()const;
    float get_accuratezza()const;
    float get_accuratezza_azimut()const;
    float get_accuratezza_zenit()const;
	//TEST
	void stampa();
	void test();
};

#endif
