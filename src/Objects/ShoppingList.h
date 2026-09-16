#pragma once

#include "src/Objects/Serializable.h"
#include <string>

class ShoppingList : public Serializable {
public:
  std::string name;

  std::vector<std::string> getAsStringVector() override {
    return {std::to_string(id), name};
  }
};
