#include "valutazioneSJ.h"


ValutazioneSJ::ValutazioneSJ(){
    media_deltadist_zenit=0;
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


void ValutazioneSJ::insert_deltadist_zenit(double _n){
    deltadist_zenit.push_back(_n);
}

void ValutazioneSJ::insert_deltadist_azimut(double _n){
    deltadist_azimut.push_back(_n);
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
	int i = 0;
	cout << endl << endl << "Zenit" << endl;
	cout << "Misure Spaziali" << endl;
	for (iter = deltadist_zenit.begin(); iter!= deltadist_zenit.end(); ++iter) {
		++i;
		cout << "Punto chiave " << i <<" -->";
		cout << *iter << endl;
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
	for (iter = deltadist_azimut.begin(); iter != deltadist_azimut.end(); ++iter) {
		++i;
		cout << "Punto chiave " << i << " -->";
		cout << *iter << endl;
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
    
}

void ValutazioneSJ::insert_deltatime_azimut(){
    
}
