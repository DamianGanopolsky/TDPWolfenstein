cmake_minimum_required(VERSION 2.6)
 
project(testing)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library

add_executable(testing_player_position testing_player_position.cpp ../player/player_position.cpp ../player/player_position.h)
target_link_libraries(testing_player_position ${GTEST_LIBRARIES} pthread)

add_executable(testing_player_info testing_player_info.cpp ../player/player_info.cpp ../player/player_info.h ../objects/items/weapons/weapon.h ../objects/items/weapons/weapon.cpp ../objects/items/item.h ../objects/items/item.cpp ../objects/object.h ../objects/object.cpp ../constants/config.h)
target_link_libraries(testing_player_info ${GTEST_LIBRARIES} pthread)

add_executable(testing_command_pick_up testing_command_pick_up.cpp ../player/player_info.cpp ../player/player_info.h ../objects/items/weapons/weapon.h ../objects/items/weapons/weapon.cpp ../objects/items/item.h ../objects/items/item.cpp ../objects/object.h ../objects/object.cpp ../constants/config.h ../commands/command_pick_up.h ../player/player_position.cpp ../player/player_position.h ../commands/command_pick_up.cpp  ./../player/player.cpp ./../player/player.h ../objects/items/bullets/bullet.cpp ../objects/items/healers/healer.h ../objects/items/healers/healer.cpp ../objects/items/bullets/bullet.h ../objects/items/healers/blood.h ../objects/items/healers/blood.cpp ../objects/items/healers/kit.h ../objects/items/healers/kit.cpp ../objects/items/healers/food.h ../objects/items/healers/food.cpp ../objects/items/keys/key.cpp ../objects/items/treasures/treasure.h ../objects/items/treasures/treasure.cpp  ../objects/items/weapons/weapon.cpp ../objects/items/weapons/weapon.h ../objects/items/treasures/chest.h ../objects/items/treasures/chest.cpp)
target_link_libraries(testing_command_pick_up ${GTEST_LIBRARIES} pthread)
