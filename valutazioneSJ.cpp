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
void ValutazioneSJ::insert_deltatimemodello_zenit(double _n){
        deltatimemodello_zenit.push_back(_n);
    
}
void ValutazioneSJ::insert_deltatimepaziente_zenit(double _n) {
	deltatimepaziente_zenit.push_back(_n);

}
void ValutazioneSJ::insert_deltatimemodello_azimut(double _n){
        deltatimemodello_azimut.push_back(_n);
}
void ValutazioneSJ::insert_deltatimepaziente_azimut(double _n) {
	deltatimepaziente_azimut.push_back(_n);
}


void ValutazioneSJ::stampa() {
	vector<double>::iterator iter;
	int i = 0;
	cout << "Zenit" << endl;
	cout << "Spazio" << endl;
	for (iter = deltadist_zenit.begin(); iter!= deltadist_zenit.end(); ++iter) {
		cout << *iter << endl;
	}
	cout << "Velocita modello" << endl;
	for (iter = deltatimemodello_zenit.begin(); iter != deltatimemodello_zenit.end(); ++iter) {
		cout << "Movimento " << i << endl;
		cout << *iter << endl;
		++i;
	}
	i = 0;
	cout << "Velocita paziente" << endl;
	for (iter = deltatimepaziente_zenit.begin(); iter != deltatimepaziente_zenit.end(); ++iter) {
		cout << "Movimento " << i << endl;
		cout << *iter << endl;
		++i;
	}
	cout << "Azimut" << endl;
	cout << "Spazio" << endl;
	for (iter = deltadist_azimut.begin(); iter != deltadist_azimut.end(); ++iter) {
		cout << *iter << endl;
	}
	i = 0;
	cout << "Velocita modello" << endl;
	for (iter = deltatimemodello_azimut.begin(); iter != deltatimemodello_azimut.end(); ++iter) {
		cout << "Movimento " << i << endl;
		cout << *iter << endl;
		++i;
	}
	i = 0;
	cout << "Velocita paziente" << endl;
	for (iter = deltatimepaziente_azimut.begin(); iter != deltatimepaziente_azimut.end(); ++iter) {
		cout << "Movimento " << i << endl;
		cout << *iter << endl;
		++i;
	}
}

void ValutazioneSJ::elaboradati() {

}

