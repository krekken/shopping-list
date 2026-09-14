#pragma once

#include "../Objects/Product.h"
#include "SerializableRepository.h"
#include "TsvParser.h"
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class ProductRepository : public SerializableRepository {
public:
  std::vector<std::string> headers = {"id", "name", "description"};

  void load() override {
    std::string filename =
        std::string(TsvParser::DATA_FOLDER) + std::string(getFilename());
    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(filename);

    for (size_t i = 1; i < parsedData.size(); ++i) {
      products.push_back(hydrate(parsedData[i]));
    }

    loaded = true;
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

protected:
  std::string_view getFilename() const override { return "products.tsv"; };
  std::vector<std::string> getHeaders() override {
    return {"id", "name", "description"};
  };

  std::vector<Serializable *> getReposedObjects() override {
    std::vector<Serializable *> items;
    for (auto &product : products) {
      items.push_back(&product);
    }

    return items;
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
