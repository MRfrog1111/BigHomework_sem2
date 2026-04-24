#include "Player.h"
#include "DataSettings.h"
Player* Player::player = 0;
Player::Player():sprite(texture){ 
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
