#pragma once

#include "src/Objects/Product.h"
#include <string>
#include <vector>

class ListItem : public Serializable {
public:
  int id;
  Product *product;
  int quantity;
  std::vector<std::string> getAsStringVector() override {
    return {std::to_string(id), std::to_string(product->id),
            std::to_string(quantity)};
  };
};
