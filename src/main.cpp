#include "./../CharacterData.hpp"
#include "./../GameData.hpp"

int main() {
  GameData game_data;

  ReadFileStatus status;

  

  status = game_data.LoadFromFile("races.xml", game_data.races, game_data.race_count);
  if (status != ReadFileStatus::SUCCESS) {
    std::cerr << "Failed to load races.xml, error code: " << static_cast<int>(status) << std::endl;
    return static_cast<int>(status);
  }

  status = game_data.LoadFromFile("classes.xml", game_data.classes, game_data.class_count);
  if (status != ReadFileStatus::SUCCESS) {
    std::cerr << "Failed to load classes.xml, error code: " << static_cast<int>(status) << std::endl;
    return static_cast<int>(status);
  }

  CharacterData character(game_data, "Costas", 2, 10);  // Create a character with reference to game_data
  character.SetLevel(20);
  character.SetHealth(1500);
  character.SetMana(800);

  character.Print();
}
