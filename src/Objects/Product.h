#pragma once

#include "src/Objects/Serializable.h"
#include <string>
#include <vector>

class Product : public Serializable {
public:
  std::string name;
  std::string description;
  std::string image; // unused for now

  std::vector<std::string> getAsStringVector() override {
    return {std::to_string(id), name, description};
  };
};
