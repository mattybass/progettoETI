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
    map<int,Coordinata> coordinatejoint; //MAP con chiave numero di joint e argomento la Coordinata relativa
    map<string,Angolo> angolijoint; ////MAP con chiave nome angolo e argomento l'Angolo relativo
    void insert_angolo(string _joint,int a,int b,int c); //Funzione che trasforma 3 coordiante in un'angolo, usata nella funzione public "void completa_angoli();"
public:
    explicit Frame(int _numeroframe); //Costruttore ad un parametro esplicito
    int get_numeroframe()const; //Ritorna il numero di frame
    Coordinata get_coordinata(int _numerojoint); // Ritorna la coordinata relativa ad uno specifico joint
    Angolo get_anogolo(int _numeroangolo);// Ritorna l'angolo relativo ad uno specifico joint
    void insert_coordinata(int _numerojoint, double _x, double _y, double _z);//Inserisce coordinate nella map di interi coordinata
    void completa_angoli();//da richiamare dopo l'inserimento di tutte le coordinate, popola la map di stringhe e angoli utilizzando la funzione private "insert_angolo"
    map<string,Angolo> get_angolijoint()const; //Ritorna una copia della MAP "angolijoint"
    
    friend ostream& operator <<(ostream& os, const Frame& f);
    
    
};

ostream& operator <<(ostream& os, const Frame& f);
#endif
