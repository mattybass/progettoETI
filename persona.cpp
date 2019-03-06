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
				completa_angoli(frame);
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

		/*		found = line.find("person");
				if (found != std::string::npos) {
					//estrai person;
				}*/

		found = line.find("joint");
		if (found != std::string::npos) {
			//estrai joint;

			found2 = line.find(str_r, 13); //il primo " � in posizione 12
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = line.substr(19, found2 - 19); //substr(inizio,nCaratteri)
				//converto da string a int
				stringstream s3(estratta);
				s3 >> joint;
				//cout << "JOINT " << joint << endl;
			}

			//estraggo x
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " � in posizione 4
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = linecoord.substr(22, found2 - 22); //substr(inizio,nCaratteri)
				//converto da string a double
				stringstream s(estratta);
				s >> x;
				//cout << endl << "X="<<x;
			}
			//estraggo y
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " � in posizione 4
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = linecoord.substr(22, found2 - 22); //substr(inizio,nCaratteri)
				//converto da string a double
				stringstream s(estratta);
				s >> y;
				//cout << endl << "Y="<<y;
			}

			//estraggo z
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " � in posizione 22
			if (found2 != std::string::npos) { //questa condizione � sempre verificata
				estratta = linecoord.substr(22, found2 - 22); //substr(inizio,nCaratteri)
				//converto da string a double
				stringstream s(estratta);
				s >> z;
				//cout << endl << "Z=" << z;
			}
			insert_coordinata(frame, joint, x, y, z);
		}

	}

	i.close();
	popola_sequenzaangolo();
    popola_framedaanalizzare();

}


void Persona::insert_frame(int _numeroframe){
    sequenzaframe.insert(pair<int,Frame> (_numeroframe,Frame(_numeroframe)));
}

void Persona::insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z){
    map<int,Frame>::iterator iter;
    iter=sequenzaframe.find(_numeroframe);
    if(iter!=sequenzaframe.end()){
        iter->second.insert_coordinata(_numerojoint, _x, _y, _z);
    }else{
        cout<<"ERRORE: frame non trovato, coordinata non inserita"<<endl;
    }
}


void Persona::completa_angoli(int _numeroframe){
    map<int,Frame>::iterator iter;
    iter=sequenzaframe.find(_numeroframe);
    
    if(iter!=sequenzaframe.end()){
        iter->second.completa_angoli();
    }else{
        cout<<"ERRORE: frame non trovato, angoli non creati"<<endl;
    }
}

void Persona::popola_sequenzaangolo(){
    map<int,Frame>::iterator iter;
    map<int,Angolo> tmp;
    map<int,Angolo>::iterator itertmp;
    for (iter=sequenzaframe.begin(); iter!=sequenzaframe.end(); ++iter) {
        tmp=iter->second.get_angolijoint();
        for(itertmp=tmp.begin();itertmp!=tmp.end();++itertmp){
            sequenzaangolo[itertmp->first].push_back(itertmp->second);
        }
    }
}

