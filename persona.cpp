#include "persona.h"

Persona::Persona(string nome_file, string percorso_file) {
	ifstream i(percorso_file + "/" + nome_file);

	string line, linecoord, estratta;

	string str_r = "\"";
	size_t found, found2;
    int frame=0;
    int joint;
	int exit_value=0; 
	/*per sapere se posso andare a utilizzare completa_angoli
	+1 se trovo {, -1 se trovo }*/
	double x, y, z;

	while (getline(i, line)) {

		if (line.find("{") != std::string::npos)
			exit_value++;
		if (line.find("}") != std::string::npos) {
			exit_value--;
			if (exit_value == 1 && frame != 0) {
				popola_angolo(frame);
			}

		}
			
		found = line.find("frame");
		if (found != std::string::npos) {
			//estrai frame;

			found2 = line.find(str_r, 5); //il primo " � in posizione 4
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = line.substr(11, found2 - 11); //substr(inizio,nCaratteri)
				//converto da string a int
				stringstream s(estratta);
				s >> frame;
				insert_frame(frame);
				//cout << "FRAME " << frame << endl;
			}
		}


		found = line.find("joint");
		if (found != std::string::npos) {
			//estrai joint;

			found2 = line.find(str_r, 13); //il primo " � in posizione 12
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = line.substr(19, found2 - 19); //substr(inizio,nCaratteri)
				//converto da string a int
				stringstream s3(estratta);
				s3 >> joint;
			}

			//estraggo x
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " � in posizione 4
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = linecoord.substr(22, found2 - 22); //substr(inizio,nCaratteri)
				//converto da string a double
				stringstream s(estratta);
				s >> x;
			}
			//estraggo y
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " � in posizione 4
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = linecoord.substr(22, found2 - 22); //substr(inizio,nCaratteri)
				//converto da string a double
				stringstream s(estratta);
				s >> y;
			}

			//estraggo z
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " � in posizione 22
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = linecoord.substr(22, found2 - 22); //substr(inizio,nCaratteri)
				//converto da string a double
				stringstream s(estratta);
				s >> z;
			}
			insert_coordinata(frame, joint, z, x, y);
		}

	}

	i.close();
	popola_sequenzaangolo();
	sequenzaAngoloELAB = sequenzaAngolo;

}

void Persona::insert_frame(int _numeroframe){
    sequenzaFrame.insert(pair<int,Frame> (_numeroframe,Frame(_numeroframe)));
}

void Persona::insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z){
    map<int,Frame>::iterator iter;
    iter=sequenzaFrame.find(_numeroframe);
    if(iter!=sequenzaFrame.end()){
        iter->second.insert_coordinata(_numerojoint, _x, _y, _z);
    }else{
        cout<<"ERRORE: frame non trovato, coordinata non inserita"<<endl;
    }
}

void Persona::popola_angolo(int _numeroframe){
    map<int,Frame>::iterator iter;
    iter=sequenzaFrame.find(_numeroframe);
    
    if(iter!=sequenzaFrame.end()){
        iter->second.completa_angolo();
    }else{
        cout<<"ERRORE: frame non trovato, angoli non creati"<<endl;
    }
}

void Persona::popola_sequenzaangolo(){
    map<int,Frame>::iterator iter;
    map<int,Angolo> tmp;
    map<int,Angolo>::iterator itertmp;
    for (iter=sequenzaFrame.begin(); iter!=sequenzaFrame.end(); ++iter) {
        tmp=iter->second.get_angolijoint();
        for(itertmp=tmp.begin();itertmp!=tmp.end();++itertmp){
            sequenzaAngolo[itertmp->first].push_back(itertmp->second);
        }
    }
}

