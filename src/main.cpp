#include "version.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <map>
#include <vector>

int main(int argc, char* argv[])
{
    try
    {
        boost::program_options::options_description description { "Possible options" };
        description.add_options()("help,h",
                                  "Print help message");

        description.add_options()("include,i",
                                  boost::program_options::value<std::vector<std::string>>()->multitoken(),
                                  "Directories to scan");

        description.add_options()("exclude,e",
                                  boost::program_options::value<std::vector<std::string>>()->multitoken(),
                                  "Directories to exclude");

        description.add_options()("depth,d",
                                  boost::program_options::value<size_t>()->default_value(0),
                                  "Scanning depth");

        description.add_options()("filemask,m",
                                  boost::program_options::value<std::vector<std::string>>()->multitoken(),
                                  "Masks for files to scans");

        description.add_options()("minsize",
                                  boost::program_options::value<uintmax_t>()->default_value(1),
                                  "Minimum file size in bytes");

        description.add_options()("blocksize",
                                  boost::program_options::value<size_t>()->default_value(512),
                                  "Block size in bytes");

        description.add_options()("hash",
                                  boost::program_options::value<std::string>()->default_value("crc32"),
                                  "Hash algorithm (crc32/md5/sha1)");

        boost::program_options::variables_map variables;
        boost::program_options::store(parse_command_line(argc, argv, description), variables);
        boost::program_options::notify(variables);

        if (variables.count("help"))
        {
            std::cout << description << std::endl;
            return 0;
        }
        std::vector<std::string> include_dirs { "." };
        if (variables.count("include"))
        {
            include_dirs = variables["include"].as<std::vector<std::string>>();
        }
        std::vector<std::string> exclude_dirs {};
        if (variables.count("exclude"))
        {
            exclude_dirs = variables["exclude"].as<std::vector<std::string>>();
        }
        [[maybe_unused]] size_t depth = variables["depth"].as<size_t>();
        std::vector<std::string> masks { "*" };
        if (variables.count("filemask"))
        {
            masks = variables["filemask"].as<std::vector<std::string>>();
        }
        [[maybe_unused]] uintmax_t min_size = variables["minsize"].as<uintmax_t>();
        [[maybe_unused]] size_t block_size = variables["blocksize"].as<size_t>();
        std::string hash = variables["hash"].as<std::string>();
        return 0;
    }
    catch (const boost::program_options::error& ex)
    {
        std::cout << ex.what() << '\n';
        return 1;
    }
}
