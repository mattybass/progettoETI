#include "persona.h"

Persona::Persona(int _framesec, string nome_file, string percorso_file) {
	framepersec = _framesec;
	ifstream i(percorso_file + "/" + nome_file);

string line, linecoord, estratta;

string str_r = "\"";
size_t found, found2;
int frame = 0;
int joint;
int exit_value = 0;
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
    insert_coordinata(frame, joint, x, z, y);
	}
}
    i.close();
    popola_sequenzaangolo();
    popola_sequenzacoordinata();
    completa_pulisci();
    sequenzaAngoloELAB = sequenzaAngolo;
}

void Persona::popola_sequenzacoordinata(){
    map<int,Frame>::const_iterator iterF;
    map<int,Coordinata>::const_iterator iterC;
    Coordinata c;
    map<int,Coordinata> mappa;
    for(iterF=sequenzaFrame.begin(); iterF!=sequenzaFrame.end();++iterF){
        mappa=iterF->second.get_coordinatejoit();
        for(iterC=mappa.begin();iterC!=mappa.end();++iterC){
            sequenzaCoordinata[iterC->first].push_back(iterC->second);
        }
    }
}



double Persona::get_angoloMedia_zenit(int _angolo, int n_frame) {
	map<int, list<Angolo> >::iterator iter;
	list<Angolo>::iterator liter;
	list<Angolo>::iterator r_liter;
	list<Angolo>::iterator l_liter;
	int i=0, cont = 1,size;
	double media=0.0;
	iter = sequenzaAngolo.find(_angolo);
	if (iter != sequenzaAngolo.end()) { //ho trovato l'angolo
		size = iter->second.size();
		for (liter = iter->second.begin(); liter != iter->second.end(); liter++) {
			i++;
			if ((*liter).get_numeroframe() == n_frame) {
				cont = 1;
				l_liter = liter;
				r_liter = liter;
				media = (*liter).get_zenit();
				while ((i + cont < size) && (i - cont > 0) && (cont < 4)) {
					l_liter--;
					r_liter++;
					media = media + (*l_liter).get_zenit() + (*r_liter).get_zenit();
					cont++;
				}
				return media = media / ((int)(2 * (cont-1) + 1));
			}
		}	
	}
	return 0;
}

double Persona::get_angoloMedia_azimut(int _angolo, int n_frame) {
	map<int, list<Angolo> >::iterator iter;
	list<Angolo>::iterator liter;
	list<Angolo>::iterator r_liter;
	list<Angolo>::iterator l_liter;
	int i = 0, size,cont;
	double media;
	iter = sequenzaAngolo.find(_angolo);
	if (iter != sequenzaAngolo.end()) { //ho trovato l'angolo
		size = iter->second.size();
		for (liter = iter->second.begin(); liter != iter->second.end(); liter++) {
			i++;
			if ((*liter).get_numeroframe() == n_frame) {
				cont = 1;
				l_liter = liter;
				r_liter = liter;
				media = (*liter).get_azimut();
				while ((i + cont < size) && (i - cont > 0) && (cont < 4)) {
					l_liter--;
					r_liter++;
					media = media + (*l_liter).get_azimut() + (*r_liter).get_azimut();
					cont++;
				}
				return media = media / ((int)(2 * (cont-1) + 1));
			}
		}
	}
	return 0;
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
		int n = 0;
		//PROCEDO A CALCOLARE MAX E MIN
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
				--cont;
			}
			if (max_o_min != 0) {
				n = (*liter).get_numeroframe();
				Angolo a(get_angoloMedia_azimut(_angolo, n), get_angoloMedia_zenit(_angolo, n), n,tipo_angolo);
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
		int n = 0;
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
				n = (*liter).get_numeroframe();
				Angolo a(get_angoloMedia_azimut(_angolo, n), get_angoloMedia_zenit(_angolo, n), n, tipo_angolo);
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
	map<int, list<Angolo> >::iterator miter;
	list<Angolo>::const_iterator liter;
	miter = valori_maxmin_zenit.find(n);
	if (miter != valori_maxmin_zenit.end()) {
		cout << "JOINT " << miter->first << ": " << endl;
		cout << "frame; azimut; zenitMAX" << endl;
		for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
			cout << (*liter) << endl;
		}
	}

	cout << endl;
	miter = valori_maxmin_azimut.find(n);
	if (miter != valori_maxmin_azimut.end()) {
		cout << "JOINT " << miter->first << ": " << endl;
		cout << "frame; azimutMAX; zenit" << endl;
		for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
			cout << (*liter) << endl;
		}
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

