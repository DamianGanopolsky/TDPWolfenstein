#include <string>
#include "yaml-cpp/yaml.h"
#include <map>
#include <iostream>
#include <fstream>

class YamlParser{

private:
    std::map <std::pair<int,int>,int> objects_map;
    
    YAML::Node map;

    //const YAML::Node& initial_map;


public:

    YamlParser(std::string YamlPath);

    std::map <std::pair<int,int>,int> load_map();

    int Map_Height();

    int Map_Width();

    void Write_Map(std::string YamlPathToWrite,std::map <int,std::vector\
    <std::pair<int,int>>> map,int height,int width);

};