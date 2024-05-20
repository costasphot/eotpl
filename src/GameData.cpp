// GameData.cpp
#include "./../GameData.hpp"

GameData::GameData() {
  PrintWorkingDirectory(); // Print the current working directory for debugging
  LoadFromFile("races.xml", races, race_count);
  LoadFromFile("classes.xml", classes, class_count);
}

void GameData::PrintWorkingDirectory() {
  std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
}

// Helper function to read file
template <std::size_t N>
ReadFileStatus GameData::ReadFile(const std::string& filename, std::array<std::string, N>& data, std::size_t& count) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename.c_str());

  if (!result) {
    std::cerr << "Error: Could not open file " << filename << ": " << result.description() << std::endl;
    return ReadFileStatus::FILE_NOT_FOUND;
  }

  pugi::xml_node root = doc.child("data");
  if (!root) {
    std::cerr << "Error: No root <data> element found in " << filename << std::endl;
    return ReadFileStatus::INVALID_FORMAT;
  }

  count = 0;
  for (pugi::xml_node item : root.children("item")) {
    if (count < data.size()) {
      if (const char* value = item.child_value()) {
        data[count++] = value;
      } else {
        std::cerr << "Error: Empty <item> found in " << filename << std::endl;
        return ReadFileStatus::EMPTY_ITEM;
      }
    } else {
      std::cerr << "Error: Too many <item> elements in " << filename << std::endl;
      return ReadFileStatus::TOO_MANY_ITEMS;
    }
  }

  return ReadFileStatus::SUCCESS;
}

// Primary template implementation
template <std::size_t N>
ReadFileStatus GameData::LoadFromFile(const std::string& filename, std::array<std::string, N>& data, std::size_t& count) {
  return ReadFile(filename, data, count);
}

// Specialized template for MAX_RACES
template <>
ReadFileStatus GameData::LoadFromFile<MAX_RACES>(const std::string& filename, std::array<std::string, MAX_RACES>& data, std::size_t& count) {
  return ReadFile("./../races.xml", data, count);
}

// Specialized template for MAX_CLASSES
template <>
ReadFileStatus GameData::LoadFromFile<MAX_CLASSES>(const std::string& filename, std::array<std::string, MAX_CLASSES>& data, std::size_t& count) {
  return ReadFile("./../classes.xml", data, count);
}

// Explicit template instantiation for the specific sizes used in GameData
template ReadFileStatus GameData::LoadFromFile<MAX_RACES>(const std::string&, std::array<std::string, MAX_RACES>&, std::size_t&);
template ReadFileStatus GameData::LoadFromFile<MAX_CLASSES>(const std::string&, std::array<std::string, MAX_CLASSES>&, std::size_t&);
