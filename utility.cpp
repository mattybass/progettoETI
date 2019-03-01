#include "utility.h"
#include "angolo.h"
#define FINESTRARICERCAMASSIMI=2

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



int ricercamassimo(map<string,list<Angolo>>){
    
    
    
    
    
    
}
