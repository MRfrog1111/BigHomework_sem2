#ifndef ENTITY_H
#define ENTITY_H
class Entity {
 protected:
  int max_hp;
  int atk;

 public:
  int hp;
  virtual void GetDamage(int& damage) = 0;
  void Heal(int& heal_amount) { hp = std::max(max_hp, hp + heal_amount); };
};
#endif