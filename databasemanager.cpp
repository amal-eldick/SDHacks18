#include "databasemanager.h"
#include "MedicationClass.h"

DataBaseManager::DataBaseManager()
{

}

bool DataBaseManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");    // "QSQLITE" Defines the type of database(in this case sqlite version3)
    db.setDatabaseName("/Users/aeldick/Desktop/sdhacks/Medication.db");
    // Links the  the directory to the database file to the database object

    if (!db.open())                                     // Opens a connection to the database and tests for connection failure
    {
        qDebug() << "Failed to connect";
        return false;
    }
    else                                                // Defaults to connection success if did not fail
    {
        qDebug() << "Connected";
        return true;
    }
}

void DataBaseManager::closeDB()
{
    db.close();                                         // Closes a connection to the database
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

QSqlDatabase DataBaseManager::returnDB()
{
    return db;
}

void DataBaseManager::addMedication(QString Medname, QNumeric Dosage, QString frequency, QNumeric time)
{
    openDB();
    QSqlQuery query;
    query.prepare("INSERT INTO Medication (Medname, Dosage, frequency, time) VALUES (:Medname, :Dosage, :frequency, :time)");
    query.bindValue(":Medname", Medname);
    query.bindValue(":Dosage", Dosage);
    query.bindValue(":frequency", frequency);
    query.bindValue(":time", time);
    query.exec();
    closeDB();
}

void DataBaseManager::deleteMedication(QString Medname)
{
    openDB();
    QSqlQuery query;
    query.prepare("DELETE FROM Medication WHERE Medname = :Medname");
    query.bindValue(":Medname", Medname);
    query.exec();
    closeDB();
}

void DataBaseManager::updateMedication(QString oldName, QString newName, QNumeric newDosage, QString newFrequency, 
                                       QNumeric newTime)
{
    deleteMedication(oldName);
    
    addMedication(newName, newDosage, newFrequency, newTime);
}

QString DataBaseManager::returnNameFromSearch(QString Medname)
{
    openDB();
    QSqlQuery query, query1;
    int dosage;
    bool morning, afternoon, evening, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday; 


    Medication meds; 
    
    query.prepare("SELECT Medname FROM Medication WHERE id LIKE '%" + Medname + "%'");
    query.exec();
    

    while (query.next())
    {
        query.bindValue(":Dosage", dosage); 
        query.bindValue(":Morning", morning); 
        query.bindValue(":Afternoon", afternoon); 
        query.bindVAlue("Evening", evening); 
        query.exec(); 
    }

    while(query1.next())
    {
        query1.bindValue(":Sunday", Sunday);
        query1.bindValue(":Monday", Monday); 
        query1.bindValue(":Tuesday", Thursdsay); 
        query1.bindValue(":Wednesday", Wednesday); 
        query1.bindValue(":Thursday", Thursday); 
        query1.bindValue(":Friday", Friday); 
    }


    closeDB();
    
    meds.setDosage(dosage); 
    meds.setMorning(morning); 
    meds.setAfternoon(afternoon); 
    meds.setEvening(evening); 

    meds.setSun(Sunday); 
    meds.setMon(Monday); 
    meds.setTues(Tuesday); 
    meds.setWed(Wednesday); 
    meds.setThurs(Thursday); 
    meds.setFri(Friday); 
    meds.setSat(Saturday); 


    return meds;
}

