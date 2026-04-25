#ifndef DATA_SETTINGS_H
#define DATA_SETTINGS_H
#include <string>
#include <vector>
// typegame settings
const std::string alfabet_def = "abcdefghijklmnopqrstuvwxyz1234567890";
const float timer_text_x = 0;
const float timer_text_y = 0;
const float score_text_x = 0;
const float score_text_y = 30;
const float task_text_x = 200;
const float task_text_y = 200;
const int window_widght = 400;
const int window_height = 400;
const std::string type_game_name = "TypeGame";
const float timer_time_def = 20;
const float timer_minus_def = 1;
// map objects generator
const int min_chest_amount = 3;
const int map_size = 8;
const int map_rand_size = 100;
const int empty_tyle_chance = 30;
const int heal_tyle_chance = 75;
const int monster1_tyle_chance = 80;
const int monster2_tyle_chance = 90;
const int chest_tyle_chance = 100;
const int empty_tyle_idx = 0;
const int heal_tyle_idx = 1;
const int monster1_tyle_idx = 2;
const int monster2_tyle_idx = 3;
const int exit_tyle_idx = 4;
const int player_tyle_idx = 5;
const int chest_tyle_idx = 6;
const int key_tyle_idx = 7;
const int open_door_tyle_idx = 8;
const int player_start_pos[] = {2, 2};
// map grid generator
const std::string game_name = "Yakuza 67";
const int rpg_window_widght = 1100;
const int rpg_window_height = 1200;
const float horizontal_border = 50;
const float vertical_border = 100;
const float grid_gap = 130;
// sprite sources
static std::pair<std::pair<float, float>, std::string> tyles[] = {
    {{0.4, 0.4}, "Sprites/grass.jpg"},    {{0.4, 0.4}, "Sprites/heal.jpg"},
    {{0.4, 0.4}, "Sprites/monster1.jpg"}, {{0.4, 0.4}, "Sprites/monster2.jpg"},
    {{0.4, 0.4}, "Sprites/door.jpg"},     {{0.4, 0.4}, "Sprites/player.jpg"},
    {{0.4, 0.4}, "Sprites/chest.jpg"},    {{0.4, 0.4}, "Sprites/key.jpg"},
    {{0.4, 0.4}, "Sprites/open_door.jpg"}};
// player Settings
static int player_hp = 10;
static int player_atk = 1;
static int player_bleed_dmg = 1;
// chest settings
static int chest_score_barrier = 3;
static float chest_timer = 20;
static int chest_chance_max = 100;
static std::vector<int> chest_chance_poll = {5, 10, 0, 7, 67, 52};
// healing potion settings
static int heal_amount_data = 1;
static int healing_potion_score_barrier = 1;
static float healing_potion_timer = 5;
// monster1 settings
static int monster1_atk = 1;
static int monster1_hp = 2;
static int monster1_score_barrier = 3;
static float monster1_timer = 100;
static float min_timer_time_data = 5;
static float timer_time_minus_data = 3;
static int score_barrier_plus_data = 1;
// monster2 settingss
static int monster2_atk = 1;
static int monster2_hp = 4;
static int monster2_score_barrier = 3;
static float monster2_timer = 10;
#endif