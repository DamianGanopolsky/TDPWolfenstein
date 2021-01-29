#include <string>
#include "yaml-cpp/yaml.h"
#include <map>
#include <iostream>
#include <fstream>

class YamlParser{

private:
    std::map <std::pair<int,int>,int> objects_map;

    std::map<int,bool> walls_map;
    
    YAML::Node map;

public:

    YamlParser(std::string YamlPath);

    std::map <std::pair<int,int>,int> load_objects(std::string YamlPath);

    std::map<int,bool> get_boxes();

    int Map_Height();

    int Map_Width();

};