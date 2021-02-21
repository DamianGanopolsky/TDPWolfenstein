#ifndef MAP_H_
#define MAP_H_

#include "../player/player.h"
#include <unordered_map>
#include "../../../Editor/YamlParser.h"
#include "./../constants/const_object_map.h"

class Map {
   std::unordered_map<Id, Player> players;
    int** map;
    int rows;
    int columns;
    void _loadMatrix(std::map <std::pair<int,int>,int> initial_map);
   
   public:
      Map(std::string YamlPathToMap);
      ~Map();
      int getObjectPos(int x, int y);
      void setObjectPos(int x, int y, ObjectsInMap object);
      std::pair<int, int> getNextPos(Direction direction, int x ,int y, int value);
    
};

#endif   // MAP_H_
