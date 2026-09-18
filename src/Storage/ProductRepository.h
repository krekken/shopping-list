#pragma once

#include "../Objects/Product.h"
#include "Repository.h"
#include "TsvParser.h"
#include "src/Objects/Serializable.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class ProductRepository : public Repository {
public:
  void create(std::string name, std::string description) {
    std::shared_ptr<Product> product =
        hydrate({std::to_string(getAutoIncrement()), name, description});

    products.push_back(product);
  }

  void deleteItem(int id) override {
    auto iterator = std::find_if(
        products.begin(), products.end(),
        [id](const std::shared_ptr<Product> &p) { return p->id == id; });
    if (iterator == products.end()) {
      throw std::runtime_error("product couldn't be found");
    }
    products.erase(iterator);
  }

  std::vector<std::string> headers = {"id", "name", "description"};

  void load() override {
    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(getPath());

    for (size_t i = 1; i < parsedData.size(); ++i) {
      products.push_back(hydrate(parsedData[i]));
    }

    loaded = true;
  }

  Product *find(int id) override {
    for (auto &product : products) {
      if (product->id == id) {
        return product.get();
      }
    }
    throw std::runtime_error("product couldn't be found");
  }

  std::shared_ptr<Product> findShared(int id) {
    for (auto &product : products) {
      if (product->id == id) {
        return product;
      }
    }
    throw std::runtime_error("product couldn't be found");
  }

protected:
  std::string_view getFilename() const override { return "products.tsv"; };
  std::vector<std::string> getHeaders() override {
    return {"id", "name", "description"};
  };

  std::vector<std::shared_ptr<Serializable>> getReposedObjects() override {
    std::vector<std::shared_ptr<Serializable>> items;

    for (auto &product : products) {
      items.push_back(product);
    }

    return items;
  }

private:
  std::vector<std::shared_ptr<Product>> products;

  std::shared_ptr<Product> hydrate(std::vector<std::string> row) {
    auto product = std::make_shared<Product>();
    product->id = std::stoi(row.at(0));
    product->name = row.at(1);
    product->description = row.at(2);
    product->image = "";

    return product;
  }
};