void Persona::maxminFind_zenit(int _angolo, int _finestra) {
	map<int, list<Angolo> >::iterator iter;
	iter = sequenzaAngoloELAB.find(_angolo);

	if (iter != sequenzaAngoloELAB.end()) { //ho trovato l'angolo
		list<Angolo>::iterator liter;
		list<Angolo>::iterator liter2;
		list<Angolo>::iterator liter3;
		map<int, Frame> miter;
		int max_o_min = 1;
		int tipo_angolo = 0;
		int cont = 0;
		liter = iter->second.begin();
		++liter;
		while (liter != (iter->second).end()) {
			liter2 = liter;
			liter3 = liter;
			++liter2;
			--liter3;
			while (liter2 != (iter->second).end() && liter3 != (iter->second).begin() && cont!=0) {
				
				if(((*liter).get_zenit() > (*liter2).get_zenit()) && ((*liter).get_zenit() > (*liter3).get_zenit()) && max_o_min != 0) {
					tipo_angolo = 1;
				}
				else if (((*liter).get_zenit() < (*liter2).get_zenit()) && ((*liter).get_zenit() < (*liter3).get_zenit()) && max_o_min != 0) {
					tipo_angolo = -1;
				}
				else
					max_o_min = 0;

				++liter2;
				--liter3;
				cont--;
			}
			if (max_o_min != 0) {
				Angolo a = (*liter);
				a.set_maxmin(tipo_angolo);
				valori_maxmin_zenit[_angolo].push_back(a);
			}
			++liter;
			max_o_min = 1;
			tipo_angolo = 0;
			cont = _finestra;
		}
		
	}
}

void Persona::maxminFind_azimut(int _angolo, int _finestra) {
	map<int, list<Angolo> >::iterator iter;
	iter = sequenzaAngoloELAB.find(_angolo);

	if (iter != sequenzaAngoloELAB.end()) { //ho trovato l'angolo
		list<Angolo>::iterator liter;
		list<Angolo>::iterator liter2;
		list<Angolo>::iterator liter3;
		int max_o_min = 1; 
		int tipo_angolo = 0;
		int cont = 0;
		liter = iter->second.begin();
		++liter;
		while (liter != (iter->second).end()) {
			liter2 = liter;
			liter3 = liter;
			++liter2;
			--liter3;
			while (liter2 != (iter->second).end() && liter3 != (iter->second).begin() && cont != 0) {

				if (((*liter).get_azimut() > (*liter2).get_azimut()) && ((*liter).get_azimut() > (*liter3).get_azimut()) && max_o_min != 0) {
					tipo_angolo = 1;
				}
				else if (((*liter).get_azimut() < (*liter2).get_azimut()) && ((*liter).get_azimut() < (*liter3).get_azimut()) && max_o_min != 0) {
					tipo_angolo = -1;
				}
				else
					max_o_min = 0;

				++liter2;
				--liter3;
				cont--;
			}
			if (max_o_min != 0) {
				Angolo a=(*liter);
				a.set_maxmin(tipo_angolo);
				valori_maxmin_azimut[_angolo].push_back(a);
			}
			++liter;
			max_o_min = 1;
			tipo_angolo = 0;
			cont = _finestra;
		}

	}
}

void Persona::maxminFind_angolo(int _angolo, int _finestra) {
	maxminFind_zenit(_angolo, _finestra);
	maxminFind_azimut(_angolo, _finestra);
}

void Persona::stampaConsole_maxmin(int n) {
	map<int, list<Angolo> >::const_iterator miter;
	list<Angolo>::const_iterator liter;
	miter = valori_maxmin_zenit.find(n);
	cout << "JOINT " << miter->first << ": " << endl;
	cout << "frame; azimut; zenitMAX" << endl;
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		cout << (*liter) << endl;
	}
	cout << endl;
	miter = valori_maxmin_azimut.find(n);
	cout << "JOINT " << miter->first << ": " << endl;
	cout << "frame; azimutMAX; zenit" << endl;
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		cout << (*liter) << endl;
	}
}

void Persona::stampaConsole_angolo(int n, bool scelta) {
	map<int, list<Angolo> >::const_iterator miter;
	list<Angolo>::const_iterator liter;
	if (scelta == true)
		miter = sequenzaAngolo.find(n);
	else
		miter = sequenzaAngoloELAB.find(n);
	cout << "JOINT " << miter->first << ": " << endl;
	cout << "frame; azimut; zenit" << endl;
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		cout << (*liter) << endl;
	}
}