void Persona:: popola_max_min_angolo_zenit(int _angolo, float _tolleranzazenit){
 map<int,list<Angolo>>::iterator iter;
 iter= sequenzaangolo.find(_angolo);
    if(iter!=sequenzaangolo.end()){
		int size = iter->second.size();
		float mediazenit = medialista(iter->second).first;
		float devst = devst_lista(iter->second).first;
		int max_confronto = (int)500/ devst;
		int how=0;//massimo->how=1 //minimo->how=2 //cresce o descresce->how=0
	//	bool exit_value = 0; //massimo o minimo->bool=1 //niente->bool=0

		
        list<Angolo>::iterator iterl;
		list<Angolo>::iterator a_iterl;//after
		list<Angolo>::iterator b_iterl;//before
		list<Angolo>::iterator na_iterl;
		list<Angolo>::iterator nb_iterl;

		//inserisco il primo elemento con max/min relativo??
		int contl=1,cont1=1,cont2;
        for(iterl=++(iter->second.begin());iterl!=--(iter->second.end());iterl++){
		//	cont1 = contl;
			cont2 = 2;//parte da 2 poich� entro nel while solo nel momento in cui vado ad analizzare le due celle successive o pi�
			//inizializzo iteratori
			how = 0;
			int dove = 0;//sinistra->1 //destra->2 //entrambi->3 //valore iniziale->0 //altro->4
			a_iterl = iterl;
			a_iterl++;
			b_iterl = iterl;
			b_iterl--;
			na_iterl = iterl;
			nb_iterl = iterl;
			Angolo a = *(a_iterl);
			Angolo b = *(b_iterl);
			Angolo na = *(na_iterl);
			Angolo nb = *(nb_iterl);
			Angolo n = *(iterl);


			if (na.get_zenit() > a.get_zenit() && nb.get_zenit() > b.get_zenit()) {
				how = 1;
			//	iterl++;
			//	contl++;
			}
			if (na.get_zenit() < a.get_zenit() && nb.get_zenit() < b.get_zenit()) {
				how = 2;
			//	iterl++;
			//	contl++;
			}
				
			while (cont2 < (size - cont1) && (cont1-cont2>=0) && cont2 <= max_confronto && how!=0){
				a_iterl++;	b_iterl--;	
				//na_iterl++;	nb_iterl--;
				a = *(a_iterl);	b = *(b_iterl);	na = *(na_iterl);	nb = *(nb_iterl);

				if ((how==1 && na.get_zenit() > a.get_zenit() && nb.get_zenit() > b.get_zenit())||((how == 2 && na.get_zenit() < a.get_zenit() && nb.get_zenit() < b.get_zenit()))) {
				//	iterl++;
				//	contl++;
					cont2++;
				}
				else {
					how = 0;
				}
			/*	if (how == 1) {//massimo ipotetico
					if (na.get_zenit() > a.get_zenit() && nb.get_zenit() > b.get_zenit() && (dove == 0 || dove == 3)){
						dove = 3;
					}
					else {
						if (na.get_zenit() > a.get_zenit() && (dove == 0 || dove == 2 || dove == 3)) {
							dove = 2;
							//puoi guardare a destra
						}
						else {
							if (nb.get_zenit() > b.get_zenit() && (dove == 0 || dove == 1 || dove == 3)) {
								dove = 1;
								//puoi guardare a sinistra
							}
							else {
								dove = 4;
							}
						}
					}
				}
				if (how == 2) {//minimo ipotetico
					if (na.get_zenit() < a.get_zenit() && nb.get_zenit() < b.get_zenit() && (dove == 0 || dove == 3)) {
						dove = 3;
					}
					else {
						if (na.get_zenit() < a.get_zenit() && (dove == 0 || dove == 2 || dove == 3)) {
							dove = 2;
							//puoi guardare a destra
						}
						else {
							if (nb.get_zenit() < b.get_zenit() && (dove == 0 || dove == 1 || dove == 3)) {
								dove = 1;
								//puoi guardare a sinistra
							}
							else {
								dove = 4;
							}
						}
					}
				}


				if (dove != 4) {
					cont2++;
				}
				else{
					how = 0;
				}
			*/	
			}
			if (how != 0) {
				max_min_angoli_zenit[_angolo].insert(n.get_numeroframe());
			}

			cont1++;
			//contl++;
		
        }
    }else{
        cout<<"Angolo "<<_angolo<<" non trovato."<<endl;
    }
}

