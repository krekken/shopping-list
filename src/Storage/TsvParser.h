#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

class TsvParser {
public:
  static constexpr std::string_view DATA_FOLDER = "data/";

  static std::vector<std::vector<std::string>> parse(std::string filename) {
    std::vector<std::vector<std::string>> rows;
    std::ifstream filestream(filename);
    std::string line;

    while (std::getline(filestream, line)) {
      rows.push_back(splitLine(line));
    }

    return rows;
  }

  static void write(std::vector<std::vector<std::string>> rows,
                    std::string filename) {
    std::ofstream stream(filename);
    std::string line;

    for (auto &row : rows) {
      stream << joinLine(row) << "\n";
    }
  }

  static std::string joinLine(std::vector<std::string> fields) {
    std::string line;
    for (int i = 0; i < fields.size(); i++) {
      if (i > 0) {
        line += '\t';
      }

      line += fields[i];
    }

    return line;
  }

  static std::vector<std::string> splitLine(const std::string &line) {
    std::vector<std::string> fields;
    std::string field;
    std::istringstream stream(line);
    while (std::getline(stream, field, '\t')) {
      fields.push_back(field);
    }

    return fields;
  }
};
