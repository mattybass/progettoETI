#include "valutazioneSJ.h"


ValutazioneSJ::ValutazioneSJ(){
    media_deltadist_zenit=0;
    media_deltadist_azimut=0;
}

void ValutazioneSJ::media_deltadist(){
    vector<pair<double,float>>::const_iterator iterV;
    int somma=0;
    float percenutale=0.0;
    int counter=deltadist_zenit.size();
    for(iterV=deltadist_zenit.begin();iterV!=deltadist_zenit.end();++iterV){
        somma=somma+fabs((iterV->first));
        percenutale=percenutale+(fabs((iterV->second)));
    }
    if(counter!=0){
        media_deltadist_zenit=(double)somma/counter;
        media_deltadist_zenit_percento=(float)percenutale/counter;
    }else{
        media_deltadist_zenit=0;
        media_deltadist_zenit_percento=0.0;
    }
    
    int somma1=0;
    float percentuale1=0.0;
    int counter1=deltadist_azimut.size();
    for(iterV=deltadist_azimut.begin();iterV!=deltadist_azimut.end();++iterV){
        somma1=somma1+fabs((iterV->first));
        percentuale1=percentuale1+fabs((iterV->second));
    }
    if(counter1!=0){
        media_deltadist_azimut=(double)somma1/counter1;
        media_deltadist_azimut_percento=(float)percentuale1/counter1;
    }else{
        media_deltadist_azimut=0;
        media_deltadist_azimut_percento=0.0;
    }
    
}


void ValutazioneSJ::insert_deltadist_zenit(double _n, float _p){
    deltadist_zenit.push_back(pair<double,float> (_n,_p));
}

void ValutazioneSJ::insert_deltadist_azimut(double _n, float _p){
    deltadist_azimut.push_back(pair<double,float> (_n,_p));
}
double ValutazioneSJ::get_media_deltadist_zenit() {
	return media_deltadist_zenit;
}
double ValutazioneSJ::get_media_deltadist_azimut() {
	return media_deltadist_azimut;
}
void ValutazioneSJ::insert_duratamovimentimodello_zenit(double _n){
        duratamovimentimodello_zenit.push_back(_n);
    
}
void ValutazioneSJ::insert_duratamovimentipaziente_zenit(double _n) {
	duratamovimentipaziente_zenit.push_back(_n);

}
void ValutazioneSJ::insert_duratamovimentimodello_azimut(double _n){
        duratamovimentimodello_azimut.push_back(_n);
}
void ValutazioneSJ::insert_duratamovimentipaziente_azimut(double _n) {
	duratamovimentipaziente_azimut.push_back(_n);
}


void ValutazioneSJ::stampa() {
	vector<double>::iterator iter;
    vector<pair<double,float>>::iterator iterVP;
	int i = 0;
	cout << endl << endl << "Zenit" << endl;
	cout << "Misure Spaziali" << endl;
	for (iterVP = deltadist_zenit.begin(); iterVP!= deltadist_zenit.end(); ++iterVP) {
		++i;
		cout << "Punto chiave " << i <<" -->";
		cout << iterVP->first << "Percentuale"<< iterVP->second<< endl;
	}
	i = 0;
	cout << endl << "Misure di velocita" << endl;
	cout << "Velocita modello" << endl;
	for (iter = duratamovimentimodello_zenit.begin(); iter != duratamovimentimodello_zenit.end(); ++iter) {
		++i;
		cout << "Movimento " << i << " -->";
		cout << *iter << endl;
	}
	i = 0;
	cout << "Velocita paziente" << endl;
	for (iter = duratamovimentipaziente_zenit.begin(); iter != duratamovimentipaziente_zenit.end(); ++iter) {
		++i;
		cout << "Movimento " << i << " -->";
		cout << *iter << endl;
	}
	cout << endl << "Azimut" << endl;
	cout << "Misure Spaziali" << endl;
	for (iterVP = deltadist_azimut.begin(); iterVP != deltadist_azimut.end(); ++iterVP) {
		++i;
		cout << "Punto chiave " << i << " -->";
		cout << iterVP->first << "Percentuale"<< iterVP->second<< endl;
	}
	i = 0;
	cout << endl << "Misure di velocita" << endl;
	cout << "Velocita modello" << endl;
	for (iter = duratamovimentimodello_azimut.begin(); iter != duratamovimentimodello_azimut.end(); ++iter) {
		++i;
		cout << "Movimento " << i << " -->";
		cout << *iter << endl;
	}
	i = 0;
	cout << "Velocita paziente" << endl;
	for (iter = duratamovimentipaziente_azimut.begin(); iter != duratamovimentipaziente_azimut.end(); ++iter) {
		++i;
		cout << "Movimento " << i << " -->";
		cout << *iter << endl;
	}
}

void ValutazioneSJ::elaboradati() {

}


