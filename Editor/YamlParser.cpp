#include "YamlParser.h"
#include <iostream>
#include <fstream>
#define PLAYER 1
#define TREASURE 2
#define MEDICAL_KIT 3
#define KEY 4
#define AUTOMATIC_GUN 5
#define CHAIN_CANNON 6
#define FOOD 7
#define BULLETS 8
#define WALL 9
#define DOOR 10

std::string jugadores[]{"0","1"};


std::map <std::pair<int,int>,int> YamlParser::load_map(){



    /* Chain Cannon */
    const YAML::Node& chain_cannon = initial_map["Weapons"]["Chain_Cannon"];
    std::pair<int,int> map_position;
    for (YAML::const_iterator it = chain_cannon["position"].begin(); it != chain_cannon["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,CHAIN_CANNON});
    }

    /* Automatic gun */

    const YAML::Node& automatic_gun = initial_map["Weapons"]["Automatic_Gun"];

    for (YAML::const_iterator it = automatic_gun["position"].begin(); it != automatic_gun["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,AUTOMATIC_GUN});
    }

    /* Treasure */

    const YAML::Node& treasure=initial_map["Treasures"]["Treasure"];
    for (YAML::const_iterator it = treasure["position"].begin(); it != treasure["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,TREASURE});
    }

    /* Red Wall */

    const YAML::Node& red_wall = initial_map["Walls"]["Red_Wall"];

    for (YAML::const_iterator it = red_wall["position"].begin(); it != red_wall["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,WALL});
    }

    /* Players */

    const YAML::Node& players=initial_map["Players"];

    for (YAML::const_iterator it = players.begin(); it != players.end(); ++it) {
        const YAML::Node& pos = *it;
        for(std::size_t i=0;i<sizeof(jugadores)/sizeof(jugadores[0]);i++){
             //std::cout << jugadores[i] << std::endl;
             const YAML::Node& position = pos[jugadores[i]]["position"];
            for(YAML::const_iterator it2 = position.begin(); it2 != position.end(); ++it2){
                const YAML::Node& coord = *it2;
                //std::cout << coord['x'] << std::endl;
            }
        }
    }
    return objects_map;
}

void YamlParser::Write_Map(std::string YamlPathToWrite,std::map <int,\
std::vector<std::pair<int,int>>> map){
    YAML::Emitter out;

    for (auto const& x : map){
        out << YAML::BeginMap;
        out << YAML::Key << x.first;
        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "position";
        out << YAML::Value << YAML::BeginSeq;

        for(std::pair<int,int> position : x.second) {
            out << YAML::BeginMap;
            out << YAML::Key << "x";
            out << YAML::Value << position.first;
            out << YAML::Key << "y";
            out << YAML::Value << position.second;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;
        out << YAML::EndMap;
        out << YAML::EndMap;
    }
    /*
    out << YAML::BeginMap;
    out << YAML::Key << "map_dimentions";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "height" ;
    out << YAML::Value << "36";
    out << YAML::EndMap;
    out << YAML::Key << "children";
    //out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
    out << YAML::Value << YAML::BeginSeq;
    out << "Sashas";
    out << YAML::EndSeq;
    out << YAML::EndMap;*/
    std::ofstream fileOut("../Maps/Export.yaml");
    fileOut << out.c_str();
}

int YamlParser::Map_Height(){
    return initial_map["map_dimentions"]["height"].as<int>();
}

int YamlParser::Map_Width(){
    return initial_map["map_dimentions"]["width"].as<int>();
}