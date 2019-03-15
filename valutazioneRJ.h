#ifndef __valutazioneRJ_h__
#define __valutazioneRJ_h__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
/*
TODO
- abbiamo pensato a popolarlo con dei map di vector di double 
- ridistribuzione pesi sui joint che non sono quello indagato 
- alla fine faremo una media dei distaccamenti e una media delle velocità
*/

class ValutazioneRJ {
private:
	//ZENIT
	map<int, vector<double>> deltadistZenitRJ; //chiave tutti i joint meno quello indagato e vettori di scostamento tra max e min
	//AZIMUT
	map<int, vector<double>> deltadistAzimut;  //idem

public: 
	void misura_scostamenti_RJ(); 

};


#endif
