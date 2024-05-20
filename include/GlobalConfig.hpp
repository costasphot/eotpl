// config.hpp
// Configuration settings for the Car System

#pragma once

#include <iostream>

namespace GlobalConfig {
  constexpr bool DEVELOPER_MODE = true; // Set it to true for development, false for production
  constexpr bool CONFIDENTIAL_OVERRIDE = false; // Might contain sensitive information (often present in destructor messages)
}
