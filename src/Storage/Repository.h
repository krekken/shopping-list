#pragma once

#include "TsvParser.h"
#include "src/Objects/Serializable.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class Repository {
public:
  virtual ~Repository() = default;
  virtual void load() = 0;
  virtual Serializable *find(int id) = 0;

  void save() {
    std::vector<std::shared_ptr<Serializable>> objects = getReposedObjects();
    std::vector<std::vector<std::string>> rows;

    if (objects.empty()) {
      throw std::runtime_error("No objects");
    }

    rows.push_back(getHeaders());

    for (int i = 0; i < objects.size(); i++) {
      const std::vector<std::string> line = objects.at(i)->getAsStringVector();
      rows.push_back(line);
    }

    TsvParser::write(rows, std::string(TsvParser::DATA_FOLDER) +
                               std::string(getFilename()));
  };
  virtual void deleteItem(int id) = 0;
  virtual bool isLoaded() { return loaded; };

protected:
  virtual std::string_view getFilename() const = 0;
  std::string getPath() {
    return std::string(std::string(TsvParser::DATA_FOLDER) +
                       std::string(getFilename()));
  }
  virtual std::vector<std::string> getHeaders() = 0;
  virtual std::vector<std::shared_ptr<Serializable>> getReposedObjects() = 0;

  int getAutoIncrement() {
    std::vector<std::shared_ptr<Serializable>> objects = getReposedObjects();
    if (objects.empty()) {
      return 1;
    }

    int autoIncrement = 0;

    for (auto &object : objects) {
      autoIncrement = std::max(autoIncrement, object->id);
    }

    autoIncrement++;

    return autoIncrement;
  }
  bool loaded = false;
};
