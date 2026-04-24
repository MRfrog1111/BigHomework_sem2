#pragma once
#include "Entity.h"
#include "Player.h"
#include "Assemble.h"
#include "DataSettings.h"
//Player* player = Player::getInstance();
class Enemy : Entity {
 public:
   virtual void GetDamage(int& damage)=0;
 protected:
   float timer_time;
   int score_barrier;
};
class Monster1 : Enemy {
  Monster1() {

  };
  virtual ~Monster1() {};
  void GetDamage(int& damage) override {

  }
};
class Monster2 : Enemy {
  Monster2() {

  };
  virtual ~Monster2() {};
  void GetDamage(int& damage) override {
  
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
  HealingPotion(){ 
	this->score_barrier = healing_potion_score_barrier;
    this->timer_time = healing_potion_timer;
    this->heal_amount = heal_amount_data;
  };
  virtual ~HealingPotion(){};


  void GetDamage(int& damage) override { 
	if (TypeWriterStart(score_barrier,timer_time)) {
      Player::getInstance()->Heal(heal_amount);
    } else {
            GameOver();
      }
  }
};