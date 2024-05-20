// CharacterData.cpp
#include "./../CharacterData.hpp"

CharacterData::CharacterData(const GameData& game_data, const std::string& name, uint8_t race, uint8_t class_type)
    : m_game_data(game_data), m_name(name), m_data(0), m_mana_data(0) {
      SetRace(race);
      SetClassType(class_type);
}

CharacterData::CharacterData(const GameData& game_data, const std::string& name, uint8_t race, uint8_t class_type, uint8_t level, uint16_t health, uint16_t mana)
  : m_game_data(game_data), m_name(name), m_data(0), m_mana_data(mana) {
  SetRace(race);
  SetClassType(class_type);
  SetLevel(level);
  SetHealth(health);
  SetMana(mana);
}

void CharacterData::Print() const {
  std::cout << "Name: " << GetName() << '\n'
    << "Race: " << m_game_data.races[GetRace()] << '\n'
    << "Class: " << m_game_data.classes[GetClassType()] << '\n'
    << "Level: " << static_cast<int>(GetLevel()) << '\n'
    << "Health: " << static_cast<int>(GetHealth()) << '\n'
    << "Mana: " << static_cast<int>(GetMana()) << '\n';
}
