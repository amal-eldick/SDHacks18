#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QString>
#include "customer.h"

class DataBaseManager
{
private:
    QSqlDatabase db;                              // The database object

public:
    DataBaseManager();
    bool openDB();                                // Adds the database and opens the connection
    void closeDB();                               // Closes connection and removes the database
    QSqlDatabase returnDB();                      // Returns database object value
    void addMedication(QString Medname, QNumeric Dosage, QString frequency, QNumeric time);
    void deleteMedication(QString Medname);
    void updateMedication(QString oldName, QString newName, QNumeric newDosage, QString newFrequency, 
                                       QNumeric newTime);

QString returnNameFromSearch(QString Medname);
};

#endif // DATABASEMANAGER_H
