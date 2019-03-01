#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <set>
#include "angolo.h"
#include "Frame.h"

class Persona{
private:
    map<int,Frame> sequenzaframe; //Contiene tutti i frame ordinati tramite una chiave: il numero progressivo.
    map<string,list<Angolo>> sequenzaangolo; //MAP con chaive nome dell'angolo e argomento lista di Angolo. Rappresenta l'andamento temporale dei vari angolii. [Variazione nel empo: NB siamo nel discreto]
    set<int> framedaanalizzare;
    map<string,set<int>> framexangolo;
    
public:
    void insert_frame(int _numeroframe); //Crea un frame vuoto e lo insrisce nella map.
    void insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z); //Inserisce una coordinata ad un detrimanto joint in un frame specifico.
    void completa_angoli(int _numeroframe); // Crea e popola la map degli angoli inserita in un determinato frame.
    void popola_sequenzaangolo(); //Da richiamare una volta popolati tutta la map "suqenezaframe" e dopo aver richiamato le varie completa_angoli
    
    
    friend ostream& operator <<(ostream& os, const Frame& f);
};

ostream& operator <<(ostream& os, const Frame& f);
#endif
