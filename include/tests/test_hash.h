#pragma once

#include "hash.h"

#include <QtTest/QtTest>

class TestHash : public QObject
{
    Q_OBJECT
private slots:
    void Test_data();
    void Test();
};