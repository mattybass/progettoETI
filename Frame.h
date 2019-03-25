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
    map<int,Coordinata> coordinatejoint; //MAP: $->numero di joint, coordinata relativa
    map<int,Angolo> angolijoint; ////MAP: &->numero angolo, valore angolo
	//METODI
    void insert_angolo(int _joint,int a,int b,int c); //Funzione che trasforma 3 coordiante in un'angolo, usata nella funzione public "void completa_angolo();"

public:
    explicit Frame(int _numeroframe); //Costruttore ad un parametro esplicito
    
    void set_angolo_zenit(int n, double nu);
    void set_angolo_azimut(int n, double nu);
    
	//METODI GET
	int get_numeroframe()const; //Ritorna il numero di frame
    Coordinata get_coordinata(int _numerojoint); // Ritorna la coordinata relativa ad uno specifico joint
	map<int,Angolo> get_angolijoint()const; //Ritorna una copia della MAP "angolijoint"
	Angolo restituisci_angolo(int _angolo)const;
    map<int,Coordinata> get_coordinatejoit()const; //Ritorna una copia della MAP "coordinatejoint"

	//INSERIMENTO DATI
	void insert_coordinata(int _numerojoint, double _x, double _y, double _z);//Inserisce coordinate nella map di interi coordinata
    void completa_angolo();//da richiamare dopo l'inserimento di tutte le coordinate, popola la map di stringhe e angoli utilizzando la funzione private "insert_angolo"
    
	
    friend ostream& operator <<(ostream& os, const Frame& f);
    
    
};

ostream& operator <<(ostream& os, const Frame& f);
#endif
