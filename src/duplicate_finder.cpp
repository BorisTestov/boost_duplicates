#include "duplicate_finder.h"

DuplicateFinder::DuplicateFinder(const std::vector<std::string>& include_dirs,
                                 const std::vector<std::string>& exclude_dirs,
                                 const std::vector<std::string>& filemasks,
                                 size_t block_size,
                                 size_t scan_depth,
                                 uintmax_t min_file_size,
                                 const std::string& hasher) :
    include_dirs_(TrySetDirs(include_dirs)),
    exclude_dirs_(TrySetDirs(exclude_dirs)),
    filemasks_(SetFileMasks(filemasks)),
    block_size_(block_size),
    scan_depth_(scan_depth),
    min_file_size_(min_file_size),
    hasher_(TrySetHasher(hasher)) {}

std::unordered_map<std::string, std::vector<std::string>> DuplicateFinder::Find()
{
    return {};
}

std::vector<boost::filesystem::path> DuplicateFinder::TrySetDirs(const std::vector<std::string>& dirs)
{
    std::vector<boost::filesystem::path> directories;
    for (const std::string& dir : dirs)
    {
        auto path = boost::filesystem::path(dir);
        if (not boost::filesystem::exists(path))
        {
            throw std::runtime_error("Directory doesn't exists: " + dir);
        }
        if (not boost::filesystem::is_directory(path))
        {
            throw std::runtime_error("Path isn't a directory: " + dir);
        }
        directories.push_back(path);
    }
    return directories;
}

std::shared_ptr<IHash> DuplicateFinder::TrySetHasher(const std::string& hasher)
{
    if (hasher == "md5")
    {
        return std::make_unique<MD5Hasher>();
    }
    if (hasher == "sha1")
    {
        return std::make_unique<SHA1Hasher>();
    }
    if (hasher == "crc32")
    {
        return std::make_unique<CRC32Hasher>();
    }
    throw std::runtime_error("Hasher type doesn't recognized: " + hasher);
}

std::vector<boost::regex> DuplicateFinder::SetFileMasks(const std::vector<std::string>& filemasks)
{
    std::vector<boost::regex> resulted_masks;
    for (const std::string& mask : filemasks)
    {
        resulted_masks.push_back(boost::regex(mask));
    }
    return resulted_masks;
}
