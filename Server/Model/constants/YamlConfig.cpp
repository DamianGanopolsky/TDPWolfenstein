#include "YamlConfig.h"

YAML::Node data_config=YAML::LoadFile("../Yaml_configs/server_config.yaml");

const struct YamlParamConfig GameConfig = {
    .kit_points=data_config["kit_points"].as<int>(),
    .food_points=data_config["food_points"].as<int>(),
    .max_life=data_config["max_life"].as<int>(),
    .cup_points=data_config["cup_points"].as<int>(),
    .max_bullets=data_config["max_bullets"].as<int>(), 
    .num_bullets_picked_up=data_config["num_bullets_picked_up"].as<int>(),
};
