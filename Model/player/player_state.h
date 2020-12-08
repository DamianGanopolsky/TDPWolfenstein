#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "./player_info.h"
#include "../constants/config.h"
#include "./def.h"
#include "../constants/config_player.h"

class State {
 protected:
    Id player_id;

 public:
    State(Id player_id);
    virtual ~State();

    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;

    virtual const bool attack() const = 0;
    virtual const bool canBeAttacked() const = 0;
    virtual const bool resurrect() const = 0;
};

class Alive : public State {
 public:
    Alive(Id player_id);
    ~Alive();

    Alive(const Alive&) = delete;
    Alive& operator=(const Alive&) = delete;
    Alive(Alive&&) = delete;
    Alive& operator=(Alive&&) = delete;

    virtual const bool attack() const override;
    virtual const bool canBeAttacked() const override;
    virtual const bool resurrect() const override;

};

class Dead : public State {
 public:
    Dead(Id player_id);
    ~Dead();

    Dead(const Dead&) = delete;
    Dead& operator=(const Dead&) = delete;
    Dead(Dead&&) = delete;
    Dead& operator=(Dead&&) = delete;

    virtual const bool attack() const override;
    virtual const bool canBeAttacked() const override;
    virtual const bool resurrect() const override;

};
#endif