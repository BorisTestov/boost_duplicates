#include "test_hash.h"
#include "test_version.h"

int main(int argc, char* argv[])
{
    bool status = true;
    status &= QTest::qExec(new TestVersion(), argc, argv);
    status &= QTest::qExec(new TestHash(), argc, argv);
    return status;
}
