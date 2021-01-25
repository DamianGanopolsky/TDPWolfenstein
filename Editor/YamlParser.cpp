#include "YamlParser.h"
#include <iostream>

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
#define CUADRICULA 64


std::string jugadores[]{"0","1"};

YamlParser::YamlParser(std::string YamlPath){
    map= YAML::LoadFile(YamlPath);
}


std::map <std::pair<int,int>,int> YamlParser::load_map(){

    
    /* Chain Cannon */
    //const YAML::Node& initial_map=map["Map"];
    //std::cout << initial_map["map_dimentions"]["height"] << std::endl;
    //const YAML::Node& chain_cannon = initial_map["Chain_Cannon"];
    const YAML::Node& chain_cannon = map["Map"]["Chain_Cannon"];
    std::pair<int,int> map_position;
    for (YAML::const_iterator it = chain_cannon["position"].begin(); it != chain_cannon["position"].end(); ++it) {
        
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,CHAIN_CANNON});
    }

    const YAML::Node& door= map["Map"]["Door"];
    for (YAML::const_iterator it = door["position"].begin(); it != door["position"].end(); ++it) {
        
        const YAML::Node& pos = *it;
        //std::cout << "Map" << std::endl;
        //std::cout << "x es" << map_position.first << "y es" << map_position.second << std::endl;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,DOOR});
    }

    const YAML::Node& food= map["Map"]["Food"];
    for (YAML::const_iterator it = food["position"].begin(); it != food["position"].end(); ++it) {
        
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,FOOD});
    }

    const YAML::Node& medical_kit= map["Map"]["Medical_Kit"];
    for (YAML::const_iterator it = medical_kit["position"].begin(); it != medical_kit["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,MEDICAL_KIT});
    }
    

    /* Automatic gun */
    //const YAML::Node& initial_map=map["Map"];

    //const YAML::Node& automatic_gun = initial_map["Weapons"]["Automatic_Gun"];
    const YAML::Node& automatic_gun = map["Map"]["Automatic_Gun"];

    for (YAML::const_iterator it = automatic_gun["position"].begin(); it != automatic_gun["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,AUTOMATIC_GUN});
    }

    /* Treasure */

    //const YAML::Node& treasure=initial_map["Treasures"]["Treasure"];
    //const YAML::Node& treasure=initial_map["Treasure"];
    const YAML::Node& treasure=map["Map"]["Treasure"];
    for (YAML::const_iterator it = treasure["position"].begin(); it != treasure["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,TREASURE});
    }

    /* Red Wall */

    //const YAML::Node& red_wall = initial_map["Walls"]["Red_Wall"];
    //const YAML::Node& red_wall = initial_map["Red_Wall"];
    const YAML::Node& red_wall=map["Map"]["Red_Wall"];
    

    for (YAML::const_iterator it = red_wall["position"].begin(); it != red_wall["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,WALL});
    }

    /* Players */


    //const YAML::Node& players=initial_map["Players"];
    
    const YAML::Node& players=map["Map"]["Players"];

    for (YAML::const_iterator it = players["position"].begin(); it != players["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map[map_position]=PLAYER;
       // objects_map.insert({map_position,PLAYER});
        /*for(std::size_t i=0;i<sizeof(jugadores)/sizeof(jugadores[0]);i++){
             //std::cout << jugadores[i] << std::endl;
            const YAML::Node& position = pos[jugadores[i]]["position"];
            for(YAML::const_iterator it2 = position.begin(); it2 != position.end(); ++it2){
                const YAML::Node& coord = *it2;
                //std::cout << coord['x'] << std::endl;
            }
        }*/
    }
    
    return objects_map;
}

void YamlParser::Write_Map(std::string YamlPathToWrite,std::map <int,\
std::vector<std::pair<int,int>>> map,int height,int width){
    YAML::Emitter out;
    //out << YAML::BeginDoc;
    out << YAML::BeginMap;
    out << YAML::Key<< "Map";
    out << YAML::Value << YAML::BeginMap;
    //out << YAML::BeginMap;
    out << YAML::Key << "map_dimentions";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "height";
    out << YAML::Value << height;
    out << YAML::Key << "width";
    out << YAML::Value << width;
    out << YAML::EndMap;
    //out << YAML::EndMap;

    for (auto const& x : map){
        //out << YAML::BeginMap;
       // out << YAML::Key << x.first;
        switch(x.first){
            case PLAYER:
                out << YAML::Key << "Players";
                break;
            case TREASURE:
                out << YAML::Key << "Treasure";
                break;
            case MEDICAL_KIT:
                out << YAML::Key << "Medical_Kit";
                break;
            case KEY:
                out << YAML::Key << "Key";
                break;
            case AUTOMATIC_GUN:
                out << YAML::Key << "Automatic_Gun";
                break;
            case CHAIN_CANNON:
                out << YAML::Key << "Chain_Cannon";
                break;
            case FOOD:
                out << YAML::Key << "Food";
                break;
            case BULLETS:
                out << YAML::Key << "Bullets";
                break;
            case WALL:
                out << YAML::Key << "Red_Wall";
                break;
            case DOOR:
                out << YAML::Key << "Door";
                break;
            default:
                break;
        }
        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "position";
        out << YAML::Value << YAML::BeginSeq;

        for(std::pair<int,int> position : x.second) {
            out << YAML::BeginMap;
            out << YAML::Key << "x";
            out << YAML::Value << position.first*CUADRICULA;
            out << YAML::Key << "y";
            out << YAML::Value << position.second*CUADRICULA;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;
        out << YAML::EndMap;
    }
    out << YAML::EndMap;
    std::ofstream fileOut("../Maps/Export.yaml");
    fileOut << out.c_str();
}

int YamlParser::Map_Height(){
    //return initial_map["map_dimentions"]["height"].as<int>();
    return map["Map"]["map_dimentions"]["height"].as<int>();
}

int YamlParser::Map_Width(){
    //return initial_map["map_dimentions"]["width"].as<int>();
    return map["Map"]["map_dimentions"]["width"].as<int>();
}