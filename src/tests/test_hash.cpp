#include "test_hash.h"

#include <iostream>

enum HashMethods
{
    MD5,
    SHA1,
    CRC32
};

Q_DECLARE_METATYPE(HashMethods)
Q_DECLARE_METATYPE(std::vector<unsigned int>)
Q_DECLARE_METATYPE(std::string)

void TestHash::Test_data()
{
    QTest::addColumn<std::string>("input_string");
    QTest::addColumn<HashMethods>("hash_method");
    QTest::addColumn<std::vector<unsigned int>>("expected_hash");
    QTest::addRow("MD5")
        << std::string("this is a test string") << HashMethods::MD5 << std::vector<unsigned int> { 1387687496, 1689824628, 4197058369, 4085850654 };
    QTest::addRow("SHA1")
        << std::string("this is a test string") << HashMethods::SHA1 << std::vector<unsigned int> { 2587320183, 2880526228, 2416715401, 2166490151, 1031109787 };
    QTest::addRow("CRC32")
        << std::string("this is a test string") << HashMethods::CRC32 << std::vector<unsigned int> { 4236695221 };
}

void TestHash::Test()
{
    QFETCH(std::string, input_string);
    QFETCH(HashMethods, hash_method);
    std::vector<unsigned int> hash;
    switch (hash_method)
    {
        case HashMethods::MD5:
        {
            MD5Hasher hasher;
            hash = hasher.Hash(input_string.c_str());
            break;
        }
        case HashMethods::SHA1:
        {
            SHA1Hasher hasher;
            hash = hasher.Hash(input_string.c_str());
            break;
        }
        case HashMethods::CRC32:
        {
            CRC32Hasher hasher;
            hash = hasher.Hash(input_string.c_str());
            break;
        }
        default:
        {
            QFAIL("UNKNOWN HASH METHOD");
        }
    }
    QTEST(hash, "expected_hash");
}