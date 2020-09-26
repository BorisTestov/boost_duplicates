#include "test_hash.h"

#include <iostream>
Q_DECLARE_METATYPE(std::vector<unsigned int>)
Q_DECLARE_METATYPE(std::string)

void TestHash::TestMD5_data()
{
    QTest::addColumn<std::string>("input_string");
    QTest::addColumn<unsigned int>("buffer_size");
    QTest::addColumn<std::vector<unsigned int>>("expected_hash");

    QTest::addRow("Buffer size 12")
        << std::string("this is a test string") << uint(12) << std::vector<unsigned int> { 877304089, 3431493312, 979825022, 2579097034 };

    QTest::addRow("Buffer size 21")
        << std::string("this is a test string") << uint(21) << std::vector<unsigned int> { 1387687496, 1689824628, 4197058369, 4085850654 };

    QTest::addRow("Buffer size 1")
        << std::string("this is a test string") << uint(1) << std::vector<unsigned int> { 2767149283, 1652618633, 836177393, 2657379691 };
}

void TestHash::TestMD5()
{
    QFETCH(std::string, input_string);
    QFETCH(unsigned int, buffer_size);
    MD5Hasher hasher;
    auto hash = hasher.Hash(input_string.c_str(), buffer_size);
    //    for (auto e : hash)
    //    {
    //        std::cout << e << " ";
    //    }
    QTEST(hash, "expected_hash");
}

void TestHash::TestCRC32_data()
{
    QTest::addColumn<std::string>("input_string");
    QTest::addColumn<unsigned int>("buffer_size");
    QTest::addColumn<std::vector<unsigned int>>("expected_hash");

    QTest::addRow("Buffer size 12")
        << std::string("this is a test string") << uint(12) << std::vector<unsigned int> { 874586011 };

    QTest::addRow("Buffer size 21")
        << std::string("this is a test string") << uint(21) << std::vector<unsigned int> { 4236695221 };

    QTest::addRow("Buffer size 1")
        << std::string("this is a test string") << uint(1) << std::vector<unsigned int> { 2238339752 };
}

void TestHash::TestCRC32()
{
    QFETCH(std::string, input_string);
    QFETCH(unsigned int, buffer_size);
    CRC32Hasher hasher;
    auto hash = hasher.Hash(input_string.c_str(), buffer_size);
    QTEST(hash, "expected_hash");
}

void TestHash::TestSHA1_data()
{
    QTest::addColumn<std::string>("input_string");
    QTest::addColumn<unsigned int>("buffer_size");
    QTest::addColumn<std::vector<unsigned int>>("expected_hash");

    QTest::addRow("Buffer size 12")
        << std::string("this is a test string") << uint(12) << std::vector<unsigned int> { 156626849, 2309717713, 2773603300, 651741541, 678155972 };

    QTest::addRow("Buffer size 21")
        << std::string("this is a test string") << uint(21) << std::vector<unsigned int> { 2587320183, 2880526228, 2416715401, 2166490151, 1031109787 };

    QTest::addRow("Buffer size 1")
        << std::string("this is a test string") << uint(1) << std::vector<unsigned int> { 2398979835, 2024106577, 1173190457, 3702525048, 1478251381 };
}

void TestHash::TestSHA1()
{
    QFETCH(std::string, input_string);
    QFETCH(unsigned int, buffer_size);
    SHA1Hasher hasher;
    auto hash = hasher.Hash(input_string.c_str(), buffer_size);
    QTEST(hash, "expected_hash");
}