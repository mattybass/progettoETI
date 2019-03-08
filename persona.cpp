#include "persona.h"

Persona::Persona(string nome_file) {
	ifstream i(nome_file);

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
	iter = sequenzaAngolo.find(_angolo);

	if (iter != sequenzaAngolo.end()) { //ho trovato l'angolo
		list<Angolo>::iterator liter;
		list<Angolo>::iterator liter2;
		list<Angolo>::iterator liter3;
		liter = iter->second.begin();
		for (int i = 0; i < _finestra; ++i) {
			++liter;
		}
		int s = (iter->second).size();
		int max_o_min;
		for (int i = 0; i < s - _finestra; ++i) {
			liter2 = liter;
			liter3 = liter;
			++liter2;
			--liter3;
			max_o_min = 1;
			for (int i = 0; i < _finestra - 1; ++i) {
				if (((float)(*liter).get_zenit() > (float)(*liter2).get_zenit()) && ((float)(*liter).get_zenit() > (float)(*liter3).get_zenit()) && max_o_min != 0) {
					++liter2;
					--liter3;
				}
				else
					if (((float)(*liter).get_zenit() < (float)(*liter2).get_zenit()) && ((float)(*liter).get_zenit() < (float)(*liter3).get_zenit()) && max_o_min != 0) {
						++liter2;
						--liter3;
					}
					else
						max_o_min = 0;
			}
			if (max_o_min != 0) {
				maxmin_zenit[_angolo].insert((*liter).get_numeroframe());
			}
			++liter;
		}
	}
}

void Persona::maxminFind_azimut(int _angolo, int _finestra) {
	map<int, list<Angolo> >::iterator iter;
	iter = sequenzaAngolo.find(_angolo);

	if (iter != sequenzaAngolo.end()) { //ho trovato l'angolo
		list<Angolo>::iterator liter;
		list<Angolo>::iterator liter2;
		list<Angolo>::iterator liter3;
		liter = iter->second.begin();
		for (int i = 0; i < _finestra; ++i) {
			++liter;
		}
		int s = (iter->second).size();
		int max_o_min;
		for (int i = 0; i < s - _finestra; ++i) {
			liter2 = liter;
			liter3 = liter;
			++liter2;
			--liter3;
			max_o_min = 1;
			for (int i = 0; i < _finestra - 1; ++i) {
				if (((float)(*liter).get_azimut() > (float)(*liter2).get_azimut()) && ((float)(*liter).get_azimut() > (float)(*liter3).get_azimut()) && max_o_min != 0) {
					++liter2;
					--liter3;
				}
				else
					if (((float)(*liter).get_azimut() < (float)(*liter2).get_azimut()) && ((float)(*liter).get_azimut() < (float)(*liter3).get_azimut()) && max_o_min != 0) {
						++liter2;
						--liter3;
					}
					else
						max_o_min = 0;
			}
			if (max_o_min != 0) {
				maxmin_azimut[_angolo].insert((*liter).get_numeroframe());
			}
			++liter;
		}
	}
}

void Persona::maxminFind_angolo(int _angolo, int _finestra) {
	maxminFind_azimut(_angolo, _finestra);
<<<<<<< Updated upstream
	maxminFind_zenit(_angolo, _finestra);
=======
	//maxminFind_zenit(_angolo, _finestra);
>>>>>>> Stashed changes
}

void Persona::stampaConsole_maxmin(int n) {
	map<int, set<int>>::const_iterator iter1;
	set<int>::const_iterator iter1a;
	map<int, set<int>>::const_iterator iter2;
	set<int>::const_iterator iter2a;
	cout << "JOINT " << n << ": massimi e minimi" << endl;
	cout << "zenit-> ";
	iter1 = maxmin_zenit.find(n);
	if (iter1 != maxmin_zenit.end()) {
		for (iter1a = iter1->second.begin(); iter1a != iter1->second.end(); ++iter1a) {
			cout << (*iter1a) << "; ";
		}
	}
	cout << endl;

	cout << "azimut-> ";
	iter2 = maxmin_azimut.find(n);
	if (iter2 != maxmin_azimut.end()) {
		for (iter2a = iter2->second.begin(); iter2a != iter2->second.end(); ++iter2a) {
			cout << (*iter2a) << "; ";
		}
	}
	cout << endl;
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

void Persona::stampaFile_angolo(int n, string name) {
	map<int, list<Angolo> >::const_iterator miter;
	list<Angolo>::const_iterator liter;
	ofstream file;
	string l = "Matlab/"+name + ".txt";
	file.open(l.c_str(), ios::out);
	miter = sequenzaAngolo.find(n);
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		file << (*liter) << endl;
	}
	ofstream file2;
	string l2 = name + "ELAB.txt";
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
	double sum_zenit;
	double sum_azimut;
	iter = sequenzaAngolo.find(_angolo);
	if (iter != sequenzaAngolo.end()) { //ho trovato l'angolo
		int s = (iter->second).size();
		liter = iter->second.begin();
		for (int i = 0; i < (s - _finestra); ++i) {
			sum_azimut = 0;
			sum_zenit = 0;
			liter2 = liter;
			for (int i = 0; i < _finestra; ++i) {
				sum_zenit = sum_zenit + (*liter2).get_zenit();
				sum_azimut = sum_azimut + (*liter2).get_azimut();
				++liter2;
			}
			(*liter).set_azimut(sum_azimut / _finestra);
			(*liter).set_zenit(sum_zenit / _finestra);
			++liter;
		}
	}
	else
		cout << "Angolo non trovato!" << endl;
}

ostream& operator <<(ostream& os, const Persona& p) {
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
}



