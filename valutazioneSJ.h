#ifndef __valutazioneSJ_h__
#define __valutazioneSJ_h__

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class ValutazioneSJ{
private:
    vector<double> deltadist_zenit;
    vector<double> deltatimemodello_zenit;
	vector<double> deltatimepaziente_zenit;
    double media_deltadist_zenit;
    vector<double> deltadist_azimut;
    vector<double> deltatimemodello_azimut;
	vector<double> deltatimepaziente_azimut;
    double media_deltadist_azimut;
public:
    ValutazioneSJ();
    //Metodi valutazione spaziale
    void insert_deltadist_zenit(double _n);
    void insert_deltadist_azimut(double _n);
	void media_deltadist();
	double get_media_deltadist_zenit();
	double get_media_deltadist_azimut();
	//Metodi valutazione velocità
	void insert_deltatimemodello_zenit(double _n);
	void insert_deltatimepaziente_zenit(double _n);
    void insert_deltatimemodello_azimut(double _n);
	void insert_deltatimepaziente_azimut(double _n);
   
	//Metodi di valutazione
	void elaboradati(); //funzione che in base ai vettori presenti in questa classe fornisce delle considerazioni
	void stampa();
};
#endif
