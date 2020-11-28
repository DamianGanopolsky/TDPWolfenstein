#include <gtest/gtest.h>

#include "../commands/command_pick_up.h"
#include "../objects/items/treasures/chest.h"

TEST(CommandPickUp, CommandPickUp) {
    PlayerInfo info;
    CommandPickUp cmd();
    ASSERT_EQ(0, 0);
}

TEST(CommandPickUp, pickUpBullet) {
    PlayerInfo info;
    CommandPickUp cmd;

    Bullet item;
    ASSERT_EQ(true, cmd.pickUp(info, item));
    ASSERT_EQ(NUM_BULLETS_PICKED_UP, info.getNumBullets());

    info.addBullets(MAX_BULLETS);
    ASSERT_EQ(false, cmd.pickUp(info, item));
    ASSERT_EQ(MAX_BULLETS, info.getNumBullets());
}

TEST(CommandPickUp, pickUpBlood) {
    PlayerInfo info;
    CommandPickUp cmd;

    Blood item;
    ASSERT_EQ(false, cmd.pickUp(info, item));
    ASSERT_EQ(MAX_LIFE, info.getLife());

    info.reduceLife(MAX_LIFE);
    info.addLife(BLOOD_MINIMUN_TO_HEAL+1);
    ASSERT_EQ(false, cmd.pickUp(info, item));
    ASSERT_EQ(BLOOD_MINIMUN_TO_HEAL+1, info.getLife());

    info.reduceLife(BLOOD_MINIMUN_TO_HEAL);
    ASSERT_EQ(true, cmd.pickUp(info, item));
    ASSERT_EQ(BLOOD_POINTS+1, info.getLife());
}


TEST(CommandPickUp, pickUpFood) {
    PlayerInfo info;
    CommandPickUp cmd;

    Food item;
    ASSERT_EQ(false, cmd.pickUp(info, item));
    ASSERT_EQ(MAX_LIFE, info.getLife());

    info.reduceLife(MAX_LIFE);
    ASSERT_EQ(true, cmd.pickUp(info, item));
    ASSERT_EQ(MAX_LIFE/2, info.getLife());
}

TEST(CommandPickUp, pickUpKit) {
    PlayerInfo info;
    CommandPickUp cmd;

    Kit item;
    ASSERT_EQ(false, cmd.pickUp(info, item));
    ASSERT_EQ(MAX_LIFE, info.getLife());

    info.reduceLife(MAX_LIFE);
    ASSERT_EQ(true, cmd.pickUp(info, item));
    ASSERT_EQ(MAX_LIFE, info.getLife());
}

TEST(CommandPickUp, pickUpKey) {
    PlayerInfo info;
    CommandPickUp cmd;

    Key item;
    ASSERT_EQ(true, cmd.pickUp(info, item));
    ASSERT_EQ(1, info.getKey());
}

TEST(CommandPickUp, pickUpTreasure) {
    PlayerInfo info;
    CommandPickUp cmd;
    Chest chest;
    ASSERT_EQ(true, cmd.pickUp(info, chest));
    ASSERT_EQ(CHEST_POINTS, info.getTreasure());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