void Persona::stampaFile_maxmin(int n, string name, string percorso_file) {
	map<int, list<Angolo> >::const_iterator miter;
	list<Angolo>::const_iterator liter;
	ofstream file;
	string l = percorso_file + "/" + name + "ZENIT.txt";
	file.open(l.c_str(), ios::out);
	miter = valori_maxmin_zenit.find(n);
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		file << (*liter) << endl;
	}

	ofstream file1;
	string l1 = percorso_file + "/" + name + "AZIMUT.txt";
	file1.open(l1.c_str(), ios::out);
	miter = valori_maxmin_azimut.find(n);
	for (liter = miter->second.begin(); liter != miter->second.end(); liter++) {
		file << (*liter) << endl;
	}
}

void Persona::stampaFile_coordinate(int n, string name, string percorso_file) {
	map<int,list<Coordinata> >::const_iterator miter;
    list<Coordinata>::const_iterator liter;
	ofstream file;
	string l = percorso_file + "/" + name + ".txt";
	file.open(l.c_str(), ios::out);
    miter=sequenzaCoordinata.find(n);
    if(miter!=sequenzaCoordinata.end()){
        for(liter=miter->second.begin();liter!=miter->second.end();++liter){
            file<< liter->get_x() <<" "<<liter->get_y()<<" "<<liter->get_z()<<endl;
        }
    }
}

void Persona::mediamobile_angolo(int _angolo, int _finestra) {  
	map<int, list < Angolo> >::iterator iter;					
	list<Angolo>::iterator liter;
	list<Angolo>::iterator liter2;
	list<Angolo>::iterator liter3;
	list<Angolo>::iterator liter4;
	double sum_zenit;
	double sum_azimut;
	iter = sequenzaAngoloELAB.find(_angolo);
	if (iter != sequenzaAngoloELAB.end()) { //ho trovato l'angolo
		liter = iter->second.begin();
		int cont;
		int i;
		int j;
		while (liter != iter->second.end()){
			int sizemezzi = _finestra / 2;
			liter3 = liter;
			i = 0;
			liter4 = iter->second.end();
			--liter4;
			while (i < sizemezzi && liter3!=liter4){
				++liter3; //liter3 punta all'elemento che devo aggiornare
				++i;
			}
			sum_azimut = 0;
			sum_zenit = 0;
			liter2 = liter;
			j = 0;
			cont = 0;
			while (j < _finestra&&liter2 != iter->second.end()) {
				sum_zenit = sum_zenit + (*liter2).get_zenit();
				sum_azimut = sum_azimut + (*liter2).get_azimut();
				++liter2;
				++cont;
				++j;
			}
			(*liter3).set_azimut(sum_azimut / cont);
			(*liter3).set_zenit(sum_zenit / cont);
			++liter;
		}
	}
	else
		cout << "Angolo non trovato!" << endl;
}

void Persona::maxminClean_angolo(int _angolo, double _tolleranzazenit, double _tolleranzaazimut) {
	map<int, list<Angolo>>::iterator miter;
    map<int, list<Angolo>>::iterator miter2;
	list<Angolo>::iterator iter2;
    miter2=sequenzaAngoloELAB.find(_angolo);
    double mean_zenit = media_zenit(miter2->second);
	miter = valori_maxmin_zenit.find(_angolo);
	list<Angolo>::iterator inizio;
	list<Angolo>::iterator fine;
	list<Angolo> temp;
	//PULISCO ZENIT
	if (miter != valori_maxmin_zenit.end()){ //ho trovato l angolo
		inizio = (miter->second).begin();
        fine = (miter->second).end();
        fine--;
		Angolo iniziale = *inizio;
		Angolo finale = *fine;
		int i = (*inizio).get_numeroframe();
        int j = (*fine).get_numeroframe();

		for (iter2 = inizio; iter2 != fine; ++iter2) {
			if ((*iter2).get_numeroframe() > (i + 15) && (*iter2).get_numeroframe() < (j - 15) &&(((iter2->get_zenit())>mean_zenit+_tolleranzazenit)||((iter2->get_zenit())<mean_zenit-_tolleranzazenit)))
				temp.push_back(*iter2);
		}

		temp.push_front(iniziale);
		temp.push_back(finale);
		valori_maxmin_zenit.erase(miter);
		valori_maxmin_zenit[_angolo] = temp;
	}
	temp.clear();


	miter = valori_maxmin_azimut.find(_angolo);
	//PULISCO AZIMUT
	if (miter != valori_maxmin_azimut.end()) { //ho trovato l angolo
		list<Angolo>::iterator iter2;
        double mean_azimut = media_azimut(miter2->second);
		list<Angolo>::iterator inizio;
        list<Angolo>::iterator fine;
		inizio = (miter->second).begin();
        fine = (miter->second).end();
        fine--;
		Angolo iniziale = *inizio;
		Angolo finale = *fine;
		int i = (*inizio).get_numeroframe();
        int j = (*fine).get_numeroframe();
		for (iter2 = inizio; iter2 != fine; ++iter2) {
			if ((*iter2).get_numeroframe() > (i + 15)&&(*iter2).get_numeroframe()<(j-15)&&(((iter2->get_azimut())>mean_azimut+_tolleranzaazimut)||((iter2->get_azimut())<mean_azimut-_tolleranzaazimut)))
				temp.push_back(*iter2);
		}
		temp.push_front(iniziale);
		temp.push_back(finale);
		valori_maxmin_azimut.erase(miter);
		valori_maxmin_azimut[_angolo] = temp;
	}

}

