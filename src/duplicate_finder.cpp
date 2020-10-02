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
    for (const auto& dir : include_dirs_)
    {
        for (const boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator(dir))
        {
            ScanPath(entry.path(), scan_depth_);
        }
    }
    std::unordered_map<std::string, std::vector<std::string>> duplicates;
    if (files_.size() < 2)
    {
        return duplicates;
    }
    for (auto first_file = std::begin(files_); first_file != end(files_); first_file++)
    {
        if (not AlreadyInDuplicates(first_file->GetFilePath(), duplicates))
        {
            for (auto second_file = std::begin(files_); second_file != end(files_); second_file++)
            {
                if (not AlreadyInDuplicates(second_file->GetFilePath(), duplicates) && first_file->GetFilePath() != second_file->GetFilePath())
                {
                    if (first_file->Equal(*second_file))
                    {
                        duplicates[first_file->GetFilePath().string()].emplace_back(
                            second_file->GetFilePath().string());
                    }
                }
            }
        }
    }
    return duplicates;
}

std::vector<boost::filesystem::path> DuplicateFinder::TrySetDirs(const std::vector<std::string>& dirs)
{
    std::vector<boost::filesystem::path> directories;
    for (const std::string& dir : dirs)
    {
        auto path = boost::filesystem::weakly_canonical(boost::filesystem::absolute(dir));
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
        return std::make_shared<MD5Hasher>();
    }
    if (hasher == "sha1")
    {
        return std::make_shared<SHA1Hasher>();
    }
    if (hasher == "crc32")
    {
        return std::make_shared<CRC32Hasher>();
    }
    throw std::runtime_error("Hasher type doesn't recognized: " + hasher);
}

std::vector<boost::regex> DuplicateFinder::SetFileMasks(const std::vector<std::string>& filemasks)
{
    std::vector<boost::regex> resulted_masks;
    for (const std::string& mask : filemasks)
    {
        resulted_masks.emplace_back(boost::regex(mask));
    }
    return resulted_masks;
}

void DuplicateFinder::ScanPath(const boost::filesystem::path& path, size_t depth)
{
    if (boost::filesystem::exists(path) and not InExcludeDirs(path))
    {
        if (boost::filesystem::is_regular_file(path))
        {
            AddFile(path);
        }
        else if (boost::filesystem::is_directory(path) and depth > 0)
        {
            for (const boost::filesystem::directory_entry& dir : boost::filesystem::directory_iterator(path))
            {
                ScanPath(dir.path(), depth - 1);
            }
        }
    }
}

void DuplicateFinder::AddFile(const boost::filesystem::path& path)
{
    using namespace boost::filesystem;
    if (not exists(path) or not is_regular_file(path))
    {
        return;
    }
    if (file_size(path) < min_file_size_)
    {
        return;
    }
    if (not MasksSatisfied(path))
    {
        return;
    }
    std::string abs_path = weakly_canonical(absolute(path)).string();
    if (scanned_file_paths_.find(abs_path) != scanned_file_paths_.end())
    {
        return;
    }
    scanned_file_paths_.insert(abs_path);
    files_.emplace_back(HashedFile(path.string(), block_size_, hasher_));
}

bool DuplicateFinder::InExcludeDirs(const boost::filesystem::path& path)
{
    for (const auto& excluded_dir : exclude_dirs_)
    {
        if (boost::filesystem::equivalent(path, excluded_dir))
        {
            return true;
        }
    }
    return false;
}

bool DuplicateFinder::MasksSatisfied(const boost::filesystem::path& path)
{
    if (filemasks_.size() == 0)
    {
        return true;
    }
    std::string filename = path.filename().string();
    for (const auto& mask : filemasks_)
    {
        if (boost::regex_match(filename, mask))
        {
            return true;
        }
    };
    return false;
}

bool DuplicateFinder::AlreadyInDuplicates(const boost::filesystem::path& path,
                                          const std::unordered_map<std::string, std::vector<std::string>>& duplicates)
{
    bool already_in_duplicates = false;
    std::string filepath = path.string();
    for (const auto& duplicate : duplicates)
    {
        for (const auto& duplicate_path : duplicate.second)
        {
            if (filepath == duplicate_path)
            {
                already_in_duplicates = true;
                break;
            }
        }
    }
    return already_in_duplicates;
}
