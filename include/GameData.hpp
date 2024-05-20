// GameData.hpp
#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include <iostream>
#include <string>
#include <array>
#include <filesystem>
#include "pugixml.hpp"

constexpr std::size_t MAX_RACES{ 12 };
constexpr std::size_t MAX_CLASSES{ 14 };

enum class ReadFileStatus : int {
  SUCCESS = 0x0,
  FILE_NOT_FOUND = 0x1,
  INVALID_FORMAT = 0x2,
  TOO_MANY_ITEMS = 0x3,
  EMPTY_ITEM = 0x4,
  UNKNOWN_ERROR = 0xFFFFFFFF // TODO: see why it doesn't accept it and it rather complains (warning) - put breakpoint on implementation or on definition
};

struct GameData {
  std::array<std::string, MAX_RACES> races{};
  std::array<std::string, MAX_CLASSES> classes{};
  std::size_t race_count{ 0 };
  std::size_t class_count{ 0 };

  GameData();

  template <std::size_t N>
  ReadFileStatus LoadFromFile(const std::string& filename, std::array<std::string, N>& data, std::size_t& count);

  // Specialized templates
  template <>
  ReadFileStatus LoadFromFile<MAX_RACES>(const std::string& filename, std::array<std::string, MAX_RACES>& data, std::size_t& count);

  template <>
  ReadFileStatus LoadFromFile<MAX_CLASSES>(const std::string& filename, std::array<std::string, MAX_CLASSES>& data, std::size_t& count);

private:
  template <std::size_t N>
  ReadFileStatus ReadFile(const std::string& filename, std::array<std::string, N>& data, std::size_t& count);

  static void PrintWorkingDirectory();
};

#endif // GAMEDATA_HPP
