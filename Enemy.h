#ifndef ENEMY_H
#define ENEMY_H
#include "Assemble.h"
#include "DataSettings.h"
#include "Entity.h"
#include "Player.h"
class Enemy : Entity {
 public:
  virtual void GetDamage(int& damage) = 0;

 protected:
  float timer_time;
  int score_barrier;
};
class Monster1 : Enemy {
  float min_timer_time;
  float timer_time_minus;
  int score_barrier_plus;

 public:
  int atk;
  int hp;
  Monster1() {
    this->score_barrier = monster1_score_barrier;
    this->timer_time = monster1_timer;
    this->atk = monster1_atk;
    this->hp = monster1_hp;
    this->min_timer_time = min_timer_time_data;
    this->timer_time_minus = timer_time_minus_data;
    this->score_barrier_plus = score_barrier_plus_data;
  };
  virtual ~Monster1() {};
  void GetDamage(int& damage) override {
    if (TypeWriterStart(score_barrier, timer_time)) {
      hp -= damage;
    } else {
      GameOver();
    }
    score_barrier += score_barrier_plus;
    timer_time = std::max(monster1_timer - timer_time_minus, min_timer_time);
  }
};
class Monster2 : Enemy {
 public:
  int atk;
  int hp;
  Monster2() {
    this->score_barrier = monster2_score_barrier;
    this->timer_time = monster2_timer;
    this->atk = monster2_atk;
    this->hp = monster2_hp;
  };
  virtual ~Monster2() {};
  void GetDamage(int& damage) override {
    if (TypeWriterStart(score_barrier, timer_time)) {
      hp -= damage;
    } else {
      hp += damage;
      Player::getInstance()->GetDamage(damage);
    }
  }
};
class Chest : Enemy {
  int key_chance;

 public:
  Chest(int key_chance_data) {
    this->score_barrier = chest_score_barrier;
    this->timer_time = chest_timer;
    this->key_chance = key_chance_data;
  };
  Chest() {
    this->score_barrier = chest_score_barrier;
    this->timer_time = chest_timer;
    this->key_chance = chest_chance_max;
  }
  virtual ~Chest() {};
  void GetDamage(int& damage) override {
    if (TypeWriterStart(score_barrier, timer_time)) {
      std::random_device rd;
      std::mt19937 gen(rd());
      int open_result = gen() % chest_chance_max;
      if (open_result <= key_chance) {
        Player::getInstance()->hasKey = true;
      }
    } else {
      GameOver();
    }
  }
};
class HealingPotion : Enemy {
  int heal_amount;

 public:
  HealingPotion() {
    this->score_barrier = healing_potion_score_barrier;
    this->timer_time = healing_potion_timer;
    this->heal_amount = heal_amount_data;
  };
  virtual ~HealingPotion() {};

  void GetDamage(int& damage) override {
    if (TypeWriterStart(score_barrier, timer_time)) {
      Player::getInstance()->Heal(heal_amount);
    } else {
      GameOver();
    }
  }
};
#endif