void Persona::popola_max_min_angolo_azimut(int _angolo, float _tolleranzaazimut){
	map<int, list<Angolo>>::iterator iter;
	iter = sequenzaangolo.find(_angolo);
	if (iter != sequenzaangolo.end()) {
		int size = iter->second.size();
		float mediaazimut = medialista(iter->second).second;
		float devst = devst_lista(iter->second).second;
		int max_confronto = (int)1000 / devst;
		int how = 0;//massimo->how=1 //minimo->how=2 //cresce o descresce->how=0
	//	bool exit_value = 0; //massimo o minimo->bool=1 //niente->bool=0


		list<Angolo>::iterator iterl;
		list<Angolo>::iterator a_iterl;//after
		list<Angolo>::iterator b_iterl;//before
		list<Angolo>::iterator na_iterl;
		list<Angolo>::iterator nb_iterl;

		//inserisco il primo elemento con max/min relativo??
		int contl = 1, cont1 = 1, cont2;
		for (iterl = ++(iter->second.begin()); iterl != --(iter->second.end()); iterl++) {
			//	cont1 = contl;
			cont2 = 2;//parte da 2 poich� entro nel while solo nel momento in cui vado ad analizzare le due celle successive o pi�
			//inizializzo iteratori
			how = 0;
			int dove = 0;//sinistra->1 //destra->2 //entrambi->3 //valore iniziale->0 //altro->4
			a_iterl = iterl;
			a_iterl++;
			b_iterl = iterl;
			b_iterl--;
			na_iterl = iterl;
			nb_iterl = iterl;
			Angolo a = *(a_iterl);
			Angolo b = *(b_iterl);
			Angolo na = *(na_iterl);
			Angolo nb = *(nb_iterl);
			Angolo n = *(iterl);


			if (na.get_azimut() > a.get_azimut() && nb.get_azimut() > b.get_azimut()) {
				how = 1;
				//	iterl++;
				//	contl++;
			}
			if (na.get_azimut() < a.get_azimut() && nb.get_azimut() < b.get_azimut()) {
				how = 2;
				//	iterl++;
				//	contl++;
			}

			while (cont2 < (size - cont1) && (cont1 - cont2 > 0) && cont2 <= max_confronto && how != 0) {
				a_iterl++;	b_iterl--;
				//na_iterl++;	nb_iterl--;
				a = *(a_iterl);	b = *(b_iterl);	na = *(na_iterl);	nb = *(nb_iterl);

				if ((how == 1 && na.get_zenit() > a.get_zenit() && nb.get_zenit() > b.get_zenit()) || ((how == 2 && na.get_zenit() < a.get_zenit() && nb.get_zenit() < b.get_zenit()))) {
					//	iterl++;
					//	contl++;
					cont2++;
				}
				else {
					how = 0;
				}

			}
			if (how != 0) {
				max_min_angoli_azimut[_angolo].insert(n.get_numeroframe());
			}

			cont1++;
			//contl++;

		}
	}
	else {
		cout << "Angolo " << _angolo << " non trovato." << endl;
	}
}

void Persona::popola_framedaanalizzare(){
    popola_max_min_angolo_azimut(3,0.05);
    popola_max_min_angolo_azimut(2,0.05);
    popola_max_min_angolo_azimut(1,0.05);
    popola_max_min_angolo_azimut(8,0.05);
    popola_max_min_angolo_azimut(6,0.05);
    popola_max_min_angolo_azimut(11,0.05);
    popola_max_min_angolo_azimut(12,0.05);
    popola_max_min_angolo_azimut(9,0.05);
    
    popola_max_min_angolo_zenit(3,0.05);
    popola_max_min_angolo_zenit(2,0.12);
    popola_max_min_angolo_zenit(1,0.05);
    popola_max_min_angolo_zenit(8,0.05);
    popola_max_min_angolo_zenit(6,0.05);
    popola_max_min_angolo_zenit(11,0.05);
    popola_max_min_angolo_zenit(12,0.05);
    popola_max_min_angolo_zenit(9,0.05);
    
    
    map<int,set<int>>::iterator iter1;
    set<int>::iterator iter2;
    
    for(iter1=max_min_angoli_azimut.begin();iter1!=max_min_angoli_azimut.end();++iter1){
        for(iter2=iter1->second.begin();iter2!=iter1->second.end();++iter2){
            framedaanalizzare.insert((*iter2));
        }
    }
    
    for(iter1=max_min_angoli_zenit.begin();iter1!=max_min_angoli_zenit.end();++iter1){
        for(iter2=iter1->second.begin();iter2!=iter1->second.end();++iter2){
            framedaanalizzare.insert((*iter2));
        }
    }
}

