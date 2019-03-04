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

			found2 = line.find(str_r, 5); //il primo " è in posizione 4
			if (found2 != std::string::npos) { //questa condizione è sempre verificata
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

			found2 = line.find(str_r, 13); //il primo " è in posizione 12
			if (found2 != std::string::npos) { //questa condizione è sempre verificata
				estratta = line.substr(19, found2 - 19); //substr(inizio,nCaratteri)
				//converto da string a int
				stringstream s3(estratta);
				s3 >> joint;
				//cout << "JOINT " << joint << endl;
			}

			//estraggo x
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " è in posizione 4
			if (found2 != std::string::npos) { //questa condizione è sempre verificata
				estratta = linecoord.substr(22, found2 - 22); //substr(inizio,nCaratteri)
				//converto da string a double
				stringstream s(estratta);
				s >> x;
				//cout << endl << "X="<<x;
			}
			//estraggo y
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " è in posizione 4
			if (found2 != std::string::npos) { //questa condizione è sempre verificata
				estratta = linecoord.substr(22, found2 - 22); //substr(inizio,nCaratteri)
				//converto da string a double
				stringstream s(estratta);
				s >> y;
				//cout << endl << "Y="<<y;
			}

			//estraggo z
			getline(i, linecoord);
			found2 = linecoord.find(str_r, 23); //il primo " è in posizione 22
			if (found2 != std::string::npos) { //questa condizione è sempre verificata
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
    map<string,Angolo> tmp;
    map<string,Angolo>::iterator itertmp;
    for (iter=sequenzaframe.begin(); iter!=sequenzaframe.end(); ++iter) {
        tmp=iter->second.get_angolijoint();
        for(itertmp=tmp.begin();itertmp!=tmp.end();++itertmp){
            sequenzaangolo[itertmp->first].push_back(itertmp->second);
        }
    }
}

void Persona:: popola_max_min_angolo_zenit(string _angolo, float _toleranzazenit){
    list<double> listavariazionizenit;
    map<string,list<Angolo>>::iterator iter;
    iter= sequenzaangolo.find(_angolo);
    if(iter!=sequenzaangolo.end()){
        list<Angolo>::iterator iterl;
        for(iterl=iter->second.begin();iterl!=iter->second.end();++iterl){
            listavariazionizenit.push_back(iterl->get_zenit());
        }
        float mediazenit=medialista(iter->second).first;
        
        
        
        
        
        
    }else{
        cout<<"Angolo "<<_angolo<<" non trovato."<<endl;
        
        
    }
}

ostream& operator <<(ostream& os, const Persona& p) {
	map<int, Frame>::const_iterator citer;
	for (citer = p.sequenzaframe.begin(); citer != p.sequenzaframe.end(); citer++) {
		os << citer->second;
	}
	return os;
}
