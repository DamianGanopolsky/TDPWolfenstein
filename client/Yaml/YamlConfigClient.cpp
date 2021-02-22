#include "YamlConfigClient.h"

YAML::Node data_config=YAML::LoadFile("../Yaml_configs/client_settings.yaml");

const struct YamlParamConfig ClientConfig = {
    .screen_height=data_config["Screen_height"].as<int>(),
    .screen_width=data_config["Screen_width"].as<int>(),
    .constant_rate_loop_ms=data_config["constant_rate_loop_render_ms"].as<int>(),
};

