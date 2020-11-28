#include <gtest/gtest.h>

#include "../player/player.h"
#include "../player/player_position.h"
#include "../player/player_info.h"

#include <utility>

TEST(PlayerInfo, getLife) {
    PlayerInfo info;
    ASSERT_EQ(MAX_LIFE, info.getLife());
}

TEST(PlayerInfo, getKey) {
    PlayerInfo info;
    ASSERT_EQ(0, info.getKey());
}

TEST(PlayerInfo, getNumBullets) {
    PlayerInfo info;
    ASSERT_EQ(0, info.getNumBullets());

}

TEST(PlayerInfo, getTreasure) {
    PlayerInfo info;
    ASSERT_EQ(0, info.getTreasure());

}

TEST(PlayerInfo, addLife) {
    int num = 5;
    PlayerInfo info;
    info.addLife(num);
    ASSERT_EQ(MAX_LIFE, info.getLife());
}

TEST(PlayerInfo, addNumKeys) {
    int num = 5;
    PlayerInfo info;
    info.addNumKeys(num);
    ASSERT_EQ(0 + num, info.getKey());
}

TEST(PlayerInfo, addBullets) {
    int num = 5;
    PlayerInfo info;
    info.addBullets(num);
    ASSERT_EQ(0 + num, info.getNumBullets());
    info.addBullets(MAX_BULLETS);
    ASSERT_EQ(MAX_BULLETS, info.getNumBullets());
}


TEST(PlayerInfo, addTreasure) {
    int num = 5;
    PlayerInfo info;
    info.addTreasure(num);
    ASSERT_EQ(0 + num, info.getTreasure());
}

TEST(PlayerInfo, reduceLife) {
    int to_reduce = 5;
    int life = 3;
    PlayerInfo info;
    info.reduceLife(to_reduce);
    ASSERT_EQ(MAX_LIFE - to_reduce, info.getLife());
    info.addLife(life);
    ASSERT_EQ(MAX_LIFE - to_reduce + life, info.getLife());
    info.reduceLife(MAX_LIFE);
    ASSERT_EQ(0, info.getLife());
}

TEST(PlayerInfo, reduceNumKeys) {
    int to_reduce = 5;
    int life = 10;
    PlayerInfo info;
    info.reduceNumKeys(to_reduce);
    ASSERT_EQ(0, info.getKey());
    info.addNumKeys(life);
    info.reduceNumKeys(to_reduce);
    ASSERT_EQ(life-to_reduce, info.getKey());
}

TEST(PlayerInfo, reduceBullets) {
    int to_reduce = 5;
    int life = 10;
    PlayerInfo info;
    info.reduceBullets(to_reduce);
    ASSERT_EQ(0, info.getNumBullets());
    info.addBullets(life);
    info.reduceBullets(to_reduce);
    ASSERT_EQ(life-to_reduce, info.getNumBullets());
}

TEST(PlayerInfo, reduceTreasure) {
    int to_reduce = 5;
    int life = 10;
    PlayerInfo info;
    info.reduceTreasure(to_reduce);
    ASSERT_EQ(0, info.getTreasure());
    info.addTreasure(life);
    info.reduceTreasure(to_reduce);
    ASSERT_EQ(life-to_reduce, info.getTreasure());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