void ValutazioneSJ::insert_deltatime_zenit(){
    vector<double>::const_iterator iterVM;
    vector<double>::const_iterator iterVP;
    double differenza;
    float percentuale;
    
    iterVM=duratamovimentimodello_zenit.begin();
    iterVP=duratamovimentipaziente_zenit.begin();
    while(iterVM!=duratamovimentimodello_zenit.end()&&iterVP!=duratamovimentipaziente_zenit.end()){
        differenza=(*iterVM)-(*iterVP);
        percentuale=(((float)(*iterVP)/(float)(*iterVM))*100.0);
        
        if(percentuale>100.0){
            if(percentuale>200.0){
                percentuale=0;
            }else{
                percentuale=percentuale-100.0;
            }
        }
        deltatime_zenit.push_back(pair<double,float> (differenza,percentuale));
        ++iterVM;
        ++iterVP;
    }
}

void ValutazioneSJ::insert_deltatime_azimut(){
    vector<double>::const_iterator iterVM;
    vector<double>::const_iterator iterVP;
    double differenza;
    float percentuale;
    
    iterVM=duratamovimentimodello_azimut.begin();
    iterVP=duratamovimentipaziente_azimut.begin();
    while(iterVM!=duratamovimentimodello_azimut.end()&&iterVP!=duratamovimentipaziente_azimut.end()){
        differenza=(*iterVM)-(*iterVP);
        percentuale=(((float)(*iterVP)/(float)(*iterVM))*100.0);
        
        if(percentuale>100.0){
            if(percentuale>200.0){
                percentuale=0;
            }else{
                percentuale=percentuale-100.0;
            }
        }
        deltatime_azimut.push_back(pair<double,float> (differenza,percentuale));
        ++iterVM;
        ++iterVP;
    }
    
}

void ValutazioneSJ::media_deltatime(){
    vector<pair<double,float>>::const_iterator iterV;
    int somma=0;
    float percenutale=0.0;
    int counter=deltatime_zenit.size();
    for(iterV=deltatime_zenit.begin();iterV!=deltatime_zenit.end();++iterV){
        somma=somma+(iterV->first);
        percenutale=percenutale+(iterV->second);
    }
    if(counter!=0){
        media_deltatime_zenit=(double)somma/counter;
        media_deltadist_zenit_percento=(float)percenutale/counter;
    }else{
        media_deltatime_zenit=0;
        media_deltadist_zenit_percento=0.0;
    }
    
    int somma1=0;
    float percentuale1=0.0;
    int counter1=deltatime_azimut.size();
    for(iterV=deltatime_azimut.begin();iterV!=deltatime_azimut.end();++iterV){
        somma1=somma1+(iterV->first);
        percentuale1=percentuale1+(iterV->second);
    }
    if(counter1!=0){
        media_deltatime_azimut=(double)somma1/counter1;
        media_deltatime_azimut_percento=(float)percentuale1/counter1;
    }else{
        media_deltatime_azimut=0;
        media_deltatime_azimut_percento=0.0;
    }
    
}

vector<pair<double,float>> ValutazioneSJ::get_deltadist_zenit()const{
    return deltadist_zenit;
}
vector<pair<double,float>> ValutazioneSJ::get_deltatime_zenit()const{
    return deltatime_zenit;
}
double ValutazioneSJ::get_media_deltadist_zenit()const{
    return media_deltadist_zenit;
}
float ValutazioneSJ::get_media_deltadist_zenit_percento()const{
    return media_deltadist_zenit_percento;
}
double ValutazioneSJ::get_media_deltatime_zenit()const{
    return media_deltatime_zenit;
}
float ValutazioneSJ::get_media_deltatime_zenit_percento()const{
    return media_deltatime_zenit_percento;
}
vector<pair<double,float>> ValutazioneSJ::get_deltadist_azimut()const{
    return deltadist_azimut;
}
vector<pair<double,float>> ValutazioneSJ::get_deltatime_azimut()const{
    return deltatime_azimut;
}
double ValutazioneSJ::get_media_deltadist_azimut()const{
    return media_deltadist_azimut;
}
float ValutazioneSJ::get_media_deltadist_azimut_percento()const{
    return media_deltadist_azimut_percento;
}
double ValutazioneSJ::get_media_deltatime_azimut()const{
    return media_deltatime_azimut;
}
float ValutazioneSJ::get_media_deltatime_azimut_percento()const{
    return media_deltatime_azimut_percento;
}

void ValutazioneSJ::calcola_accuratezza(){
    accuratezza_azimut=(media_deltadist_azimut_percento+media_deltatime_azimut_percento)/2;
    accuratezza_zenit=(media_deltadist_zenit_percento+media_deltatime_zenit_percento)/2;
    
        accuratezza=(accuratezza_zenit+accuratezza_azimut)/2;
}

float ValutazioneSJ::get_accuratezza_azimut()const{
    return accuratezza_azimut;
}
float ValutazioneSJ::get_accuratezza_zenit()const{
    return accuratezza_zenit;
}
float ValutazioneSJ::get_accuratezza()const{
    return accuratezza;
}
