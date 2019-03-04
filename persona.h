#ifndef __PERSONA_H__
#define __PERSONA_H__

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
    map<int,set<int>> max_min_angoli_zenit; //MAP con chiave nome dell'angolo e argomento una set di massimi e minimi relativi che si discostano di una percentuale x dalla media dell'angolo.
    map<int,set<int>> max_min_angoli_azimut;
    set<int> framedaanalizzare;
    map<int,set<int>> framexangolo;
    
    //Funzioni
    void popola_max_min_angolo_zenit(string _angolo, float _tolleranzazenit); //Popola la lista di max min di UN SINGOLO ANGOLO con una tolleranzza specifica.
    void popola_max_min_angolo_azimut(string _angolo, float _tolleranzaazimut); //Popola la lista di max min di UN SINGOLO ANGOLO con una tolleranzza specifica.
public:
	Persona(string nome_file);
	void insert_frame(int _numeroframe); //Crea un frame vuoto e lo inserisce nella map.
    void insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z); //Inserisce una coordinata ad un detrimanto joint in un frame specifico.
    void completa_angoli(int _numeroframe); // Crea e popola la map degli angoli inserita in un determinato frame.
    void popola_sequenzaangolo(); //Da richiamare una volta popolati tutta la map "sequenzaframe" e dopo aver richiamato le varie completa_angoli
    void popola_framedaanalizzare(); // Esegue tutte le funzioni popola_max_min_anogolo necessarie per popoalre le 2 MAP e inoltre popola la set di frame da analizzare.
    
    
    friend ostream& operator <<(ostream& os, const Persona& p);
};

ostream& operator <<(ostream& os, const Persona& p);
#endif
