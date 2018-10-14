#include "databasemanager.h"

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
    QSqlQuery query2;
    query2.prepare("INSERT INTO Medication (Medname, Dosage, frequency, time) VALUES (:Medname, :Dosage, :frequency, :time)");
    query2.bindValue(":Medname", Medname);
    query2.bindValue(":Dosage", Dosage);
    query2.bindValue(":frequency", frequency);
    query2.bindValue(":time", time);
    query2.exec();
    closeDB();
}

void DataBaseManager::deleteCustomer(QString name)
{
    openDB();
    QSqlQuery query2;
    query2.prepare("DELETE FROM Customers WHERE name = :name");
    query2.bindValue(":name", name);
    query2.exec();
    closeDB();
}

void DataBaseManager::updateCustomer(QString oldName, QString newname, QString newdate,
                    QString newId, QString newmembership)
{
    deleteCustomer(oldName);

    addCustomer(newname, newId, newmembership, newdate);
}

void DataBaseManager::addProduct(QString name, double price, int quantity)
{
    openDB();
    QSqlQuery query2;
    query2.prepare("INSERT INTO Products (name, price, quantity) VALUES (:name, :price, :quantity)");
    query2.bindValue(":name", name);
    query2.bindValue(":price", price);
    query2.bindValue(":quantity", quantity);
    query2.exec();
    closeDB();
}

void DataBaseManager::deleteProduct(QString name)
{
    openDB();
    QSqlQuery query2;
    query2.prepare("DELETE FROM Products WHERE name = :name");
    query2.bindValue(":name", name);
    query2.exec();
    closeDB();
}

void DataBaseManager::updateProduct(QString oldName, QString newname,
                    QString newId, double newPrice, int newQty)
{
    deleteProduct(oldName);

    addProduct(newname, newPrice, newQty);
}

int DataBaseManager::testUser(QString user, QString pass)
{
    openDB();
    QSqlQuery query2;
    query2.prepare("SELECT user, pass FROM UserInfo WHERE user = :use AND pass = :passwd");
    query2.bindValue(":use", user);
    query2.bindValue(":passwd", pass);
    query2.exec();

    int userType = -1;

    while (query2.next())
    {
        if (query2.value(0) == user)
        {
           //is admin
          userType = 1;
        }
        else if (query2.value(1) == pass)
        {
           //is manager
           userType = 2;
        }
    }

    closeDB();

    return userType;
}

void DataBaseManager::addTransaction(QString date, QString customerId, QString itemName, double itemPrice, int itemQty)
{
    openDB();
    QSqlQuery query2;
    query2.prepare("INSERT INTO Purchases ('Date', 'Item_Name', 'Customer_ID', 'Price', 'Quantity', 'Unique_Transaction') VALUES (:date, :itemName, :customerId, :itemPrice, :itemQty, :uT)");
    query2.bindValue(":date", date);
    query2.bindValue(":itemName", itemName);
    query2.bindValue(":customerId", customerId);
    query2.bindValue(":itemPrice", itemPrice);
    query2.bindValue(":itemQty", itemQty);
    query2.bindValue(":uT", (date + customerId + itemName));
    query2.exec();
    closeDB();

    qDebug() << date;
    qDebug() << itemName;
    qDebug() << customerId;
    qDebug() << itemPrice;
    qDebug() << itemQty;
    qDebug() << (date + customerId + itemName);
}

void DataBaseManager::deleteTransaction(QString date, QString customerId, QString itemName, double itemPrice, int itemQty)
{
    openDB();
    QSqlQuery query2;
    query2.prepare("DELETE FROM Purchases WHERE 'Customer_ID' = :customerId AND 'Price' = :itemPrice AND 'Quantity' = :itemQty");
    query2.bindValue(":date", date);
    query2.bindValue(":itemName", itemName);
    query2.bindValue(":customerId", customerId);
    query2.bindValue(":itemPrice", itemPrice);
    query2.bindValue(":itemQty", itemQty);
    query2.exec();
    closeDB();
}

double DataBaseManager::calcRebate(QString execId)  // A database must already be open already to use this function
{
    double rebate = 0.0;

    QSqlQuery query2;
    query2.prepare("SELECT Quantity, Price FROM Purchases WHERE Customer_ID LIKE '%" + execId + "%'");
    query2.exec();

    while(query2.next())
    {
        rebate += (query2.value(0).toDouble() * query2.value(1).toDouble());
        qDebug() << "Quantity: " <<  query2.value(0).toDouble() << "Price: " << query2.value(1).toDouble() << "Rebate: " << rebate;
    }

    return (rebate * 0.04);
}

QString DataBaseManager::returnNameFromId(QString customerId) // A database must already be open already to use this function
{
    QString name;
    QSqlQuery query3;

    query3.prepare("SELECT name FROM Customers WHERE id LIKE '%" + customerId + "%'");
    query3.exec();

    query3.next();
    name = query3.value(0).toString();

    qDebug() << "NAME: " << name;

    return name;
}

