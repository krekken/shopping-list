#pragma once

#include <string>
#include <vector>

class Serializable {
public:
  int id;
  virtual std::vector<std::string> getAsStringVector() = 0;
};
