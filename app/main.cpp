/*******************************************************************************
 * Copyright [2017]   <青岛艾普智能仪器有限公司>
 * All rights reserved.
 *
 * version:     0.1
 * author:      zhaonanlin
 * brief:       二代服务器数据迁移到MySql
*******************************************************************************/
#include <QCoreApplication>
#include "sqlitetomysql.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    SqliteToMySql sql;
    sql.connect();
//    sql.aip_device_create();
//    sql.aip_device_insert();
//    sql.aip_record_create();
//    sql.aip_record_insert();
//    sql.aip_online_create();
//    sql.aip_repair_create();
//    sql.aip_repair_insert();

    return 0;
}

