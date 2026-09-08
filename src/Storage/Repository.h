#pragma once

#include <string>
#include <string_view>
#include <vector>

class Repository {
public:
  virtual ~Repository() = default;

protected:
  virtual std::vector<std::string> getHeaders();
  virtual std::string_view getFilename() const = 0;
};
