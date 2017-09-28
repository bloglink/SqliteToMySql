/*******************************************************************************
 * Copyright [2017]   <青岛艾普智能仪器有限公司>
 * All rights reserved.
 *
 * version:     0.1
 * author:      zhaonanlin
 * brief:       二代服务器数据迁移到MySql
*******************************************************************************/
#include "sqlitetomysql.h"

SqliteToMySql::SqliteToMySql()
{
}

void SqliteToMySql::connect()
{
    server = QSqlDatabase::addDatabase("QMYSQL3", "mysql");
    server.setHostName("192.168.1.55");
    server.setUserName("root");
    server.setPassword("87973318");
    server.setDatabaseName("aip-server");
    if (!server.open())
        qDebug() << "open fail" << server.lastError();

    sqlite = QSqlDatabase::addDatabase("QSQLITE", "sqlite");
    sqlite.setDatabaseName("aip-server.db");
    if (!sqlite.open())
        qDebug() << "open fail" << sqlite.lastError();
}

void SqliteToMySql::aip_device_create()
{
    QSqlQuery query(server);
    QString cmd;

    query.exec("drop table aip_device");

    cmd = "create table if not exists aip_device(";
    cmd += "devUuid bigint primary key,";           // 设备编号
    cmd += "devAddr text,";                         // 设备地址
    cmd += "devNumb text,";                         // 出厂编号
    cmd += "devType text,";                         // 设备型号
    cmd += "revNumb text,";                         // 评审编号
    cmd += "devDate text,";                         // 出厂日期
    cmd += "devCust text)";                         // 客户名称
    query.exec(cmd);
    qDebug() << "aip_device_create ok";
}

void SqliteToMySql::aip_device_insert()
{
    QSqlQuery erp(sqlite);
    QSqlQuery query(server);

    erp.exec("select NO,MAC from NetRecord");
    while (erp.next()) {
        QString numb = erp.value(0).toString();
        QString addr = erp.value(1).toString();
        if (devAddrs.contains(addr))
            continue;
        if (numb == "测试号")
            continue;
        double uuid = snow.getId();
        devNumbs.append(numb);
        devAddrs.append(addr);
        devUuids.append(uuid);
        query.prepare("insert into aip_device values(?,?,?,?,?,?,?)");
        query.bindValue(0, uuid);
        query.bindValue(1, addr);
        query.bindValue(2, numb);
        query.bindValue(3, "--");
        query.bindValue(4, "--");
        query.bindValue(5, "--");
        query.bindValue(6, "--");
        query.exec();
    }
    qDebug() << "aip_device_insert ok";
}

void SqliteToMySql::aip_record_create()
{
    QSqlQuery query(server);
    QString cmd;

    query.exec("drop table aip_record");

    cmd = "create table if not exists aip_record(";
    cmd += "recUuid bigint primary key,";           // 记录编号
    cmd += "devUuid bigint,";                       // 设备编号
    cmd += "devAddr text,";                         // 设备地址
    cmd += "devNumb text,";                         // 出厂编号
    cmd += "netPort text,";                         // 网络端口
    cmd += "netAddr text,";                         // 网络地址
    cmd += "recTime text,";                         // 记录时间
    cmd += "netStat text,";                         // 设备状态
    cmd += "verNumb text)";                         // 软件版本
    query.exec(cmd);
    qDebug() << "aip_record_create ok";
}

void SqliteToMySql::aip_record_insert()
{
    QSqlQuery erp(sqlite);
    QSqlQuery query(server);

    erp.exec("select IP,NO,MAC,TIME,STATE,VERSION from NetRecord");

    while (erp.next()) {
        QString netAddr = erp.value(0).toString();
        QString devNumb = erp.value(1).toString();
        QString devAddr = erp.value(2).toString();
        QString recTime = erp.value(3).toString();
        QString netStat = erp.value(4).toString();
        QString verNumb = erp.value(5).toString();
        if (devNumb == "测试号")
            continue;
        double recUuid = snow.getId();
        int index = devAddrs.indexOf(devAddr);
        double devUuid = devUuids.at(index);

        query.prepare("insert into aip_record values(?,?,?,?,?,?,?,?,?)");
        query.bindValue(0, recUuid);
        query.bindValue(1, devUuid);
        query.bindValue(2, devAddr);
        query.bindValue(3, devNumb);
        query.bindValue(4, "--");
        query.bindValue(5, netAddr);
        query.bindValue(6, recTime);
        query.bindValue(7, netStat);
        query.bindValue(8, verNumb);
        if (!query.exec())
            qDebug() << "aip_record_insert fail" << server.lastError();
    }
    qDebug() << "aip_record_insert ok";
}

void SqliteToMySql::aip_online_create()
{
    QSqlQuery query(server);
    QString cmd;

    query.exec("drop table aip_online");

    cmd = "create table if not exists aip_online(";
    cmd += "recUuid bigint primary key,";           // 记录编号
    cmd += "devUuid bigint,";                       // 设备编号
    cmd += "devAddr text,";                         // 设备地址
    cmd += "devNumb text,";                         // 出厂编号
    cmd += "netPort text,";                         // 网络端口
    cmd += "netAddr text,";                         // 网络地址
    cmd += "recTime text,";                         // 记录时间
    cmd += "netStat text,";                         // 设备状态
    cmd += "verNumb text)";                         // 软件版本
    query.exec(cmd);
    qDebug() << "aip_online_create ok";
}

void SqliteToMySql::aip_repair_create()
{
    QSqlQuery query(server);
    QString cmd;

    query.exec("drop table aip_repair");

    cmd = "create table if not exists aip_repair(";
    cmd += "recUuid bigint primary key,";           // 记录编号
    cmd += "devUuid bigint,";                       // 设备编号
    cmd += "fixName text,";                         // 记录人
    cmd += "fixDesc text,";                         // 情况描述
    cmd += "fixText text,";                         // 维修描述
    cmd += "fixDate text,";                         // 维修日期
    cmd += "contact text,";                         // 联系人
    cmd += "telNumb text)";                         // 联系电话
    query.exec(cmd);
    qDebug() << "aip_repair_create ok";
}

void SqliteToMySql::aip_repair_insert()
{
    QSqlQuery erp(sqlite);
    QSqlQuery query(server);

    erp.exec("select MAC,TIME,BACKUP from NetRecord");

    while (erp.next()) {
        QString devAddr = erp.value(0).toString();
        QString fixDate = erp.value(1).toString();
        QString fixText = erp.value(2).toString();
        if (fixText.isEmpty())
            continue;
        double recUuid = snow.getId();
        int index = devAddrs.indexOf(devAddr);
        double devUuid = devUuids.at(index);

        query.prepare("insert into aip_repair values(?,?,?,?,?,?,?,?)");
        query.bindValue(0, recUuid);
        query.bindValue(1, devUuid);
        query.bindValue(2, "--");
        query.bindValue(3, "--");
        query.bindValue(4, fixText);
        query.bindValue(5, fixDate);
        query.bindValue(6, "--");
        query.bindValue(7, "--");
        if (!query.exec())
            qDebug() << "aip_repair_insert fail" << server.lastError();
    }
    qDebug() << "aip_repair_insert ok";
}
