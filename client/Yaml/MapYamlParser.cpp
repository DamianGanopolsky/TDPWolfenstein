#include "MapYamlParser.h"
#include <iostream>
#define KEY 4
#define MEDICAL_KIT 5
#define TREASURE 6
#define FOOD 7
#define AUTOMATIC_GUN 8
#define BULLETS 9
#define CHAIN_CANNON 10
#define CUADRICULA 64


MapYamlParser::MapYamlParser(std::string YamlPath):yamlpath(YamlPath){
    map= YAML::LoadFile(YamlPath);
}



std::map<std::pair<int,int>,int> MapYamlParser::load_objects(){

    const YAML::Node& chain_cannon = map["Map"]["Chain_Cannon"];
    std::pair<int,int> map_position;
    for (YAML::const_iterator it = chain_cannon["position"].begin(); it != chain_cannon["position"].end(); ++it) {
        
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        map_position.first=map_position.first/CUADRICULA;
        map_position.second=map_position.second/CUADRICULA;
        objects_map.insert({map_position,CHAIN_CANNON});
    }

     //FOOD 

    const YAML::Node& food= map["Map"]["Food"];
    for (YAML::const_iterator it = food["position"].begin(); it != food["position"].end(); ++it) {
        
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        map_position.first=map_position.first/CUADRICULA;
        map_position.second=map_position.second/CUADRICULA;
        objects_map.insert({map_position,FOOD});
    }


    // MEDICAL_KIT 
    const YAML::Node& medical_kit= map["Map"]["Medical_Kit"];
    for (YAML::const_iterator it = medical_kit["position"].begin(); it != medical_kit["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        map_position.first=map_position.first/CUADRICULA;
        map_position.second=map_position.second/CUADRICULA;
        objects_map.insert({map_position,MEDICAL_KIT});
    }
    
    const YAML::Node& automatic_gun = map["Map"]["Automatic_Gun"];

    for (YAML::const_iterator it = automatic_gun["position"].begin(); it != automatic_gun["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        map_position.first=map_position.first/CUADRICULA;
        map_position.second=map_position.second/CUADRICULA;
        objects_map.insert({map_position,AUTOMATIC_GUN});
    }

    // Treasure 

    const YAML::Node& treasure=map["Map"]["Treasure"];
    for (YAML::const_iterator it = treasure["position"].begin(); it != treasure["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        map_position.first=map_position.first/CUADRICULA;
        map_position.second=map_position.second/CUADRICULA;
        objects_map.insert({map_position,TREASURE});
    }

    // Bullets 
    const YAML::Node& bullet=map["Map"]["Bullets"];
    for (YAML::const_iterator it = bullet["position"].begin(); it != bullet["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        map_position.first=map_position.first/CUADRICULA;
        map_position.second=map_position.second/CUADRICULA;
        objects_map.insert({map_position,BULLETS});
    }

    // Keys 

    const YAML::Node& key=map["Map"]["Key"];
    for (YAML::const_iterator it = key["position"].begin(); it != key["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        map_position.first=map_position.first/CUADRICULA;
        map_position.second=map_position.second/CUADRICULA;
        objects_map.insert({map_position,KEY});
    }
    return objects_map;
}


std::map<int,int> MapYamlParser::get_boxes(){
    int total_cuadriculas=Map_Width()*Map_Height();
    
    for(int i=0;i<total_cuadriculas;i++){
        walls_map[i]=2;
    }
    const YAML::Node& red_wall=map["Map"]["Red_Wall"];
    

    for (YAML::const_iterator it = red_wall["position"].begin(); it != red_wall["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        int x=pos['x'].as<int>();;
        int y=pos['y'].as<int>();;
        x=x/64;
        y=y/64;
        int num_transformed=Map_Width()*y+x;
        walls_map[num_transformed]=0;
    }

    const YAML::Node& door= map["Map"]["Door"];
    for (YAML::const_iterator it = door["position"].begin(); it != door["position"].end(); ++it) {
        
        const YAML::Node& pos = *it;
        int x=pos['x'].as<int>();;
        int y=pos['y'].as<int>();;
        x=x/64;
        y=y/64;
        int num_transformed=Map_Width()*y+x;
        walls_map[num_transformed]=1;
    }
    
    return walls_map;
}

int MapYamlParser::get_map_players(){
    return map["Map"]["Cant_players"].as<int>();
}

int MapYamlParser::Map_Height(){
    return map["Map"]["map_dimentions"]["height"].as<int>();
}

int MapYamlParser::Map_Width(){
    return map["Map"]["map_dimentions"]["width"].as<int>();
}