#pragma once

#include "../Objects/Product.h"
#include "Repository.h"
#include "TsvParser.h"
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class ProductRepository : public Repository {
public:
  static constexpr std::string_view FILENAME = "products.tsv";
  std::vector<std::string> headers = {"id", "name", "description"};

  void load() {
    std::string filename =
        std::string(TsvParser::DATA_FOLDER) + std::string(getFilename());
    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(filename);

    for (size_t i = 1; i < parsedData.size(); ++i) {
      products.push_back(hydrate(parsedData[i]));
    }
  }

  Product *find(int id) {
    if (products.empty()) {
      throw std::runtime_error("products are empty");
    }

    for (auto &product : products) {
      if (product.id == id) {
        return &product;
      }
    }

    throw std::runtime_error("product couldn't be found");
  }

  void save() {
    std::vector<std::vector<std::string>> rows;
    rows.push_back(getHeaders());

    for (const auto &product : products) {
      std::vector<std::string> line = {std::to_string(product.id), product.name,
                                       product.description};
      rows.push_back(line);
    }
  }

protected:
  std::string_view getFilename() const override { return "products.tsv"; };
  std::vector<std::string> getHeaders() override {
    return {"id", "name", "description"};
  };

private:
  std::vector<Product> products;

  Product hydrate(std::vector<std::string> row) {
    Product product;
    product.id = std::stoi(row.at(0));
    product.name = row.at(1);
    product.description = row.at(2);
    product.image = "";

    return product;
  }
};
