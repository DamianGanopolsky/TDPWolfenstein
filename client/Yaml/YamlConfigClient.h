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

#endif