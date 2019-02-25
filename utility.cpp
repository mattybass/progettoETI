#include "utility.h"



double angolo_azimut(Coordinata& c1, Coordinata& c2, Coordinata& c3){
    double angoloc1c2;
    double angoloc2c3;
    
 // ANOGOLO C1 C2
    if(c1.get_x()-c2.get_x()!=0){
        double m_c1c2= ((c1.get_y()-c2.get_y())/(c1.get_x()-c2.get_x()));
        angoloc1c2= atan(m_c1c2)*180/PI;
        
        if(angoloc1c2>0){
            if(c1.get_y()<c2.get_y()){
                angoloc1c2+=180;
            }
        }else{
            if(c1.get_y()<c2.get_y()){
                angoloc1c2=360+angoloc1c2;
            }else{
                angoloc1c2+=180;
            }
        }
        
    }else{
        
        if(c1.get_y()>c2.get_y()){
            angoloc1c2= 90.0;
        }else{
            angoloc1c2= 270.0;
        }
    }
//ANGOLO C2 C3
    
    if((c3.get_x()-c2.get_x())!=0){
        double m_c2c3= ((c3.get_y()-c2.get_y())/(c3.get_x()-c2.get_x()));
        angoloc2c3= atan(m_c2c3)*180/PI;
        
        if(angoloc2c3>0){
            if(c3.get_y()<c2.get_y()){
                angoloc2c3+=180;
            }
        }else{
            if(c3.get_y()<c2.get_y()){
                angoloc2c3=360+angoloc2c3;
            }else{
                angoloc2c3+=180;
            }
        }
        
    }else{
        if(c3.get_y()>c2.get_y()){
            angoloc2c3= 90.0;
        }else{
            angoloc2c3= 270.0;
        }
    }
//DIFFERENZA TRA I DUE ANGOLI = AZIMUT
    double azimut=0;
    
    
    azimut=angoloc2c3-angoloc1c2;
    if(azimut<0){
        azimut=360+azimut;
    }
    
    return azimut;
}



