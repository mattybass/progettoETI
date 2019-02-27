#ifndef __FRAME_H_
#define __FRAME_H_

#include <iostream>
#include <map>
#include <string>
#include "angolo.h"
#include "coordinata.h"

class Frame{
private:
    int numeroframe;
    map<int,Coordinata> coordinatejoint;
    map<string,Angolo> angolijoint;
    void insert_angolo(string joint,int a,int b,int c); 
public:
    explicit Frame(int _numeroframe);
    int get_numeroframe()const;
    Coordinata get_coordinata(int _numerojoint);
    Angolo get_anogolo(int _numeroangolo);
    map<int,Coordinata>::const_iterator get_beginiter_cord()const;
    map<int,Coordinata>::const_iterator get_enditer_cord()const;
    map<string,Angolo>::const_iterator get_beginiter_angolo()const;
    map<string,Angolo>::const_iterator get_enditer_angolo()const;
    
    void insert_coordinata(int _numerojoint, double _x, double _y, double _z);

    void completa_angoli();
    
    friend ostream& operator <<(ostream& os, const Frame& f);
    
    
};

ostream& operator <<(ostream& os, const Frame& f);
#endif
