#include "valutazioneRJ.h"

ValutazioneRJ::ValutazioneRJ(int _jointindagato){
    jointindagato=_jointindagato;
}

void ValutazioneRJ::insert_pesiredzenit(int _n, float _p){
    pesired_zenit.insert(pair<int,float> (_n,_p));
}

void ValutazioneRJ::insert_pesiredazimut(int _n, float _p){
    pesired_azimut.insert(pair<int,float> (_n,_p));
}