void Persona::processa_angolo(int _angolo) {
	pulisci_errori_sequenzaangolo(_angolo);
	mediamobile_angolo(_angolo, 30);
	mediamobile_angolo(_angolo, 30);
	maxminFind_angolo(_angolo, 50);
	maxminClean_angolo(_angolo,5,15);
}

void Persona::pulisci_errori_sequenzaangolo(int _angolo){
    map<int,list<Angolo>>::iterator iter;
    list<Angolo>::iterator iter2;
    list<Angolo>::iterator iter3;
    map<int,Frame>::iterator iterF;
	int frame = 0;  
	double dif;
	iter=sequenzaAngoloELAB.find(_angolo);
    if(iter!=sequenzaAngoloELAB.end()){
        for(iter2=iter->second.begin();iter2!=iter->second.end();++iter2){
            iter3=iter2;
            iter3++;
            frame=0;
            if(iter3!=iter->second.end()){
                dif=fabs((iter2->get_azimut())-(iter3->get_azimut()));
                if(dif>100){
                iter3->set_azimut(iter2->get_azimut());
                    frame=iter3->get_numeroframe();
                    iterF=sequenzaFrame.find(frame);
                    if(iterF!=sequenzaFrame.end()){
                        iterF->second.set_angolo_azimut(_angolo,(iter2->get_azimut()));
                    }
                }
                dif=fabs((iter2->get_zenit())-(iter3->get_zenit()));
                if(dif>100){
                iter3->set_zenit(iter2->get_zenit());
                    frame=iter3->get_numeroframe();
                    iterF=sequenzaFrame.find(frame);
                    if(iterF!=sequenzaFrame.end()){
                        iterF->second.set_angolo_zenit(_angolo,(iter2->get_zenit()));
                    }
                }
            }
        }
    }
}

void Persona::completa_pulisci(){
    pulisci_errori_sequenzaangolo(3);
    pulisci_errori_sequenzaangolo(2);
    pulisci_errori_sequenzaangolo(1);
    pulisci_errori_sequenzaangolo(5);
    pulisci_errori_sequenzaangolo(6);
    pulisci_errori_sequenzaangolo(8);
    pulisci_errori_sequenzaangolo(11);
    pulisci_errori_sequenzaangolo(9);
    pulisci_errori_sequenzaangolo(12);
}

list<Angolo> Persona::get_valorimaxmin_zenit(int _angolo)const {
	map<int, list<Angolo>>::const_iterator iter;
	iter = valori_maxmin_zenit.find(_angolo);
	return iter->second;
}

list<Angolo> Persona::get_valorimaxmin_azimut(int _angolo)const {
	map<int, list<Angolo>>::const_iterator iter;
	iter = valori_maxmin_azimut.find(_angolo);
	return iter->second;
}

int Persona::get_numeroMaxMin_zenit(int _angolo){
	map<int, list<Angolo>>::const_iterator iterM;
	iterM = valori_maxmin_zenit.find(_angolo);
	return (iterM->second).size();
}

int Persona::get_numeroMaxMin_azimut(int _angolo){
    map<int, list<Angolo>>::const_iterator iterM;
    iterM=valori_maxmin_azimut.find(_angolo);
	return (iterM->second).size();
}

int Persona::get_numeroFramePerSecondo()const {
	return framepersec;
}

Angolo Persona::return_angolo(int _angolo, int _nframe)const {
	map<int, Frame>::const_iterator iter;
	iter = sequenzaFrame.find(_nframe); //ho il frame che mi interessa!
	return (iter->second).restituisci_angolo(_angolo);
}

void Persona::processa_esercizio(){
	processa_angolo(1);
	processa_angolo(2);
	processa_angolo(3);
	processa_angolo(5);
	processa_angolo(6);
	processa_angolo(8);
	processa_angolo(9);
	processa_angolo(11);
	processa_angolo(12);
}
