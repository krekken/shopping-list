#include "ProductRepository.h"
#include <stdexcept>
#include <string>
#include <vector>

void ProductRepository::load() {
  std::string filename = std::string(TsvParser::DATA_FOLDER) +
                         std::string(ProductRepository::FILENAME);
  std::vector<std::vector<std::string>> parsedData = TsvParser::parse(filename);

  for (size_t i = 1; i < parsedData.size(); ++i) {
    products.push_back(hydrate(parsedData[i]));
  }
}

Product ProductRepository::find(int id) {
  if (products.empty()) {
    throw std::runtime_error("products are empty");
  }

  for (const auto &product : products) {
    if (product.id == id) {
      return product;
    }
  }

  throw std::runtime_error("product couldn't be found");
};

Product ProductRepository::hydrate(std::vector<std::string> row) {
  Product product;
  product.id = std::stoi(row.at(0));
  product.name = row.at(1);
  product.description = row.at(2);
  product.image = "";

  return product;
}
