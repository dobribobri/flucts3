#ifndef DBASE_H
#define DBASE_H

#include <QSqlDatabase>
#include <qsqlquery.h>
#include <QSqlError>
#include <QString>
#include <QDebug>

class DBase {
    private:
        QSqlDatabase db;

    public:
        bool okOpen = false;

  std::string T, Po, P, Pa, U, DD, Ff, ff10, ff3, N, WW, W1, W2, Tn, Tx, Cl, Nh, H, Cm, Ch, VV, Td, RRR, tR, E, Tg, E_p, sss;
  double T_c = 15.;

        void connect() {
            if (okOpen == false) {
                db = QSqlDatabase::addDatabase("QPSQL");
                db.setHostName("localhost");
                db.setPort(5432);
                db.setDatabaseName("flucts3");
                db.setUserName("postgres");
                db.setPassword("4815162342");
                okOpen = db.open();
                if (!okOpen) qDebug() << "not open" << db.lastError();
            }
            return;
        }

/*
 * flucts3=# CREATE TABLE weather (Datetime char(20), T char(10), Po char(10), P char(10), Pa char(10),
 * U char(10), DD char(128), Ff char(10), ff10 char(10), ff3 char(10), N char(128), WW char(256),
 * W1 char(256), W2 char(256), Tn char(10), Tx char(10), Cl char(256), Nh char(128), H char(128),
 * Cm char(256), Ch char(256), VV char(10), Td char(10), RRR char(128), tR char(10), E char(256),
 * Tg char(10), E_p char(256), sss char(256));
 * */

        void datetime_select_all(std::string _datetime_key) {
            qDebug() << "Trying to make SELECT";
            if (okOpen)
            {
                std::string zapros = "SELECT * FROM weather WHERE datetime = '" + _datetime_key + "'";
                //QSqlQuery query("SELECT * FROM weather WHERE datetime = '01.06.2018 03:00'");
                QSqlQuery query(zapros.c_str());
                while (query.next())
                {
                    qWarning() << query.value(0).toString();
                    T = query.value(1).toString().toStdString();
                    Po = query.value(2).toString().toStdString();
                    P = query.value(3).toString().toStdString();
                    Pa = query.value(4).toString().toStdString();
                    U = query.value(5).toString().toStdString();
                    DD = query.value(6).toString().toStdString();
                    Ff = query.value(7).toString().toStdString();
                    ff10 = query.value(8).toString().toStdString();
                    ff3 = query.value(9).toString().toStdString();
                    N = query.value(10).toString().toStdString();
                    WW = query.value(11).toString().toStdString();
                    W1 = query.value(12).toString().toStdString();
                    W2 = query.value(13).toString().toStdString();
                    Tn = query.value(14).toString().toStdString();
                    Tx = query.value(15).toString().toStdString();
                    Cl = query.value(16).toString().toStdString();
                    Nh = query.value(17).toString().toStdString();
                    H = query.value(18).toString().toStdString();
                    Cm = query.value(19).toString().toStdString();
                    Ch = query.value(20).toString().toStdString();
                    VV = query.value(21).toString().toStdString();
                    Td = query.value(22).toString().toStdString();
                    RRR = query.value(23).toString().toStdString();
                    tR = query.value(24).toString().toStdString();
                    E = query.value(25).toString().toStdString();
                    Tg = query.value(26).toString().toStdString();
                    E_p = query.value(27).toString().toStdString();
                    sss = query.value(28).toString().toStdString();
                }

                qDebug() << query.lastError().text();
            } else {
                qDebug() << "Database isn't open! First run 'DBase::connect()'";
            }
            return;
        }
};

#endif // DBASE_H
