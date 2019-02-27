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
    map<int,Frame> sequenzaframe;
    map<string,list<Angolo>> sequenzaangolo;
    set<int> framedaanalizzare;
    map<string,set<int>> framexangolo;
    void insert_maplist(Frame);
    void insert_set();
    void insert_mapset();
public:
    map<int,Frame>::const_iterator get_beginiter_frame()const;
    map<int,Frame>::const_iterator get_enditer_frame()const;
    set<int>::const_iterator get_beginiter_anal()const;
    set<int>::const_iterator get_enditer_anal()const;
    void insert(Frame);
    
    
    friend ostream& operator <<(ostream& os, const Frame& f);
    
    
};

ostream& operator <<(ostream& os, const Frame& f);
#endif
