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
    void addCustomer(QString name, QString id, QString membership, QString date);
    void deleteCustomer(QString name);
    void updateCustomer(QString oldName, QString newname, QString newdate,
                        QString newId, QString newmembership);
    void addProduct(QString name, double price, int quantity);
    void deleteProduct(QString name);
    void updateProduct(QString oldName, QString newname,
                        QString newiId, double newPrice, int newQty);
    //login capability
    int testUser(QString user, QString pass);
    void addTransaction(QString date, QString customerId, QString itemName, double itemPrice, int itemQty);
    void deleteTransaction(QString date, QString customerId, QString itemName, double itemPrice, int itemQty);
    double calcRebate(QString execId);
    QString returnNameFromId(QString customerId);
    QString returnMembershipFromId(QString customerId);
    void createInvRepTempTable(QString aDate);
    void createExecRebateTempTable();

    //capability to add/remove/change users in the program below this line
    void addUserinfo(QString username, QString password, int userType);
    void deleteUserInfo(QString username);
    void changeUserInfo(QString oldName, QString newname, QString newpass, int newType);
};

#endif // DATABASEMANAGER_H
