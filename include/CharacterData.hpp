// CharacterData.hpp
#ifndef CHARACTER_DATA
#define CHARACTER_DATA

#include <iostream>
#include <cstdint>
#include <string>
#include <utility>
#include "GameData.hpp"

class CharacterData {
public:
  // For players
  CharacterData(const GameData& game_data, const std::string& name, std::uint8_t race, std::uint8_t class_type);

  // Only for developers (not for donators; it's not a pay-to-win game)
  CharacterData(const GameData& game_data, const std::string& name, std::uint8_t race, std::uint8_t class_type, std::uint8_t level, std::uint16_t health, std::uint16_t mana);

  ~CharacterData() = default;

  // Inline Setters
  void SetName(const std::string& name);
  void SetRace(std::uint8_t race);
  void SetClassType(std::uint8_t class_type);
  void SetLevel(std::uint8_t level);
  void SetHealth(std::uint16_t health);
  void SetMana(std::uint16_t mana);

  // Inline Getters
  std::string GetName() const;
  std::uint8_t GetRaceIndex() const;
  std::string GetRace() const;
  std::uint8_t GetClassTypeIndex() const;
  std::string GetClassType() const;
  std::uint8_t GetLevel() const;
  std::uint16_t GetHealth() const;
  std::uint16_t GetMana() const;

  // Member Functions
  void Print() const;
  void SaveCharacter(const std::string& filename) const;

private:
  const GameData& m_game_data;
  const std::string filename;
  std::string m_name;
  std::uint32_t m_data; // First 32 bits for race, class, level, health
  std::uint16_t m_mana_data; // Additional 16 bits for mana

  struct Mask {
    static constexpr std::uint32_t kRace{ 0x1F };
    static constexpr std::uint32_t kClassType{ 0x1F << 5 };
    static constexpr std::uint32_t kLevel{ 0x3F << 10 };
    static constexpr std::uint32_t kHealth{ 0xFFFFU << 16 };
  };
  // Narrowing conversion rule:
  // Prevents certain implicit type conversions that can lose information, such as converting from a
  // larger integer type to a smaller one, or from a signed type to an unsigned type where the value
  // might not fit. In my case, '0xFFFF << 16' is treated as an 'int', and shifting it left by 16 bits
  // results in a value that doesn't fit in a 32-bit 'uint32_t' without potentially losing information,
  // hence the narrowing conversion error. To fix this, I can use a 'uint32_t' literal by appending the
  // 'U' suffix to the hexadecimal constants, ensuring they are treaded as 'uint32_t' from the start.
};

// Inline Setters
inline void CharacterData::SetName(const std::string& name) {
  m_name = name;
}

inline void CharacterData::SetRace(std::uint8_t race) {
  m_data = (m_data & ~Mask::kRace) | (race & 0x1F);
}

inline void CharacterData::SetClassType(std::uint8_t class_type) {
  m_data = (m_data & ~Mask::kClassType) | ((class_type & 0x1F) << 5);
}

inline void CharacterData::SetLevel(std::uint8_t level) {
  m_data = (m_data & ~Mask::kLevel) | ((level & 0x1F) << 10);
}

inline void CharacterData::SetHealth(std::uint16_t health) {
  m_data = (m_data & ~Mask::kHealth) | ((health & 0x1F) << 16);
}

inline void CharacterData::SetMana(std::uint16_t mana) {
  m_mana_data = mana;
}

// Inline Getters
inline std::string CharacterData::GetName() const {
  return m_name;
}

inline std::uint8_t CharacterData::GetRaceIndex() const {
  return m_data & Mask::kRace;
}

inline std::string CharacterData::GetRace() const {
  return m_game_data.races[GetRaceIndex()];
}

inline std::uint8_t CharacterData::GetClassTypeIndex() const {
  return (m_data >> 5) & 0x1F;
}

inline std::string CharacterData::GetClassType() const {
  return m_game_data.classes[GetClassTypeIndex()];
}

inline std::uint8_t CharacterData::GetLevel() const {
  return (m_data >> 10) & 0x3F;
}

inline std::uint16_t CharacterData::GetHealth() const {
  return (m_data >> 16) & 0xFFFF;
}

inline std::uint16_t CharacterData::GetMana() const {
  return m_mana_data;
}

#endif // CHARACTER_DATA
