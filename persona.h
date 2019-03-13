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
	int framepersec;
    map<int,Frame> sequenzaFrame; //Contiene tutti i frame ordinati tramite una chiave: il numero progressivo.
    map<int,list<Angolo>> sequenzaAngolo; //MAP: $ joint, lista di Angolo //andamento temporale dei vari angoli
    map<int,list<Coordinata> > sequenzaCoordinata; //MAP: $ joint, lista di Angolo //andamento temporale delle varie coordinata
	map<int, list<Angolo>> sequenzaAngoloELAB;
    
    map<int, list<Angolo>> valori_maxmin_zenit;
	map<int, list<Angolo>> valori_maxmin_azimut;
    
    //Metodi
	void maxminFind_zenit(int _angolo, int _finestra);
	void maxminFind_azimut(int _angolo, int _finestra);

public:
	Persona(int _framesec, string nome_file,string percorso_file="json");

	//METODI GET
	double get_angoloMedia_zenit(int _angolo, int n_frame);
	double get_angoloMedia_azimut(int _angolo,int n_frame);
    int get_numeroMaxMin_zenit(int _angolo);
    int get_numeroMaxMin_azimut(int _angolo);
	int get_numeroFramePerSecondo()const;
	list<Angolo> get_valorimaxmin_zenit(int _angolo)const;
	list<Angolo> get_valorimaxmin_azimut(int _angolo)const;
	bool jointpresente_zenit(int _joint); //funzione che controlla se è presente quel joint nella map di valori max min e ritorna true se si 
	bool jointpresente_azimut(int _joint);

	//USO PER LETTURA ED INSERIMENTO DATI
	void insert_frame(int _numeroframe); //Crea un frame vuoto e lo inserisce nella map.
    void insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z); //Inserisce una coordinata ad un detrimanto joint in un frame specifico.
    void popola_angolo(int _numeroframe); // Crea e popola la map degli angoli inserita in un determinato frame.
    void popola_sequenzaangolo(); //Da richiamare una volta popolati tutta la map "sequenzaframe" e dopo aver richiamato le varie completa_angoli
    void popola_sequenzacoordinata(); //Da richiamare una volta popolati tutta la map "sequenzaframe"
    

	void mediamobile_angolo(int _angolo, int _finestra);
    void pulisci_errori_seqenzanagolo(int _angolo);//PULISCE ERRRORI PER UN SINGOLO ANGOLO
    void completa_pulisci();//Richiama pulisci errori
    
	void maxminFind_angolo(int _angolo, int _finestra);
	void maxminClean_angolo(int _angolo, double _tolleranzazenit, double _tolleranzaazimut);
    void maxminBE(int _angolo); //Inserisce il punto di inzio e di fine, s enon giˆ inseriti.

	//STAMPE
	void stampaConsole_maxmin(int n);
	void stampaConsole_angolo(int n, bool scelta);
    void stampaFile_coordinate(int n, string name, string percorso_file);
	void stampaFile_angolo(int n, string name, string percorso_file="matlab");
	void stampaFile_maxmin(int n, string name, string percorso_file="matlab");

	void processa_angolo(int _angolo);
    
};

//ostream& operator <<(ostream& os, const Persona& p);

#endif
