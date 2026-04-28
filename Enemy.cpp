#include "Enemy.h"
Monster* Monster::createMonster(int id) {
  Monster* p = nullptr;
  switch (id) {
    case monster1_tyle_idx:
      p = new Monster1();
      break;
    case monster2_tyle_idx:
      p = new Monster2();
      break;
    default:
      assert(false);
  }
  return p;
};
