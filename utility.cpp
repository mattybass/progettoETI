#include "utility.h"
#include "angolo.h"


double angolo_XY(Coordinata &c1,Coordinata &c2){
	double angolo;
	if(c1.get_x()-c2.get_x()!=0){
        double m= ((c1.get_y()-c2.get_y())/(c1.get_x()-c2.get_x()));
        angolo= atan(m)*180/PI;
        
        if(angolo>0){
            if(c1.get_y()<c2.get_y()){
                angolo+=180;
            }
        }
		else{
            if(c1.get_y()<c2.get_y()){
                angolo+=360;
            }
			else{
                angolo+=180;
            }
        }
        
    }else{
        
        if(c1.get_y()>c2.get_y()){
            angolo= 90.0;
        }else{
            angolo= 270.0;
        }
    }
    return angolo;
}

double angolo_XZ(Coordinata &c1,Coordinata &c2){
	double angolo;
	if(c1.get_x()-c2.get_x()!=0){
        double m= ((c1.get_z()-c2.get_z())/(c1.get_x()-c2.get_x()));
        angolo= atan(m)*180/PI;
        
        if(angolo>0){
            if(c1.get_z()<c2.get_z()){
                angolo+=180;
            }
        }
		else{
            if(c1.get_z()<c2.get_z()){
                angolo+=360;
            }
			else{
                angolo+=180;
            }
        }
        
    }else{
        
        if(c1.get_z()>c2.get_z()){
            angolo= 90.0;
        }else{
            angolo= 270.0;
        }
    }
    return angolo;	
}


double angolo_azimut(Coordinata& c1, Coordinata& c2, Coordinata& c3){
    double angoloc1c2=angolo_XY(c1,c2);
    double angoloc2c3=angolo_XY(c2,c3);
    
//DIFFERENZA TRA I DUE ANGOLI = AZIMUT
    double azimut;
      
    azimut=angoloc2c3-angoloc1c2;
    if(azimut<0){
        azimut=360+azimut;
    }
    
    return azimut;
}

double angolo_zenit(Coordinata& c1, Coordinata& c2, Coordinata& c3){
    double angoloc1c2=angolo_XZ(c1,c2);
    double angoloc2c3=angolo_XZ(c2,c3);
    
//DIFFERENZA TRA I DUE ANGOLI = AZIMUT
    double zenit=angoloc2c3-angoloc1c2;
    if(zenit<0){
        zenit+=360;
    }
    
    return zenit;
}

float medialista(list<int> _lista){
    float media =0;
    list<int>::iterator iter;
    int index=0;
    int somma=0;
    
    for (iter=_lista.begin(); iter!=_lista.end(); ++iter) {
        ++index;
        somma=somma+(*iter);
    }
    media=(float)somma/index;

    return media;
}


pair<float,float> medialista(list<Angolo> _lista){
    float mediazenit =0;
    float mediaazimut=0;
    list<Angolo>::iterator iter;
    int index=0;
    float sommazenit=0;
    float sommaazimut=0;
    
    for (iter=_lista.begin(); iter!=_lista.end(); ++iter) {
        ++index;
        sommazenit=sommazenit + iter->get_zenit();
        sommaazimut=sommaazimut + iter->get_azimut();
    }
    
    mediazenit=(float)sommazenit/index;
    mediaazimut=(float)sommaazimut/index;
    
    return pair<float, float> (mediazenit,mediaazimut);
    
}
