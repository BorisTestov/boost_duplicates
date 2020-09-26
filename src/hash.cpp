#include "hash.h"

#include <iostream>

std::vector<unsigned int> CRC32Hasher::Hash(const char* buffer, const unsigned int& buffer_size)
{
    boost::crc_32_type result;
    result.process_bytes(buffer, buffer_size);
    auto checksum = result.checksum();
    return { checksum };
}

std::vector<unsigned int> MD5Hasher::Hash(const char* buffer, const unsigned int& buffer_size)
{
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(buffer, buffer_size);
    hash.get_digest(digest);
    return { std::begin(digest), std::end(digest) };
}

std::vector<unsigned int> SHA1Hasher::Hash(const char* buffer, const unsigned int& buffer_size)
{
    boost::uuids::detail::sha1 hash;
    boost::uuids::detail::sha1::digest_type digest;
    hash.process_bytes(buffer, buffer_size);
    hash.get_digest(digest);
    return { std::begin(digest), std::end(digest) };
}