#include <string>
#include "yaml-cpp/yaml.h"
#include <map>
#include <iostream>
#include <fstream>

class YamlParser{

private:
    std::map <std::pair<int,int>,int> objects_map;
    
    YAML::Node map;

public:

    YamlParser(std::string YamlPath);

    std::map <std::pair<int,int>,int> load_map(std::string YamlPath);

    int Map_Height();

    int Map_Width();

};