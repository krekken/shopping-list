#include <string>
#include <string_view>
#include <vector>

class TsvParser {
public:
  static constexpr std::string_view DATA_FOLDER = "data/";
  static std::vector<std::vector<std::string>> parse(std::string filename);
  static std::vector<std::string> splitLine(const std::string &line);
};
