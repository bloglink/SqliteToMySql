/*******************************************************************************
 * Copyright [2017]   <青岛艾普智能仪器有限公司>
 * All rights reserved.
 *
 * version:     0.1
 * author:      zhaonanlin
 * brief:       二代服务器数据迁移到MySql
*******************************************************************************/
#ifndef SQLITETOMYSQL_H
#define SQLITETOMYSQL_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QElapsedTimer>

#include "lqsnowflake.h"

class SqliteToMySql {
public:
    SqliteToMySql();
    void connect();
    void aip_device_create();
    void aip_device_insert();
    void aip_record_create();
    void aip_record_insert();
    void aip_online_create();
    void aip_repair_create();
    void aip_repair_insert();
private:
    QSqlDatabase server;
    QSqlDatabase sqlite;

    LQSnowflake snow;

    QStringList devAddrs;
    QStringList devNumbs;
    QList<double> devUuids;
};

#endif // SQLITETOMYSQL_H