void Persona::stampa_max(int n) {
	map<int, set<int>>::const_iterator iter1;
	set<int>::const_iterator iter1a;
	map<int, set<int>>::const_iterator iter2;
	set<int>::const_iterator iter2a;
	cout << "JOINT " << n << ": massimi e minimi" << endl;
	cout << "zenit-> ";
	iter1 = max_min_angoli_zenit.find(n);
	if (iter1 != max_min_angoli_zenit.end()) {
		for (iter1a = iter1->second.begin(); iter1a != iter1->second.end(); ++iter1a) {
			cout << (*iter1a) << "; ";
		}
	}
	cout << endl;

	cout << "azimut-> ";
	iter2 = max_min_angoli_azimut.find(n);
	if (iter2 != max_min_angoli_azimut.end()) {
		for (iter2a = iter2->second.begin(); iter2a != iter2->second.end(); ++iter2a) {
			cout << (*iter2a) << "; ";
		}
	}
	cout << endl;
}

void Persona::stampa_angoli(int n) {
	map<int, list<Angolo>>::const_iterator miter;
	list<Angolo>::const_iterator liter;
	miter = sequenzaangolo.find(n);
	cout <<"JOINT "<< miter->first << ": "<< endl;
	cout << "frame; azimut; zenit" << endl;
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		cout << (*liter)<<endl;
	}
}
void Persona::stampafile_angoli(int n,string name) {
	map<int, list<Angolo>>::const_iterator miter;
	list<Angolo>::const_iterator liter;
	ofstream file;
	file.open(name+".txt", ios::out);
	miter = sequenzaangolo.find(n);
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		file << (*liter) << endl;
	}
}

ostream& operator <<(ostream& os, const Persona& p) {
	map<int, set<int>>::const_iterator iter1;
	set<int>::const_iterator iter1a;
	map<int, set<int>>::const_iterator iter2;
	set<int>::const_iterator iter2a;


	cout << "Massimi/minimi Azimut joint 1: " << endl;
	iter2 = p.max_min_angoli_azimut.find(1);
	if (iter2 != p.max_min_angoli_azimut.end()) {
		for (iter2a = iter2->second.begin(); iter2a != iter2->second.end(); ++iter2a) {
			cout << (*iter2a) << "; ";
		}
	}
	return os;
}

void Persona::test_persona(int n) {
		float azimut=0, zenit=0;
		map<int, list<Angolo>>::iterator iter;
	/*	iter = sequenzaangolo.find(n);
		if (iter != sequenzaangolo.end()) {
			azimut = (devst_lista(iter->second)).second;
			zenit = (devst_lista(iter->second)).first;
		}
		cout << endl << endl << "AZIMUT->" << azimut;
		cout << endl << endl << "ZENIT->" << zenit;*/
		cout<<ERi_zenit(2, 50, 10);
		cout << ERi_zenit(2, 500, 10);
	}

void Persona::kamazenit_lista(int _angolo, int period, int fast_period, int slow_period) {//kaufman's adaptive moving average
	map<int, list<Angolo>>::iterator iter;
	list<Angolo>::iterator iterl;
	list<Angolo>::iterator iterl_b;
	int cont = 0;
	iter = sequenzaangolo.find(_angolo);
	if (iter != sequenzaangolo.end()) {
		for (iterl = (iter->second).begin(); iterl != (iter->second).end(); iterl++) {
			if (cont > period) {
				iterl_b = iterl;
				iterl_b--;
				Angolo a = *(iterl);
				Angolo b = *(iterl_b);
				double fast = (2 / ((double)(fast_period + 1)));
				double slow = (2 /( (double)(slow_period + 1)));
				double sc = ERi_zenit(_angolo, cont, period)*(fast - slow) + slow;
				double res = (b.get_zenit() + sc * (a.get_zenit() - b.get_zenit()));
				(*iterl).set_zenit(res);
			//	cout << sc << endl;
			}	
			cont++;
		}
	}
	else {
		cout << "Angolo " << _angolo << " non trovato." << endl;
	} 
}

