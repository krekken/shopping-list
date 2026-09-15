#pragma once

#include "src/Objects/Product.h"
#include "src/Objects/ShoppingList.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class ListItem : public Serializable {
public:
  int id;
  std::weak_ptr<Product> product;
  int quantity;
  std::weak_ptr<ShoppingList> shoppingList;

  std::vector<std::string> getAsStringVector() override {
    auto p = product.lock();
    if (!p) {
      throw std::runtime_error("list item references a deleted product");
    }
    return {std::to_string(id), std::to_string(p->id),
            std::to_string(quantity)};
  }
};
