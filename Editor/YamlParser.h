#include <string>
#include "yaml-cpp/yaml.h"
#include <map>
#include <iostream>
#include <fstream>

class YamlParser{

private:
    std::map <std::pair<int,int>,int> objects_map;

    std::map<int,std::pair<int,int>> players_spawn_map;
    
    YAML::Node map;


public:

    YamlParser(std::string YamlPath);

    std::map <std::pair<int,int>,int> load_map(std::string YamlPath);

    std::map <int,std::pair<int,int>> load_players(std::string YamlPath);

    int Map_Height();

    int Map_Width();

    void Write_Map(std::string YamlPathToWrite,std::map <int,std::vector\
    <std::pair<int,int>>> map,int height,int width);

};