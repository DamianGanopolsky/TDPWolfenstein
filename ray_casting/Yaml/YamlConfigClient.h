#ifndef YAMLCONFIGCLIENT_H 
#define YAMLCONFIGCLIENT_H

#include <string>
#include "yaml-cpp/yaml.h"

struct YamlParamConfig{
    int screen_height;
    int screen_width;
    int constant_rate_loop_ms;
};

extern const struct YamlParamConfig ClientConfig;
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