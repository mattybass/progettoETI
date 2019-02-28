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
    map<string,list<Angolo>> sequenzaangolo;
    map<string,set<int>> framexangolo;
    set<int> framedaanalizzare;
    
public:
    void insert_frame(int _numeroframe); //Crea un frame vuoto e lo insrisce nella map.
    void insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z); //Inserisce una coordinata ad un detrimanto joint in un frame specifico.
    void completa_angoli(int _numeroframe); // Crea e popola la map degli angoli inserita in un determinato frame.
    
    
    friend ostream& operator <<(ostream& os, const Frame& f);
};

ostream& operator <<(ostream& os, const Frame& f);
#endif
