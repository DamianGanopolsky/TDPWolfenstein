#include "MapYamlParser.h"
#include <iostream>
#define KEY 4
#define MEDICAL_KIT 5
#define TREASURE 6
#define FOOD 7
#define AUTOMATIC_GUN 8
#define BULLETS 9
#define CHAIN_CANNON 10


MapYamlParser::MapYamlParser(std::string YamlPath):yamlpath(YamlPath){
    map= YAML::LoadFile(YamlPath);
}




//std::unordered_map<int,int> MapYamlParser::load_objects(){
std::map<std::pair<int,int>,int> MapYamlParser::load_objects(){

    //map= YAML::LoadFile(YamlPath);
    // Chain Cannon 
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
       /* int num_transformed=Map_Width()*map_position.second+map_position.first;
        objects_map.insert({num_transformed,CHAIN_CANNON});*/
    }

     //FOOD 

    const YAML::Node& food= map["Map"]["Food"];
    for (YAML::const_iterator it = food["position"].begin(); it != food["position"].end(); ++it) {
        
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        //std::cout << "x de obj a cargar es" << map_position.first << "y es" << map_position.second << std::endl;
        objects_map.insert({map_position,FOOD});
        /*int num_transformed=Map_Width()*map_position.second+map_position.first;
        std::cout << "Numero transformado es" << num_transformed << std::endl;
        objects_map.insert({num_transformed,FOOD});*/
    }

/*
    // MEDICAL_KIT 
    const YAML::Node& medical_kit= map["Map"]["Medical_Kit"];
    for (YAML::const_iterator it = medical_kit["position"].begin(); it != medical_kit["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,MEDICAL_KIT});
    }
    

    // a gun
    //const YAML::Node& initial_map=map["Map"];

    //const YAML::Node& automatic_gun = initial_map["Weapons"]["Automatic_Gun"];
    const YAML::Node& automatic_gun = map["Map"]["Automatic_Gun"];

    for (YAML::const_iterator it = automatic_gun["position"].begin(); it != automatic_gun["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,AUTOMATIC_GUN});
    }

    // Treasure 

    //const YAML::Node& treasure=initial_map["Treasures"]["Treasure"];
    //const YAML::Node& treasure=initial_map["Treasure"];
    const YAML::Node& treasure=map["Map"]["Treasure"];
    for (YAML::const_iterator it = treasure["position"].begin(); it != treasure["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,TREASURE});
    }

    // Bullets 
    const YAML::Node& bullet=map["Map"]["Bullets"];
    for (YAML::const_iterator it = bullet["position"].begin(); it != bullet["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,BULLETS});
    }

    // Keys 

    const YAML::Node& key=map["Map"]["Key"];
    for (YAML::const_iterator it = key["position"].begin(); it != key["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        map_position.first=pos['x'].as<int>();;
        map_position.second=pos['y'].as<int>();;
        objects_map.insert({map_position,KEY});
    }*/
    return objects_map;
}


std::map<int,int> MapYamlParser::get_boxes(){
    //map= YAML::LoadFile(yamlpath);
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
        //std::cout << "Wall";
        //std::cout << "en x" << x << "en y" << y << std::endl;
        int num_transformed=Map_Width()*y+x;
        //std::cout << "Num transformed" << num_transformed << std::endl;
        //std::cout << "En " << num_transformed << "cargo una pared" << std::endl;
        walls_map[num_transformed]=0;
    }

    const YAML::Node& door= map["Map"]["Door"];
    for (YAML::const_iterator it = door["position"].begin(); it != door["position"].end(); ++it) {
        
        const YAML::Node& pos = *it;
        //NECESITO TRANSFORMARLO A CUADRICULA
        int x=pos['x'].as<int>();;
        int y=pos['y'].as<int>();;
        //std::cout << "Door";
        x=x/64;
        y=y/64;
        //std::cout << "en x" << x << "en y" << y << std::endl;
        int num_transformed=Map_Width()*y+x;
        //std::cout << "Num transformed" << num_transformed << std::endl;
        walls_map[num_transformed]=1;
        //walls_map.insert({num_transformed,KEY});

    }
    
    return walls_map;
}

int MapYamlParser::Map_Height(){
    return map["Map"]["map_dimentions"]["height"].as<int>();
}

int MapYamlParser::Map_Width(){
    return map["Map"]["map_dimentions"]["width"].as<int>();
}