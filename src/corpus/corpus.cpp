/**
 * @file corpus.cpp
 * @author Sean Massung
 */

#include "corpus/corpus.h"
#include "corpus/all.h"

namespace meta {
namespace corpus {

std::unique_ptr<corpus> corpus::load(const std::string & config_file)
{
    auto config = cpptoml::parse_file(config_file);
    std::string type = *config.get_as<std::string>("corpus-type");
    if(type == "file-corpus")
    {
        std::string prefix = *config.get_as<std::string>("prefix");
        std::string file_list = *config.get_as<std::string>("list");
        std::string dataset = *config.get_as<std::string>("dataset");
        std::string file = prefix + "/"
            + dataset + "/" + file_list + "-full-corpus.txt";
        return std::unique_ptr<corpus>{
            new file_corpus{prefix + "/" + dataset + "/", file}
        };
    }
    else
        throw corpus_exception{"corpus type was not able to be determined"};
}

}
}
