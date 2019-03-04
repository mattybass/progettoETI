#include "persona.h"

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

/*void Persona::popola_max_min_angolo(string _angolo, float _tolleranzaazimut, float _toleranzazenit){
    list<double> listavariazioniazimut;
    list<double> listavariazionizenit;
    map<string,list<Angolo>>::iterator iter;
    iter= sequenzaangolo.find(_angolo);
    if(iter!=sequenzaangolo.end()){
        list<Angolo>::iterator iterl;
        for(iterl=iter->second.begin();iterl!=iter->second.end();++iterl){
            listavariazioniazimut.push_back(iterl->get_azimut());
            listavariazionizenit.push_back(iterl->get_zenit());
        }
        float mediaazimut=medialista(iter->second).second;
        float mediazenit=medialista(iter->second).first;
        list<double>::iterator iterd;
        iterd=listavariazionizenit.begin();
        iterd++;
        
        while (iterd!=listavariazionizenit.end()){
            double a= *(iterd--);
            double b= *(iterd);
            double c= *(iterd++);
            
            if(a<b && b>c && b>(mediazenit+_toleranzazenit*mediazenit) ){
                
            }
        }
    
    }else{
        cout<<"Angolo "<<_angolo<<" non trovato."<<endl;
        
        
    }
} */

void Persona::popola_max_min_angolo(string _angolo, float _tolleranzaazimut, float _toleranzazenit){
    




}
