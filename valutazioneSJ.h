#ifndef __valutazioneSJ_h__
#define __valutazioneSJ_h__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "utility.h"
using namespace std;

class ValutazioneSJ{
private:
    //ZENIT
    vector<pair<double,float>> deltadist_zenit; //Vector con pair. First= differenza distanze, Second= percentuale sulla differenza
    vector<double> duratamovimentimodello_zenit;
	vector<double> duratamovimentipaziente_zenit;
    vector<pair<double,float>> deltatime_zenit;//Vector con pair. First= differenza tempo, Second= percentuale sulla differenza
    double media_deltadist_zenit; //Media differenze distanze
    float media_deltadist_zenit_percento; //Percentuale media sulle differenze distanze
    double media_deltatime_zenit; //Media differenze tempo
    float media_deltatime_zenit_percento; //Percentuale media sulle differenze tempo
	float accuratezza_zenit;
	int diffpuntizenit; 
    //AZIMUT
    vector<pair<double,float>> deltadist_azimut;
    vector<double> duratamovimentimodello_azimut;
	vector<double> duratamovimentipaziente_azimut;
    vector<pair<double,float>> deltatime_azimut;
    double media_deltadist_azimut;
    float media_deltadist_azimut_percento;
    double media_deltatime_azimut;
    float media_deltatime_azimut_percento;
	float accuratezza_azimut;
	int diffpuntiazimut;
	//GENERALI
    float accuratezza; 
public:
	//COSTRUTTORE
    ValutazioneSJ();
	//SET
	void set_diffpunti_azimut(int _diff);
	void set_diffpunti_zenit(int _diff);
    //INSERT
    void insert_deltadist_zenit(double _n, float _p);
    void insert_deltadist_azimut(double _n, float _p);
	void insert_duratamovimentimodello_zenit(double _n);
	void insert_duratamovimentipaziente_zenit(double _n);
	void insert_duratamovimentimodello_azimut(double _n);
	void insert_duratamovimentipaziente_azimut(double _n);
	void insert_deltatime_zenit();
	void insert_deltatime_azimut();
    //GET
	double get_media_deltadist_zenit();
	double get_media_deltadist_azimut();
    vector<pair<double,float>> get_deltadist_zenit()const;
    vector<pair<double,float>> get_deltatime_zenit()const;
    double get_media_deltadist_zenit()const;
    float get_media_deltadist_zenit_percento()const;
    double get_media_deltatime_zenit()const;
    float get_media_deltatime_zenit_percento()const;
    vector<pair<double,float>> get_deltadist_azimut()const;
    vector<pair<double,float>> get_deltatime_azimut()const;
    double get_media_deltadist_azimut()const;
    float get_media_deltadist_azimut_percento()const;
    double get_media_deltatime_azimut()const;
    float get_media_deltatime_azimut_percento()const;
    float get_accuratezza_azimut()const;
    float get_accuratezza_zenit()const;
    float get_accuratezza()const;
	//PROCESS
	void media_deltadist();
	void media_deltatime();
	void calcola_accuratezza();
	//PRINT
	void stampa_file_accurato(ofstream& _file);//funzione che stampa sul file tutti i valori comprese le valutazioni sui singoli movimenti
	void stampa_file_non_accurato(ofstream& _file);//funzione che stampa sul file solo i valori medi senza tener conto dei singoli movimenti
	void stampa(); 
};
#endif
