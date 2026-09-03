#include "TsvParser.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<std::string>> TsvParser::parse(std::string filename) {
  std::vector<std::vector<std::string>> rows;
  std::ifstream filestream(filename);
  std::string line;

  while (std::getline(filestream, line)) {
    rows.push_back(splitLine(line));
  }

  return rows;
};

std::vector<std::string> TsvParser::splitLine(const std::string &line) {
  std::vector<std::string> fields;
  std::string field;
  std::istringstream stream(line);
  while (std::getline(stream, field, '\t')) {
    fields.push_back(field);
  }

  return fields;
};
