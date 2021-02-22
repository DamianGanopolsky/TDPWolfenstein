#ifndef YAMLCONFIG_H 
#define YAMLCONFIG_H

#include <string>
#include "yaml-cpp/yaml.h"

struct YamlParamConfig{
    int rotation_size;
    int displacement;
    float pi;
    int points_per_cell;
    int kills_weight_final_score;
    int treasure_weight_final_score;
    int kit_points;
    int food_points;
    int max_life;
    int max_resurrections;
    int cup_points;
    int max_bullets;
    int num_bullets_picked_up;
    int life_cooldown;
    int life_lost_because_time;
    int knife_base_damage;
    int gun_base_damage;
    int machine_gun_base_damage;
    int chain_cannon_base_damage;
    int knife_max_range;
    int machine_gun_cooldown;
    int chain_cannon_cooldown;
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