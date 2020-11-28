#include <gtest/gtest.h>

#include "../player/player.h"
#include "../player/player_position.h"
#include "../player/player_info.h"

#include <utility>

TEST(PlayerPosition, PlayerPosition) {
    int pos_x = 2;
    int pos_y = 3;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(-1, -1, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos3(MAP_WIDTH+1, MAP_HEIGHT+1, MAP_WIDTH, MAP_HEIGHT);

    ASSERT_EQ(pos_x, pos1.getX());
    ASSERT_EQ(pos_y, pos1.getY());
    ASSERT_EQ(0, pos2.getX());
    ASSERT_EQ(0, pos2.getY());
    ASSERT_EQ(0, pos3.getX());
    ASSERT_EQ(0, pos3.getY());
}

TEST(PlayerPosition, getPosUp) {
    int pos_x = 2;
    int pos_y = 3;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(0, 0, MAP_WIDTH, MAP_HEIGHT);

    std::pair<int,int> par1 = pos1.getPosUp();
    std::pair<int,int> par2 = pos2.getPosUp();
    
    ASSERT_EQ(pos_x, par1.first);
    ASSERT_EQ(pos_y-1, par1.second);
    ASSERT_EQ(0, par2.first);
    ASSERT_EQ(0, par2.second);

    ASSERT_EQ(pos_x, pos1.getX());
    ASSERT_EQ(pos_y, pos1.getY());
}

TEST(PlayerPosition, getPosDown) {
    int pos_x = 2;
    int pos_y = 3;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(MAP_WIDTH, MAP_HEIGHT, MAP_WIDTH, MAP_HEIGHT);

    std::pair<int,int> par1 = pos1.getPosDown();
    std::pair<int,int> par2 = pos2.getPosDown();
    
    ASSERT_EQ(pos_x, par1.first);
    ASSERT_EQ(pos_y+1, par1.second);
    ASSERT_EQ(MAP_WIDTH, par2.first);
    ASSERT_EQ(MAP_HEIGHT, par2.second);

    ASSERT_EQ(pos_x, pos1.getX());
    ASSERT_EQ(pos_y, pos1.getY());
}

TEST(PlayerPosition, getPosLeft) {
    int pos_x = 5;
    int pos_y = 5;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(0, 0, MAP_WIDTH, MAP_HEIGHT);

    std::pair<int,int> par1 = pos1.getPosLeft();
    std::pair<int,int> par2 = pos2.getPosLeft();
    
    ASSERT_EQ(pos_x-1, par1.first);
    ASSERT_EQ(pos_y, par1.second);
    ASSERT_EQ(0, par2.first);
    ASSERT_EQ(0, par2.second);

    ASSERT_EQ(pos_x, pos1.getX());
    ASSERT_EQ(pos_y, pos1.getY());
}

TEST(PlayerPosition, getPosRight) {
    int pos_x = 5;
    int pos_y = 5;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(MAP_WIDTH, MAP_HEIGHT, MAP_WIDTH, MAP_HEIGHT);

    std::pair<int,int> par1 = pos1.getPosRight();
    std::pair<int,int> par2 = pos2.getPosRight();
    
    ASSERT_EQ(pos_x+1, par1.first);
    ASSERT_EQ(pos_y, par1.second);
    ASSERT_EQ(MAP_WIDTH, par2.first);
    ASSERT_EQ(MAP_HEIGHT, par2.second);

    ASSERT_EQ(pos_x, pos1.getX());
    ASSERT_EQ(pos_y, pos1.getY());
}

TEST(PlayerPosition, moveUp) {
    int pos_x = 5;
    int pos_y = 5;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(0, 0, MAP_WIDTH, MAP_HEIGHT);

    pos1.moveUp();
    pos2.moveUp();

    ASSERT_EQ(pos_x, pos1.getX());
    ASSERT_EQ(pos_y-1, pos1.getY());
    ASSERT_EQ(0, pos2.getX());
    ASSERT_EQ(0, pos2.getY());
}

TEST(PlayerPosition, moveDown) {
    int pos_x = 5;
    int pos_y = 5;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(MAP_WIDTH, MAP_HEIGHT, MAP_WIDTH, MAP_HEIGHT);
    
    pos1.moveDown();
    pos2.moveDown();

    ASSERT_EQ(pos_x, pos1.getX());
    ASSERT_EQ(pos_y+1, pos1.getY());
    ASSERT_EQ(MAP_WIDTH, pos2.getX());
    ASSERT_EQ(MAP_HEIGHT, pos2.getY());

}

TEST(PlayerPosition, moveLeft) {
    int pos_x = 5;
    int pos_y = 5;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(0, 0, MAP_WIDTH, MAP_HEIGHT);
    
    pos1.moveLeft();
    pos2.moveLeft();

    ASSERT_EQ(pos_x-1, pos1.getX());
    ASSERT_EQ(pos_y, pos1.getY());
    ASSERT_EQ(0, pos2.getX());
    ASSERT_EQ(0, pos2.getY());
}

TEST(PlayerPosition, moveRight) {
    int pos_x = 2;
    int pos_y = 3;
    PlayerPosition pos1(pos_x, pos_y, MAP_WIDTH, MAP_HEIGHT);
    PlayerPosition pos2(MAP_WIDTH, MAP_HEIGHT, MAP_WIDTH, MAP_HEIGHT);

    pos1.moveRight();
    pos2.moveRight();

    ASSERT_EQ(pos_x+1, pos1.getX());
    ASSERT_EQ(pos_y, pos1.getY());
    ASSERT_EQ(MAP_WIDTH, pos2.getX());
    ASSERT_EQ(MAP_HEIGHT, pos2.getY());
}

 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
