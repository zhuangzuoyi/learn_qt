#include <QCoreApplication>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"
#include "QDebug"
#include "QDateTime"
#include "QTime"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "./testdatabas.db" );

    if( !db.open() )
    {
      qDebug() << db.lastError();
      qFatal( "Failed to connect." );
    }
    qDebug()<<"connect to database success";
    qDebug()<<db.tables();

    QSqlQuery sql_query;
    QString create_table = "create table if not exists randdata (time varchar(30), rand int)";
    // QString create_table = "create table randdata (time varchar(30), rand int)";
    sql_query.prepare(create_table);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }


    QDateTime dt;
    QString current_dt = dt.currentDateTime().toString("yyyy:MM:dd:hh:mm:ss:zzz");





    qsrand(dt.currentDateTime().toTime_t());
    QString rand = QString::number(qrand());
    QString sql_insert = "insert into randdata values (";
    sql_insert.append("\"").append( current_dt + "\",").append(rand).append(")");
    sql_query.prepare(sql_insert);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted Wang!";
    }

    db.close();
    return a.exec();
}