QString DataBaseManager::returnMembershipFromId(QString customerId) // A database must already be open already to use this function
{
    //NOT WORKING PROPERLY: "QSqlQuery::value: not positioned on a valid record"
    QString membership;
    QSqlQuery query3;

    query3.prepare("SELECT membership FROM Customers WHERE id LIKE '%" + customerId + "%'");
    query3.exec();

    query3.next();

    membership = query3.value(0).toString();

    qDebug() << "MEM: " << membership;

    return membership;
}

void DataBaseManager::createInvRepTempTable(QString aDate) // A database must already be open already to use this function
{
    double revenue = 0.0;
    double numExec = 0;
    double numReg = 0;

    QSqlQuery query;
    query.exec("CREATE TEMPORARY TABLE InvRep (itemName TEXT, quantity INTEGER, customerName TEXT, customerId TEXT, membershipType TEXT, revenue NUMERIC, count INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE)");

    QSqlQuery query2;
    query2.prepare("SELECT Item_Name, Quantity, Customer_ID, Price FROM Purchases WHERE Date LIKE '%" + aDate + "%'");
    query2.exec();

    while (query2.next())
    {
        query.prepare("INSERT INTO InvRep (itemName, quantity, customerName, customerId, membershipType, revenue) VALUES (:itemName, :quantity, :customerName, :customerId, :membershipType, :revenue)");
        query.bindValue(":itemName", query2.value(0));
        query.bindValue(":quantity", query2.value(1));
        query.bindValue(":customerName", returnNameFromId(query2.value(2).toString()));
        query.bindValue(":customerId", query2.value(2));
        query.bindValue(":membershipType", returnMembershipFromId(query2.value(2).toString()));
        query.bindValue(":revenue", (query2.value(3).toDouble() * query2.value(1).toDouble()));
        query.exec();

        if (returnMembershipFromId(query2.value(2).toString()) == "Executive")
        {
            numExec += 1;
        }
        else if (returnMembershipFromId(query2.value(2).toString()) == "Regular")
        {
            numReg += 1;
        }

        qDebug() << "Exec: " << numExec << " Reg: " << numReg;

        revenue += (query2.value(1).toDouble() * query2.value(3).toDouble());
    }

    query.prepare("INSERT INTO InvRep (membershipType, revenue) VALUES (:membershipType, :revenue)");
    query.bindValue(":membershipType", "EXECUTIVE: ");
    query.bindValue(":revenue", numExec);
    query.exec();
    query.prepare("INSERT INTO InvRep (membershipType, revenue) VALUES (:membershipType, :revenue)");
    query.bindValue(":membershipType", "REGULAR: ");
    query.bindValue(":revenue", numReg);
    query.exec();
    query.prepare("INSERT INTO InvRep (membershipType, revenue) VALUES (:membershipType, :revenue)");
    query.bindValue(":membershipType", "TOTAL REVENUE: ");
    query.bindValue(":revenue", revenue);
    query.exec();
}

void DataBaseManager::createExecRebateTempTable()
{
    QChar cc;
    QSqlQuery query;
    query.exec("create temporary table ExecRebate (id integer primary key, name varchar(40), rebate numeric)");

    QSqlQuery query2;
    query2.prepare("SELECT name, id FROM Customers WHERE membership LIKE '%Executive%'");
    query2.exec();

    while(query2.next())
    {
        qDebug() << endl << query2.value(1) << endl;
        query.prepare("INSERT INTO ExecRebate (id, name, rebate) VALUES (:id, :name, :rebate)");
        query.bindValue(":id", query2.value(1));
        query.bindValue(":name", query2.value(0));
        query.bindValue(":rebate", calcRebate(query2.value(1).toString()));
        query.exec();
    }
}

void DataBaseManager::addUserinfo(QString username, QString password, int userType)
{
    openDB();
    QSqlQuery query2;
    query2.prepare("INSERT INTO UserInfo ('user', 'pass', 'type') VALUES (:user, :pass, :type)");
    query2.bindValue(":user", username);
    query2.bindValue(":pass", password);
    query2.bindValue(":type", userType);
    query2.exec();
    closeDB();

}


void DataBaseManager::deleteUserInfo(QString username)
{
    if (username == "Admin")
            qDebug() << "Can't delete that, try changing my password instead!";

    else
    {
        openDB();
        QSqlQuery query2;
        query2.prepare("DELETE FROM UserInfo WHERE user = :user");
        query2.bindValue(":user", username);
        query2.exec();
        closeDB();
    }
}

void DataBaseManager::changeUserInfo(QString oldName, QString newname, QString newpass, int newType)
{
    deleteUserInfo(oldName);
    addUserinfo(newname, newpass, newType);
}
