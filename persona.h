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
#include <nlohmann/json.hpp> //per funzionare bisogna aggiungere il file json.hpp (contenuto nella cartella nlohmann) all'interno della cartella del vostro compilatore 

#include "angolo.h"
#include "Frame.h"
#include "utility.h"

using namespace std;

class Persona{
private:
    map<int,Frame> sequenzaframe; //Contiene tutti i frame ordinati tramite una chiave: il numero progressivo.
    map<string,list<Angolo>> sequenzaangolo; //MAP con chaive nome dell'angolo e argomento lista di Angolo. Rappresenta l'andamento temporale dei vari angolii. [Variazione nel empo: NB siamo nel discreto]
    map<string,set<int>> max_min_angoli; //MAP con chiave nome dell'angolo e argomento una set di massimi e minimi relativi che si discostano di una percentuale x dalla media dell'angolo.
    set<int> framedaanalizzare;
    map<string,set<int>> framexangolo;
    
    
    void popola_max_min_angolo(string _angolo, float _tolleranzaazimut, float _toleranzazenit); //Popola la lista di max min di UN SINGOLO ANGOLO con una tolleranzza specifica.
public:
	Persona(string nome_file);
	void insert_frame(int _numeroframe); //Crea un frame vuoto e lo inserisce nella map.
    void insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z); //Inserisce una coordinata ad un detrimanto joint in un frame specifico.
    void completa_angoli(int _numeroframe); // Crea e popola la map degli angoli inserita in un determinato frame.
    void popola_sequenzaangolo(); //Da richiamare una volta popolati tutta la map "sequenzaframe" e dopo aver richiamato le varie completa_angoli
    
    
    
    friend ostream& operator <<(ostream& os, const Frame& f);
};

ostream& operator <<(ostream& os, const Frame& f);
#endif
