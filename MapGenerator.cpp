#include <vector>
#include "Assemble.h"
// 0 - пустая клетка, 1 - хилка, 2 - монстр1, 3 - монстр2, 4 - выход, 5 - игрок 
// процентное соотношение: 40, 35, 10, 10, 5
void GenerateObjects(std::vector<std::vector<int>>&layout_plan) {
  std::random_device rd;
  std::mt19937 gen(rd());
  int chest_count = 0;
  for (int i = 0; i < map_size; i++) {
    std::vector<int> buf_vector;
    layout_plan.push_back(buf_vector);
    for (int j = 0; j < map_size; j++) {
      layout_plan[i].push_back(0);
    }
  }
  for (int i = 0; i < map_size; i++) {
    for (int j = 0; j < map_size; j++) {
      int tyle_tupe = gen() % map_rand_size;
      if (tyle_tupe < empty_tyle_chance) {
        layout_plan[i][j] = empty_tyle_idx;
      } else if (tyle_tupe < heal_tyle_chance) {
        layout_plan[i][j] = heal_tyle_idx;
      } else if (tyle_tupe < monster1_tyle_chance) {
        layout_plan[i][j] = monster1_tyle_idx;
      } else if (tyle_tupe < monster2_tyle_chance) {
        layout_plan[i][j] = monster2_tyle_idx;
      } else if (tyle_tupe < chest_tyle_chance) {
        layout_plan[i][j] = chest_tyle_idx;
        chest_count += 1;
      }
    }
  }
  if (chest_count < min_chest_amount) {
    for (int i = 0; i < min_chest_amount; i++) {
      layout_plan[i][0] = chest_tyle_idx;
    }
  }
  int door_pos_x = gen() % map_size;
  int door_pos_y = gen() % map_size;
  while (door_pos_x == player_start_pos[0]) {
    door_pos_x = gen() % map_size;
  }
  while (door_pos_y == player_start_pos[1]) {
    door_pos_y = gen() % map_size;
  }
  layout_plan[door_pos_x][door_pos_y] = exit_tyle_idx;
  layout_plan[player_start_pos[0]][player_start_pos[1]] = player_tyle_idx;
}
void GenerateCoordinates(std::vector<std::vector<std::pair<float, float>>>& layout_coordinates) { 
  float x=0;
  float y=0;
  for (int i = 0; i < map_size; i++) {
    x = horizontal_border+i*grid_gap;
    y = vertical_border;
    std::vector<std::pair<float, float>> buf_vector;
    layout_coordinates.push_back(buf_vector);
    for (int j = 0; j < map_size; j++) {
      y = vertical_border + j * grid_gap;
      layout_coordinates[i].push_back({x, y});
    }
  }
}