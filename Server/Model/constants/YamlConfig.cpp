#include "YamlConfig.h"

YAML::Node data_config=YAML::LoadFile("../Yaml_configs/server_config.yaml");

const struct YamlParamConfig GameConfig = {
    .rotation_size=data_config["rotation_size"].as<int>(),
    .displacement=data_config["displacement"].as<int>(),
    .pi=data_config["pi"].as<float>(),
    .points_per_cell=data_config["points_per_cell"].as<int>(),
    .kills_weight_final_score=data_config["kills_weight_final_score"].as<int>(),
    .treasure_weight_final_score=data_config["treasure_weight_final_score"].as<int>(),
    .kit_points=data_config["kit_points"].as<int>(),
    .food_points=data_config["food_points"].as<int>(),
    .max_life=data_config["max_life"].as<int>(),
    .max_resurrections=data_config["max_resurrections"].as<int>(),
    .cup_points=data_config["cup_points"].as<int>(),
    .max_bullets=data_config["max_bullets"].as<int>(), 
    .num_bullets_picked_up=data_config["num_bullets_picked_up"].as<int>(),
    .life_cooldown=data_config["life_cooldown"].as<int>(),
    .time_to_start_life_cooldown=data_config["time_to_start_life_cooldown"].as<int>(),
    .life_lost_because_time=data_config["life_lost_because_time"].as<int>(),
    .knife_base_damage=data_config["knife_base_damage"].as<int>(),
    .gun_base_damage=data_config["gun_base_damage"].as<int>(),
    .machine_gun_base_damage=data_config["machine_gun_base_damage"].as<int>(),
    .chain_cannon_base_damage=data_config["chain_cannon_base_damage"].as<int>(),
    .knife_max_range=data_config["knife_max_range"].as<int>(),
    .machine_gun_cooldown=data_config["machine_gun_cooldown"].as<int>(),
    .chain_cannon_cooldown=data_config["chain_cannon_cooldown"].as<int>(),
};
