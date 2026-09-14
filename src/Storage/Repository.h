#pragma once

#include <string>
#include <string_view>
#include <vector>

class Repository {
public:
  virtual ~Repository() = default;
  virtual void load() = 0;
  virtual bool isLoaded() { return loaded; };

protected:
  virtual std::vector<std::string> getHeaders() = 0;
  virtual std::string_view getFilename() const = 0;
  bool loaded = false;
};
