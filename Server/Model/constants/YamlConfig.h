#ifndef YAMLCONFIG_H 
#define YAMLCONFIG_H

#include <string>
#include "yaml-cpp/yaml.h"

struct YamlParamConfig{
    int kit_points;
    int food_points;
    int max_life;
    int cup_points;
    int max_bullets;
    int num_bullets_picked_up;
    int knife_base_damage;
    int gun_base_damage;
    int machine_gun_base_damage;
    int chain_cannon_base_damage;
    int knife_max_range;
    int machine_gun_cooldown;
    int chain_cannon_cooldown;
    int max_resurrections;
};

extern const struct YamlParamConfig GameConfig;
//int kit_points;
//YAML::Node Yaml= YAML::LoadFile("../Yaml_configs/server_config.yaml");
//int kit_points=Yaml["kit"].as<int>();;

/*
void load_yaml_(std::string YamlPath){
    YAML::Node Yaml= YAML::LoadFile(YamlPath);
    kit_points=Yaml["kit"].as<int>();;
}
*/
#endif