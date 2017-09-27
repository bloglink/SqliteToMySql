QT += core sql
QT -= gui

TARGET = SqliteToMySql
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    app/lqsnowflake.cpp \
    app/main.cpp \
    app/sqlitetomysql.cpp

HEADERS += \
    app/lqsnowflake.h \
    app/sqlitetomysql.h

