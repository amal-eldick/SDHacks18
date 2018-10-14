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
        setFreq(freq);
        setTime(time);
        setDay(day);
    }

    //mutators
    void setMedName(string name);
    void setDosage(float dose);
    void setFreq(int freqency);
    void setTime(int time);
    void setMon(bool monday); 
    void setTues(bool tuesday); 
    void setWed(bool wednesday); 
    void setThurs(bool thursday); 
    void setFri(bool friday); 
    void setSat(bool saturday); 
    void setSun(bool sunday); 
    
    //accessors
    string getMedName() {return medName;}
    float getDosage() {return dosage;}
    int getFreq() {return freq;}
    int getTime() {return time;}
    bool getMon() {return monday;} 
    bool getTues() {return tuesday;}
    bool getWed() {return wednesday;}
    bool getThurs(){return thursday;}
    bool getFri() {return friday;}
    bool getSat() {return saturday;}
    bool getSun() {return sunday}; 

private:
    string medName;
    float dosage;
    int freq;
    int time;
    bool sunday = 0;
    bool monday = 0;
    bool tuesday = 0;
    bool wednesday = 0;
    bool thursday = 0;
    bool friday = 0;
    bool saturday = 0;
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

void Medication::setFreq(int frequency){
    if(frequency > 0)
        freq = frequency;
    else
        freq = 1;
}

void Medication::setTime(int time){
    if(time > 0)
        time = time;
    else
        time = 0;
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





#endif /* MedicationClass_h */
