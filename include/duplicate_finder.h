#pragma once

#include "hash.h"
#include "hashed_file.h"

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <unordered_set>

/**
 * @brief Class to find duplicate files
 */
class DuplicateFinder
{
public:
    /**
     * @brief Class constructor
     * @param include_dirs - directories to scan
     * @param exclude_dirs - directories to exclude from scanning
     * @param filemasks - Mask of files to be scanned
     * @param block_size - size of hashing block
     * @param scan_depth - depth of scanning
     * @param min_file_size - Min size of scanned file in bytes
     * @param hasher - hasher type. Possible names: crc32/md5/sha1
     */
    DuplicateFinder(const std::vector<std::string>& include_dirs,
                    const std::vector<std::string>& exclude_dirs,
                    const std::vector<std::string>& filemasks,
                    size_t block_size,
                    size_t scan_depth,
                    uintmax_t min_file_size,
                    const std::string& hasher);

    /**
     * @brief Find duplicate files
     * @return - map of duplicates: path to file and vector of duplicates
     */
    std::unordered_map<std::string, std::vector<std::string>> Find();

    /**
     * @brief Set directories from vector of strings
     * @param dirs - vector of paths to directories
     * @throw std::runtime_error if one of directories doesn't exists
     * @return vector of boost paths
     */
    std::vector<boost::filesystem::path> TrySetDirs(const std::vector<std::string>& dirs);

private:
    const std::vector<boost::filesystem::path> include_dirs_;
    const std::vector<boost::filesystem::path> exclude_dirs_;
    const std::vector<boost::regex> filemasks_;
    const size_t block_size_;
    const size_t scan_depth_;
    const unsigned int min_file_size_;
    std::shared_ptr<IHash> hasher_;

    std::vector<HashedFile> files_;
    std::unordered_set<std::string> scanned_file_paths_;

    /**
     * @brief Set hasher type for scanning
     * @param hasher - string of hasher name. Possible names: crc32/md5/sha1
     * @throw std::runtime_error if hasher name not in possible names list
     * @return shared_ptr to hasher
     */
    std::shared_ptr<IHash> TrySetHasher(const std::string& hasher);

    /**
     * @brief Set filemasks for scanning
     * @param filemasks - vector of filemasks as std::string
     * @return vector of filemasks as boost::regex
     */
    std::vector<boost::regex> SetFileMasks(const std::vector<std::string>& filemasks);

    void ScanPath(const boost::filesystem::path& path, size_t depth);

    void AddFile(const boost::filesystem::path& path);

    bool InExcludeDirs(const boost::filesystem::path& path);

    bool MasksSatisfied(const boost::filesystem::path& path);

    bool AlreadyInDuplicates(const boost::filesystem::path& path,
                             const std::unordered_map<std::string, std::vector<std::string>>& duplicates);
};