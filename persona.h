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
    map<int,Frame> sequenzaFrame; //Contiene tutti i frame ordinati tramite una chiave: il numero progressivo.
    map<int,list<Angolo>> sequenzaAngolo; //MAP: $ joint, lista di Angolo //andamento temporale dei vari angoli
	map<int, list<Angolo>> sequenzaAngoloELAB;
	map<int,set<int>> maxmin_zenit; //MAP con chiave nome dell'angolo e argomento una set di massimi e minimi relativi che si discostano di una percentuale x dalla media dell'angolo. Per angolo Zenit
    map<int,set<int>> maxmin_azimut;//MAP con chiave nome dell'angolo e argomento una set di massimi e minimi relativi che si discostano di una percentuale x dalla media dell'angolo. Per angolo Azimut
    
    //Funzioni
	void maxminFind_zenit(int _angolo, int _finestra);
	void maxminFind_azimut(int _angolo, int _finestra);

public:
	Persona(string nome_file);

	//USO PER LETTURA ED INSERIMENTO DATI
	void insert_frame(int _numeroframe); //Crea un frame vuoto e lo inserisce nella map.
    void insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z); //Inserisce una coordinata ad un detrimanto joint in un frame specifico.
    void popola_angolo(int _numeroframe); // Crea e popola la map degli angoli inserita in un determinato frame.
    void popola_sequenzaangolo(); //Da richiamare una volta popolati tutta la map "sequenzaframe" e dopo aver richiamato le varie completa_angoli
    void popola_framedaanalizzare(); // Esegue tutte le funzioni popola_max_min_anogolo necessarie per popoalre le 2 MAP e inoltre popola la set di frame da analizzare.

	void mediamobile_angolo(int _angolo, int _finestra);
	void maxminFind_angolo(int _angolo, int _finestra);

	//STAMPE
	void stampaConsole_maxmin(int n);
	void stampaConsole_angolo(int n, bool scelta);
	void stampaFile_angolo(int n, string name);
    
    friend ostream& operator <<(ostream& os, const Persona& p);
};

ostream& operator <<(ostream& os, const Persona& p);

#endif
