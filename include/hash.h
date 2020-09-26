#pragma once

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <vector>

class IHash
{
public:
    virtual std::vector<unsigned int> Hash(const char* buffer) = 0;
};

/**
 * @brief Класс для хеширования методом SHA1
 */
class SHA1Hasher : public IHash
{
public:
    /**
     * @brief Хеширование методо SHA1
     * @param buffer - буффер для хеширования
     * @return std::vector<unsigned int> - результат хеширования
     */
    std::vector<unsigned int> Hash(const char* buffer) override;
};

/**
 * @brief Класс для хеширования методом CRC32
 */
class CRC32Hasher : public IHash
{
public:
    /**
     * @brief Хеширование методо CRC32
     * @param buffer - буффер для хеширования
     * @return std::vector<unsigned int> - результат хеширования
     */
    std::vector<unsigned int> Hash(const char* buffer) override;
};

/**
 * @brief Класс для хеширования методом MD5
 */
class MD5Hasher : public IHash
{
public:
    /**
     * @brief Хеширование методо MD5
     * @param buffer - буффер для хеширования
     * @return std::vector<unsigned int> - результат хеширования
     */
    std::vector<unsigned int> Hash(const char* buffer) override;
};
