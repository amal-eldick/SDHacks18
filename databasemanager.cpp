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
    QString name;

    Medication meds; 
    
    query.prepare("SELECT Medname FROM Medication WHERE id LIKE '%" + Medname + "%'");
    query.exec();
    
    while (query.next());
    {
        query.bindValue(":Dosage", meds.setDosage); 
        query.bindValue(":Morning", meds.setMorning); 
        query.bindValue(":Afternoon", meds.setAfternoon); 
        query.bindVAlue("Evening", meds.setEvening); 
        query.exec(); 
    }
    name = query.value(0).toString();
    
    closeDB();
    
    return meds;
}

QString DataBaseManager::returnTimeFromSearch(QNumeric time)
{
    openDB();
    QNumeric time;
    
    query.prepare("SELECT Medname FROM Medication WHERE id LIKE '%" + time + "%'");
    query.exec();
    
    query.next();
    name = query.value(0).toNumeric();
    
    closeDB();
    
    return time;
}
