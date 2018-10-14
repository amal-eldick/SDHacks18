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
    void setDay(string day);
    
    //accessors
    string getMedName() {return medName;}
    float getDosage() {return dosage;}
    int getFreq() {return freq;}
    int getTime() {return time;}
    string getDay() {return day;}

private:
    string medName;
    float dosage;
    int freq;
    int time;
    string day;
    bool sunday;
    bool monday;
    bool tuesday;
    bool wednesday;
    bool thursday;
    bool friday;
    bool saturday;
};


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

void Medication::setDay(string day){
    if(day != "")
        day = day;
    else
        day = "Monday";
}



#endif /* MedicationClass_h */
