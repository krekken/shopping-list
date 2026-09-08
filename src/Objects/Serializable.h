#pragma once

#include <string>
#include <vector>

class Serializable {
public:
  virtual std::vector<std::string> getAsStringVector() = 0;
};
