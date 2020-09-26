#include "test_version.h"

void TestVersion::Test()
{
    QCOMPARE((int) version().find("0.0."), 0);
}
