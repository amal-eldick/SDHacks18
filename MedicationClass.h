//
//  MedicationClass.h
//  Pill App Classes
//
//  Created by Andrew Masters on 10/13/18.
//  Copyright © 2018 Andrew Masters. All rights reserved.
//

#ifndef MedicationClass_h
#define MedicationClass_h

#include <iostream>
#include <string>

using namespace std;

class Medication {
public:
    
    //Constructor
    Medication(const string &name, const float &dose, const int &freq,
               const int &time, const string &day){
        setMedName(name);
        setDosage(dose);
        setTime(time);
        setDay(day);
    }

    //mutators
    void setMedName(string name);
    void setDosage(float dose);
    void setMon(bool monday); 
    void setTues(bool tuesday); 
    void setWed(bool wednesday); 
    void setThurs(bool thursday); 
    void setFri(bool friday); 
    void setSat(bool saturday); 
    void setSun(bool sunday); 
    void setMorning(bool morning); 
    void setAfternoon(bool afternoon);
    void setEvening(bool evening); 
    
    //accessors
    string getMedName() {return medName;}
    float getDosage() {return dosage;}
    bool getMon() {return monday;} 
    bool getTues() {return tuesday;}
    bool getWed() {return wednesday;}
    bool getThurs(){return thursday;}
    bool getFri() {return friday;}
    bool getSat() {return saturday;}
    bool getSun() {return sunday;}
    bool getMorning() {return morning;}
    bool getAfternoon() {return afternoon;}
    bool getEvening() {return evening;}



private:
    string medName;
    float dosage;
    bool sunday = 0;
    bool monday = 0;
    bool tuesday = 0;
    bool wednesday = 0;
    bool thursday = 0;
    bool friday = 0;
    bool saturday = 0;
    bool morning = 0; 
    bool afternoon = 0; 
    bool evening = 0; 
};

////// SETTERS //////

void Medication::setMedName(string name) {
    if(name != "")
        medName = name;
    else
        medName = "John Doe";
    
}

void Medication::setDosage(float dose){
    if(dose != 0.0)
        dosage = dose;
    else
        dosage = 0.0;
}

void Medication::setMon(bool monday){
    if(monday == 0)
        monday = 1;
    else
        monday = 0;
}

void Medication::setTues(bool tuesday){
    if(tuesday == 0)
        tuesday = 1;
    else
        tuesday = 0;
}

void Medication::setWed(bool wednesday){
    if(wednesday == 0)
        wednesday = 1;
    else
        wednesday = 0;
}

void Medication::setThurs(bool thursday){
    if(thursday == 0)
        thursday = 1;
    else
        thursday = 0;
}

void Medication::setFri(bool friday){
    if(friday == 0)
        friday = 1;
    else
        friday = 0;
}

void Medication::setSat(bool saturday){
    if(saturday == 0)
        saturday = 1;
    else
        saturday = 0;
}

void Medication::setSun(bool sunday){
    if(sunday == 0)
        sunday = 1;
    else
        sunday = 0;
}

void Medication::setMorning(bool morning){
    if(morning == 0)
        morning = 1;
    else
        morning = 0;
}

void Medication::setEvening(bool evening){
    if(evening == 0)
        evening = 1;
    else
        evening = 0;
}

void Medication::setAfternoon(bool afternoon){
    if(afternoon == 0)
        afternoon = 1;
    else
        afternoon = 0;
}





#endif /* MedicationClass_h */