void Persona::stampaFile_angolo(int n, string name, string percorso_file) {
	map<int, list<Angolo> >::const_iterator miter;
	list<Angolo>::const_iterator liter;
	ofstream file;
	string l = percorso_file + "/" + name + ".txt";
	file.open(l.c_str(), ios::out);
	miter = sequenzaAngolo.find(n);
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		file << (*liter) << endl;
	}
	ofstream file2;
	string l2 = percorso_file + "/" + name + "ELAB.txt";
	file2.open(l2.c_str(), ios::out);
	miter = sequenzaAngoloELAB.find(n);
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		file2 << (*liter) << endl;
	}
}

void Persona::mediamobile_angolo(int _angolo, int _finestra) {
	map<int, list < Angolo> >::iterator iter;
	list<Angolo>::iterator liter;
	list<Angolo>::iterator liter2;
	list<Angolo>::iterator liter3;
	double sum_zenit;
	double sum_azimut;
	iter = sequenzaAngoloELAB.find(_angolo);
	if (iter != sequenzaAngoloELAB.end()) { //ho trovato l'angolo
		int s = (iter->second).size();
		liter = iter->second.begin();
		for (int i = 0; i < (s - _finestra); ++i) {
			liter3 = liter;
			for (int i = 0; i < (_finestra / 2); ++i)
				++liter3;
			sum_azimut = 0;
			sum_zenit = 0;
			liter2 = liter;
			for (int i = 0; i < _finestra; ++i) {
				sum_zenit = sum_zenit + (*liter2).get_zenit();
				sum_azimut = sum_azimut + (*liter2).get_azimut();
				++liter2;
			}
			(*liter3).set_azimut(sum_azimut / _finestra);
			(*liter3).set_zenit(sum_zenit / _finestra);
			++liter;
		}
	}
	else
		cout << "Angolo non trovato!" << endl;
}

/*ostream& operator <<(ostream& os, const Persona& p) {
	map<int, set<int>>::const_iterator iter1;
	set<int>::const_iterator iter1a;
	map<int, set<int>>::const_iterator iter2;
	set<int>::const_iterator iter2a;


	cout << "Massimi/minimi Azimut joint 1: " << endl;
	iter2 = p.maxmin_azimut.find(1);
	if (iter2 != p.maxmin_azimut.end()) {
		for (iter2a = iter2->second.begin(); iter2a != iter2->second.end(); ++iter2a) {
			cout << (*iter2a) << "; ";
		}
	}
	return os;
}*/

void Persona::pulisci_max_min(int _angolo) {
	map<int, list<Angolo>>::iterator iter;
	iter = valori_maxmin_zenit.find(_angolo);
	list<Angolo> temp;
	if (iter != valori_maxmin_zenit.end()){ //ho trovato l angolo
		list<Angolo>::iterator iter2;
		list<Angolo>::iterator inizio;
		inizio = (iter->second).begin();
		int i = (*inizio).get_numeroframe();
		for (iter2 = (iter->second).begin(); iter2 != (iter->second).end(); ++iter2) {
			if ((*iter2).get_numeroframe() > (i + 15))
				temp.push_back(*iter2);
		}
		valori_maxmin_zenit.erase(iter);
		valori_maxmin_zenit[_angolo] = temp;
	}
	iter = valori_maxmin_azimut.find(_angolo);
	temp.clear();
	if (iter != valori_maxmin_azimut.end()) { //ho trovato l angolo
		list<Angolo>::iterator iter2;
		list<Angolo>::iterator inizio;
		inizio = (iter->second).begin();
		int i = (*inizio).get_numeroframe();
		for (iter2 = (iter->second).begin(); iter2 != (iter->second).end(); ++iter2) {
			if ((*iter2).get_numeroframe() > (i + 15))
				temp.push_back(*iter2);
		}
		valori_maxmin_azimut.erase(iter);
		valori_maxmin_azimut[_angolo] = temp;
	}

}



