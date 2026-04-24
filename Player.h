#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "DataSettings.h"
class Player : public Entity{
  static Player* player;
  Player();
  Player(const Player&);
  Player& operator=(Player&);
 public:
  float x;
  float y;
  int atk;
  bool hasKey;
  bool isDead;
  bool hasPickedUpKey;
  sf::Texture texture;
  sf::Sprite sprite;
  static Player* getInstance() {
    if (!player) player = new Player();
    return player;
  }
  void GetDamage(int& damage) override { 
	  hp -= damage;
    if (hp <= 0) {
            isDead = true;
    }
  };
  void Reset() {
    this->x = player_start_pos[0];
    this->y = player_start_pos[1];
    this->texture.loadFromFile(tyles[player_tyle_idx].second);
    this->sprite.setScale({tyles[player_tyle_idx].first.first,
                           tyles[player_tyle_idx].first.second});
    this->atk = player_atk;
    this->hp = player_hp;
    this->max_hp = player_hp;
    this->hasKey = false;
    this->hasPickedUpKey = false;
    this->isDead = false;
  }
};