#pragma once

#include "Repository.h"
#include "TsvParser.h"
#include "src/Objects/Serializable.h"
#include <stdexcept>
#include <string>

class SerializableRepository : public Repository {
public:
  virtual Serializable *find(int id) = 0;

  void save() override {
    std::vector<Serializable *> objects = getReposedObjects();
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

protected:
  virtual std::vector<Serializable *> getReposedObjects() = 0;
};
