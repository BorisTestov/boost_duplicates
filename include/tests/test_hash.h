#pragma once

#include "hash.h"

#include <QtTest/QtTest>

class TestHash : public QObject
{
    Q_OBJECT
private slots:
    void TestMD5_data();
    void TestMD5();
    void TestCRC32_data();
    void TestCRC32();
    void TestSHA1_data();
    void TestSHA1();
};