void Persona::kamaazimut_lista(int _angolo, int period, int fast_period, int slow_period) {//kaufman's adaptive moving average
	map<int, list<Angolo>>::iterator iter;
	list<Angolo>::iterator iterl;
	list<Angolo>::iterator iterl_b;
	int cont = 0;
	iter = sequenzaangolo.find(_angolo);
	if (iter != sequenzaangolo.end()) {
		for (iterl = (iter->second).begin(); iterl != (iter->second).end(); iterl++) {
			if (cont > period) {
				iterl_b = iterl;
				iterl_b--;
				Angolo a = *(iterl);
				Angolo b = *(iterl_b);
				double fast = (2 / ((double)(fast_period + 1)));
				double slow = (2 / ((double)(slow_period + 1)));
				double sc = ERi_azimut(_angolo, cont, period)*(fast - slow) + slow;
				double res = (b.get_azimut() + sc * (a.get_azimut() - b.get_azimut()));
				(*iterl).set_azimut(res);
				//	cout << sc << endl;
			}
			cont++;
		}
	}
	else {
		cout << "Angolo " << _angolo << " non trovato." << endl;
	}
}

long double Persona::ERi_zenit(int _angolo,int i,int n) {
	
	map<int, list<Angolo>>::const_iterator iter;
	list<Angolo>::const_iterator iterl;
	list<Angolo>::const_iterator iterl_1;
	list<Angolo>::const_iterator iterl_n;
	int cont = 0;
	long double den=0.0, num;
	iter = sequenzaangolo.find(_angolo);
	if (iter != sequenzaangolo.end()) {
		cont = 0;
		//faccio avanzare ad i-n il mio iteratore // fxcodebase.com/wiki/index.php/Kaufman's_Adaptive_Moving_Average_(KAMA)
		
		for (iterl = (iter->second).begin(); (iterl != (iter->second).end() && cont < (i-n)); iterl++) {
			cont++;
		}
		Angolo ang_n = *(iterl);
		Angolo ang = *(iterl);
		iterl_1 = iterl;
		iterl_1--;
		Angolo ang_1 = *(iterl_1);
		
		while (iterl != (iter->second).end() && cont<(i)) {
			ang = *(iterl);
			iterl_1 = iterl;
			iterl_1--;
			ang_1 = *(iterl_1);
			den = fabs(ang.get_zenit() - ang_1.get_zenit()) + den;
			iterl++;
			cont++;
		}
		num = fabs(ang.get_zenit() - ang_n.get_zenit());
		return num / den;
	}
	else {
		cout << "Angolo " << _angolo << " non trovato." << endl;
		return 0;
	}
}

long double Persona::ERi_azimut(int _angolo, int i, int n) {

	map<int, list<Angolo>>::const_iterator iter;
	list<Angolo>::const_iterator iterl;
	list<Angolo>::const_iterator iterl_1;
	list<Angolo>::const_iterator iterl_n;
	int cont = 0;
	long double den = 0.0, num;
	iter = sequenzaangolo.find(_angolo);
	if (iter != sequenzaangolo.end()) {
		cont = 0;
		//faccio avanzare ad i-n il mio iteratore // fxcodebase.com/wiki/index.php/Kaufman's_Adaptive_Moving_Average_(KAMA)

		for (iterl = (iter->second).begin(); (iterl != (iter->second).end() && cont < (i - n)); iterl++) {
			cont++;
		}
		Angolo ang_n = *(iterl);
		Angolo ang = *(iterl);
		iterl_1 = iterl;
		iterl_1--;
		Angolo ang_1 = *(iterl_1);

		while (iterl != (iter->second).end() && cont < (i)) {
			ang = *(iterl);
			iterl_1 = iterl;
			iterl_1--;
			ang_1 = *(iterl_1);
			den = fabs(ang.get_azimut() - ang_1.get_azimut()) + den;
			iterl++;
			cont++;
		}
		num = fabs(ang.get_azimut() - ang_n.get_azimut());
		return num / den;
	}
	else {
		cout << "Angolo " << _angolo << " non trovato." << endl;
		return 0;
	}
}