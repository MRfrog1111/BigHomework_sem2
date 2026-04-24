#include "Assemble.h"
#include "Player.h"
#include "Enemy.h"
#include <map>
std::vector<std::vector<sf::Sprite>> sprites_layout;
std::vector<std::vector<int>> layout_plan;
std::vector<std::vector<std::pair<float, float>>> layout_coordinates;
sf::Font font;
sf::RenderWindow window(sf::VideoMode({rpg_window_widght, rpg_window_height}),
                        game_name);
sf::Text main_text(font);
std::map<std::pair<int, int>, Chest> chests;
std::pair<int, int> door_coordinates;
std::string upper_text;
void Start1() {
  window.clear();
  sprites_layout.clear();
  layout_plan.clear();
  layout_coordinates.clear();
  chests.clear();
  Player::getInstance()->Reset();
  GenerateObjects(layout_plan);
  GenerateCoordinates(layout_coordinates);
  font.openFromFile("CyrilicOld.ttf");
  sf::Clock clock;
  FillMap();
  upper_text = "hp:";
  main_text.setString(upper_text + std::to_string(Player::getInstance()->hp));
  window.draw(main_text);
  window.display();
  float timer_time = timer_time_def;
  float timer_minus = timer_minus_def;
  Play1(clock);
}
void Battle(int monster_id) { 
    int turn = 0;
    main_text.setString ("Battle starts! press any key to continue");
    if (monster_id == monster1_tyle_idx) {
      Monster1 monster;
      while (monster.hp > 0) {
        while (const std::optional event = window.pollEvent()) {
          if (event->is<sf::Event::Closed>()) window.close();
          if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
            if (turn % 2 == 0) {
              main_text.setString("Player's turn || Battle: player hp: " +
                                  std::to_string(Player::getInstance()->hp) +
                                  " monster hp: " + std::to_string(monster.hp));
              DrawButtle();
              monster.GetDamage(Player::getInstance()->atk);

            } else {
              main_text.setString("Monster's turn || Battle: player hp: " +
                                  std::to_string(Player::getInstance()->hp) +
                                  " monster hp: " + std::to_string(monster.hp));
              Player::getInstance()->GetDamage(monster.atk);
              DrawButtle();
            }
            turn++;
          }
        }
      }
    }
    if (monster_id == monster2_tyle_idx) {
      Monster2 monster;
      while (monster.hp > 0) {
        while (const std::optional event = window.pollEvent()) {
          if (event->is<sf::Event::Closed>()) window.close();
          if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
             if (turn % 2 == 0) {
              main_text.setString("Player's turn || Battle: player hp: " +
                                  std::to_string(Player::getInstance()->hp) +
                                  " monster hp: " + std::to_string(monster.hp));
               DrawButtle();
              monster.GetDamage(Player::getInstance()->atk);
              
            } else {
               main_text.setString(
                   "Monster's turn || Battle: player hp: " +
                   std::to_string(Player::getInstance()->hp) +
                   " monster hp: " + std::to_string(monster.hp));
              Player::getInstance()->GetDamage(monster.atk);
               DrawButtle();
            }
            turn++;
          }
        }
      }
    }
    main_text.setString(upper_text + std::to_string(Player::getInstance()->hp));
    DrawMap();
}
void FillMap() {
  int chest_idx = 0;
  for (int i = 0; i < map_size; i++) {
    std::vector<sf::Sprite> current_sprites;
    sprites_layout.push_back(current_sprites);
    for (int j = 0; j < map_size; j++) {
      sf::Texture texture;
      texture.loadFromFile(tyles[layout_plan[i][j]].second);
      sf::Sprite sprite(texture);
      sprite.setScale({tyles[layout_plan[i][j]].first.first,
                       tyles[layout_plan[i][j]].first.second});
      sprite.setPosition(
          {layout_coordinates[i][j].first, layout_coordinates[i][j].second});
      sprites_layout[i].push_back(sprite);
      window.draw(sprite);
      if (layout_plan[i][j] == chest_tyle_idx) {
        if (chest_idx == 0) {
          Chest chest(chest_chance_max);
          chests.insert({{i, j}, chest});
        } else {
          std::random_device rd;
          std::mt19937 gen(rd());
          Chest chest(chest_chance_poll[gen() % chest_chance_poll.size()]);
          chests.insert({{i, j}, chest});
        }
        chest_idx++;
      }
      if (layout_plan[i][j] == exit_tyle_idx) {
        door_coordinates = {i, j};
      }
    }
  }
}
void Play1(sf::Clock& clock) {
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
          MovePlayer(Player::getInstance()->x, Player::getInstance()->y - 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
          MovePlayer(Player::getInstance()->x - 1, Player::getInstance()->y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
          MovePlayer(Player::getInstance()->x, Player::getInstance()->y + 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
          MovePlayer(Player::getInstance()->x + 1, Player::getInstance()->y);
        }
      }
    }
  }
}
void MovePlayer(int next_x, int next_y) {
  if (next_x >= 0 && next_x < map_size && next_y >= 0 && next_y < map_size) {
    if (layout_plan[next_x][next_y] == empty_tyle_idx) {
      layout_plan[next_x][next_y] = player_tyle_idx;
      layout_plan[Player::getInstance()->x][Player::getInstance()->y] =
          empty_tyle_idx;
      Player::getInstance()->x = next_x;
      Player::getInstance()->y = next_y;
    }
    else if (layout_plan[next_x][next_y] == heal_tyle_idx) {
      HealingPotion healing_potion;
      healing_potion.GetDamage(Player::getInstance()->atk);
      layout_plan[next_x][next_y] = player_tyle_idx;
      layout_plan[Player::getInstance()->x][Player::getInstance()->y] =
          empty_tyle_idx;
      Player::getInstance()->x = next_x;
      Player::getInstance()->y = next_y;
    } 
    else if (layout_plan[next_x][next_y] == chest_tyle_idx) {
      chests[{next_x, next_y}].GetDamage(Player::getInstance()->atk);
      if (Player::getInstance()->hasKey) {
        layout_plan[next_x][next_y] = key_tyle_idx;
      } else {
        layout_plan[next_x][next_y] = empty_tyle_idx;
      }
    } 
    else if (layout_plan[next_x][next_y] == chest_tyle_idx) {
      chests[{next_x, next_y}].GetDamage(Player::getInstance()->atk);
      if (Player::getInstance()->hasKey) {
        layout_plan[next_x][next_y] = key_tyle_idx;
      } else {
        layout_plan[next_x][next_y] = empty_tyle_idx;
      }
    } 
    else if (layout_plan[next_x][next_y] == key_tyle_idx) {
      layout_plan[next_x][next_y] = player_tyle_idx;
      layout_plan[Player::getInstance()->x][Player::getInstance()->y] =
          empty_tyle_idx;
      Player::getInstance()->x = next_x;
      Player::getInstance()->y = next_y;
      Player::getInstance()->hasPickedUpKey = true;
      upper_text = "has key " + upper_text;
      layout_plan[door_coordinates.first][door_coordinates.second] =
          open_door_tyle_idx;
    } 
    else if (layout_plan[next_x][next_y] == open_door_tyle_idx) {
      if (Player::getInstance()->hasPickedUpKey) {
        Win();
      } 
    } 
    else if (layout_plan[next_x][next_y] == monster2_tyle_idx) {
      Battle(monster2_tyle_idx);
      layout_plan[next_x][next_y] = player_tyle_idx;
      layout_plan[Player::getInstance()->x][Player::getInstance()->y] =
          empty_tyle_idx;
      Player::getInstance()->x = next_x;
      Player::getInstance()->y = next_y;
    }
    else if (layout_plan[next_x][next_y] == monster1_tyle_idx) {
      Battle(monster1_tyle_idx);
      layout_plan[next_x][next_y] = player_tyle_idx;
      layout_plan[Player::getInstance()->x][Player::getInstance()->y] =
          empty_tyle_idx;
      Player::getInstance()->x = next_x;
      Player::getInstance()->y = next_y;
    }
    Player::getInstance()->GetDamage(player_bleed_dmg);
    main_text.setString(upper_text + std::to_string(Player::getInstance()->hp));
    DrawMap();
  }
}
void DrawMap() {
  window.clear();
  for (int i = 0; i < map_size; i++) {
    for (int j = 0; j < map_size; j++) {
      sf::Texture texture;
      texture.loadFromFile(tyles[layout_plan[i][j]].second);
      sf::Sprite sprite(texture);
      sprite.setScale({tyles[layout_plan[i][j]].first.first,
                       tyles[layout_plan[i][j]].first.second});
      sprite.setPosition(
          {layout_coordinates[i][j].first, layout_coordinates[i][j].second});
      window.draw(sprite);
    }
  }
  window.draw(main_text);
  window.display();
  if (Player::getInstance()->isDead) {
    GameOver();
  }
}
void DrawButtle() {
  window.clear();
  window.draw(main_text);
  sf::Text text(font);
  text.setPosition({100, 100});
  text.setString("press Any key to continue");
  window.draw(text);
  window.display();
  if (Player::getInstance()->isDead) {
    GameOver();
  }
}
void Win() {
  window.clear();
  sf::Text text(font);
  text.setString("You sirvived! yay! press Any key to continue");
  window.draw(text);
  window.display();
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      if (event->is<sf::Event::KeyPressed>()) {
        Start1();
      }
    }
  }
}
void GameOver() {
  window.clear();
  sf::Text text(font);
  text.setString("Game Over. press Any key to continue");
  window.draw(text);
  window.display();
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      if (event->is<sf::Event::KeyPressed>()) {
        Start1();
      }
    }
  }
}



