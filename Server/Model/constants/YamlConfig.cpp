#include "YamlConfig.h"

YAML::Node data_config=YAML::LoadFile("../Yaml_configs/server_config.yaml");

const struct YamlParamConfig GameConfig = {
    .kit_points=data_config["kit_points"].as<int>(),
    .food_points=data_config["food_points"].as<int>(),
    .max_life=data_config["max_life"].as<int>(),
    .cup_points=data_config["cup_points"].as<int>(),
    .max_bullets=data_config["max_bullets"].as<int>(), 
    .num_bullets_picked_up=data_config["num_bullets_picked_up"].as<int>(),
    .knife_base_damage=data_config["knife_base_damage"].as<int>(),
    .gun_base_damage=data_config["gun_base_damage"].as<int>(),
    .machine_gun_base_damage=data_config["machine_gun_base_damage"].as<int>(),
    .chain_cannon_base_damage=data_config["chain_cannon_base_damage"].as<int>(),
    .knife_max_range=data_config["knife_max_range"].as<int>(),
    .machine_gun_cooldown=data_config["machine_gun_cooldown"].as<int>(),
    .chain_cannon_cooldown=data_config["chain_cannon_cooldown"].as<int>(),
    .max_resurrections=data_config["max_resurrections"].as<int>(),
};
