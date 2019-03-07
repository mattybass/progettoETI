#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <set>
#include <cmath>
#include <fstream>
#include <sstream>

#include "angolo.h"
#include "Frame.h"
#include "utility.h"

using namespace std;

class Persona{
private:
    map<int,Frame> sequenzaframe; //Contiene tutti i frame ordinati tramite una chiave: il numero progressivo.
    map<int,list<Angolo>> sequenzaangolo; //MAP con chaive nome dell'angolo e argomento lista di Angolo. Rappresenta l'andamento temporale dei vari angolii. [Variazione nel empo: NB siamo nel discreto]
	map<int, list<Angolo>> sequenzaangoloelab;
	map<int,set<int>> max_min_angoli_zenit; //MAP con chiave nome dell'angolo e argomento una set di massimi e minimi relativi che si discostano di una percentuale x dalla media dell'angolo. Per angolo Zenit
    map<int,set<int>> max_min_angoli_azimut;//MAP con chiave nome dell'angolo e argomento una set di massimi e minimi relativi che si discostano di una percentuale x dalla media dell'angolo. Per angolo Azimut
    set<int> framedaanalizzare; //Frame da analizzare, merge dei due set delle map.
    
    //Funzioni
public:
    void popola_max_min_angolo_zenit(int _angolo); //Popola la lista di max min di UN SINGOLO ANGOLO con una tolleranzza specifica.
    void popola_max_min_angolo_azimut(int _angolo); //Popola la lista di max min di UN SINGOLO ANGOLO con una tolleranzza specifica.
	Persona(string nome_file);
	void insert_frame(int _numeroframe); //Crea un frame vuoto e lo inserisce nella map.
    void insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z); //Inserisce una coordinata ad un detrimanto joint in un frame specifico.
    void completa_angoli(int _numeroframe); // Crea e popola la map degli angoli inserita in un determinato frame.
    void popola_sequenzaangolo(); //Da richiamare una volta popolati tutta la map "sequenzaframe" e dopo aver richiamato le varie completa_angoli
    void popola_framedaanalizzare(); // Esegue tutte le funzioni popola_max_min_anogolo necessarie per popoalre le 2 MAP e inoltre popola la set di frame da analizzare.
	void stampa_max(int n);
	void stampa_angoli(int n, bool scelta);
	void stampafile_angoli(int n,string name);
	long double ERi_zenit(int _angolo, int i, int n);
	long double ERi_azimut(int _angolo, int i, int n);
	void test_persona(int n);
	void kamazenit_lista(int _angolo,int period=10, int fast_period=2,int slow_period=30);
	void kamaazimut_lista(int _angolo, int period = 10, int fast_period = 2, int slow_period = 30);
	void media_mobile_angoli(int _angolo, int _finestra);
	void trova_max_min_zenit(int _angolo, int _finestra);
    
    friend ostream& operator <<(ostream& os, const Persona& p);
};

ostream& operator <<(ostream& os, const Persona& p);
#endif
