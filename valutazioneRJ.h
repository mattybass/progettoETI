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
    int jointindagato;
	//ZENIT
    map<int,float> pesired_zenit; //Map che sarˆ popolata con la i pesi redistibuiti per ogni angolo. ZENIT
	//AZIMUT
    map<int,float> pesired_azimut; //Map che sarˆ popolata con la i pesi redistibuiti per ogni angolo. AZIMUT
public:
    ValutazioneRJ(int _jointindagato);
    //INSERT
    void insert_pesiredzenit(int _n, float _p);
    void insert_pesiredazimut(int _n, float _p);
};


#endif
