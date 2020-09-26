#pragma once

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <vector>

class IHash
{
public:
    virtual std::vector<unsigned int> Hash(const char* buffer, const unsigned int& buffer_size) = 0;
};

class SHA1Hasher : public IHash
{
public:
    virtual std::vector<unsigned int> Hash(const char* buffer, const unsigned int& buffer_size);
};

class CRC32Hasher : public IHash
{
public:
    virtual std::vector<unsigned int> Hash(const char* buffer, const unsigned int& buffer_size);
};

class MD5Hasher : public IHash
{
public:
    virtual std::vector<unsigned int> Hash(const char* buffer, const unsigned int& buffer_size);
};
