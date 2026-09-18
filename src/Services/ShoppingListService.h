#pragma once

#include "ListItemRepository.h"
#include "ProductRepository.h"
#include "ShoppingListRepository.h"
#include "src/Objects/Product.h"
#include <string>

class ShoppingListService {
public:
  ShoppingListService(ProductRepository &productRepository,
                      ListItemRepository &listItemRepository,
                      ShoppingListRepository &shoppingListRepository)
      : productRepository(productRepository),
        listItemRepository(listItemRepository),
        shoppingListRepository(shoppingListRepository) {}

  void addOrUpdateItem(int productId, int listId, std::string name,
                       std::string description, int quantity) {
    Product *product;
    if (productId > 0) {
      product = productRepository.update(productId, name, description);
    } else {
      product = productRepository.create(name, description);
    }

    ListItem *existing = listItemRepository.findComposite(product->id, listId);

    if (existing != nullptr) {
      listItemRepository.update(existing->id, quantity);

      return;
    }

    listItemRepository.create(productId, quantity, listId);
  };

private:
  ProductRepository &productRepository;
  ListItemRepository &listItemRepository;
  ShoppingListRepository &shoppingListRepository;
};
