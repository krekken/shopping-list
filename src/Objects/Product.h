#pragma once
#include "src/Objects/Serializable.h"
#include <string>
#include <vector>

class Product : public Serializable {
public:
  int id;
  std::string name;
  std::string description;
  std::string image; // unused for now
  std::vector<std::string> getAsStringVector() override {
    return {"id", "name", "description"};
  };
};
