#include "valutazioneSJ.h"


ValutazioneSJ::ValutazioneSJ(int _angolo){
    angolo=_angolo;
    media_deltadist_zenit=0;
    media_deltatime_azimut=0;
    media_deltatime_azimut=0;
    media_deltadist_azimut=0;
}

void ValutazioneSJ::media_deltadist(){
    vector<double>::const_iterator iterV;
    int somma=0;
    int counter=deltadist_zenit.size();
    for(iterV=deltadist_zenit.begin();iterV!=deltadist_zenit.end();++iterV){
        somma=somma+(*iterV);
    }
    if(counter!=0){
        media_deltadist_zenit=(double)somma/counter;
    }else{
        media_deltadist_zenit=0;
    }
    
    int somma1=0;
    int counter1=deltadist_azimut.size();
    for(iterV=deltadist_azimut.begin();iterV!=deltadist_azimut.end();++iterV){
        somma1=somma1+(*iterV);
    }
    if(counter1!=0){
        media_deltadist_azimut=(double)somma1/counter1;
    }else{
        media_deltadist_azimut=0;
    }
    
}

void ValutazioneSJ::media_deltatime(){
    
    vector<double>::const_iterator iterV;
    int somma=0;
    int counter=deltatime_zenit.size();
    for(iterV=deltatime_zenit.begin();iterV!=deltatime_zenit.end();++iterV){
        somma=somma+(*iterV);
    }
    if(counter!=0){
    media_deltatime_zenit=(double)somma/counter;
    }else{
        media_deltatime_zenit=0;
    }
    
    int somma1=0;
    int counter1=deltatime_azimut.size();
    for(iterV=deltatime_azimut.begin();iterV!=deltatime_azimut.end();++iterV){
        somma1=somma1+(*iterV);
    }
    if(counter1!=0){
        media_deltatime_azimut=(double)somma1/counter1;
    }else{
        media_deltatime_azimut=0;
    }
    
}
void ValutazioneSJ::insert_deltadist_zenit(double _n){
    deltadist_zenit.push_back(_n);
}

void ValutazioneSJ::insert_deltadist_azimut(double _n){
    deltadist_azimut.push_back(_n);
}

void ValutazioneSJ::insert_deltatime_zenit(double _n){
        deltatime_zenit.push_back(_n);
    
}
void ValutazioneSJ::insert_deltatime_azimut(double _n){
        deltatime_azimut.push_back(_n);
}
double ValutazioneSJ::get_media_deltadist_zenit(){
    return media_deltadist_zenit;
}
double ValutazioneSJ::get_media_deltadist_azimut(){
    return media_deltadist_azimut;
}

double ValutazioneSJ::get_media_deltatime_zenit(){
    return media_deltatime_zenit;
}

double ValutazioneSJ::get_media_deltatime_azimut(){
    return media_deltatime_azimut;
}

void test_valuta(){
    ValutazioneSJ s(1);
    s.insert_deltadist_azimut(3);
    s.insert_deltadist_azimut(4);
    s.insert_deltadist_azimut(5);
    s.insert_deltadist_zenit(3);
    s.insert_deltadist_zenit(5);
    s.insert_deltadist_zenit(1);
    s.insert_deltatime_zenit(3);
    s.insert_deltatime_zenit(4);
    s.insert_deltatime_zenit(5);
    s.insert_deltatime_azimut(3);
    s.insert_deltatime_azimut(5);
    s.insert_deltatime_azimut(1);
    s.media_deltatime();
    s.media_deltadist();
    cout<< s.get_media_deltadist_zenit()<<endl;
    cout<< s.get_media_deltatime_zenit()<<endl;
    cout<< s.get_media_deltadist_azimut()<<endl;
    cout<< s.get_media_deltatime_azimut()<<endl;
    
}
