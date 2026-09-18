#pragma once

#include "ProductRepository.h"
#include "Repository.h"
#include "ShoppingListRepository.h"
#include "TsvParser.h"
#include "src/Objects/ListItem.h"
#include "src/Objects/Serializable.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class ListItemRepository : public Repository {
public:
  ListItemRepository(ProductRepository &productRepository,
                     ShoppingListRepository &shoppingListRepository)
      : productRepository(productRepository),
        shoppingListRepository(shoppingListRepository) {}

  void deleteItem(int id) override {
    auto iterator =
        std::find_if(listItems.begin(), listItems.end(),
                     [id](const std::shared_ptr<ListItem> listItem) {
                       return listItem->id == id;
                     });
    if (iterator == listItems.end()) {
      throw std::runtime_error("item could not be found");
    }

    listItems.erase(iterator);
  }

  void load() override {
    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(getPath());

    if (!productRepository.isLoaded()) {
      productRepository.load();
    }

    if (!shoppingListRepository.isLoaded()) {
      shoppingListRepository.load();
    }

    for (int i = 1; i < parsedData.size(); i++) {
      listItems.push_back(hydrate(parsedData.at(i)));
    }

    loaded = true;
  }

  ListItem *find(int id) override {
    if (listItems.empty()) {
      throw std::runtime_error("list items are empty");
    }

    for (auto &listItem : listItems) {
      if (listItem->id == id) {
        return listItem.get();
      }
    }

    throw std::runtime_error("list item was not found");
  }

  std::shared_ptr<ListItem> findShared(int id) {
    if (listItems.empty()) {
      throw std::runtime_error("list items are empty");
    }

    for (auto &listItem : listItems) {
      if (listItem->id == id) {
        return listItem;
      }
    }

    throw std::runtime_error("list item was not found");
  }

  std::vector<ListItem *> findForList(int listId) {
    if (listItems.empty()) {
      throw std::runtime_error("list items are empty");
    }

    std::vector<ListItem *> filteredListItems;

    for (auto &listItem : listItems) {
      if (listItem->shoppingList.lock()->id == listId) {
        filteredListItems.push_back(listItem.get());
      }
    }

    return filteredListItems;
  };

protected:
  std::string_view getFilename() const override { return "list_items.tsv"; };
  std::vector<std::string> getHeaders() override {
    return {"id", "id_product", "quantity", "id_shopping_list"};
  };

  std::vector<std::shared_ptr<Serializable>> getReposedObjects() override {
    std::vector<std::shared_ptr<Serializable>> items;

    for (auto &listItem : listItems) {
      items.push_back(listItem);
    }

    return items;
  };

private:
  std::vector<std::shared_ptr<ListItem>> listItems;

  ProductRepository &productRepository;
  ShoppingListRepository &shoppingListRepository;

  std::shared_ptr<ListItem> hydrate(std::vector<std::string> row) {
    auto listItem = std::make_shared<ListItem>();

    listItem->id = std::stoi(row.at(0));
    listItem->product = productRepository.findShared(std::stoi(row.at(1)));
    listItem->quantity = std::stoi(row.at(2));
    listItem->shoppingList =
        shoppingListRepository.findShared(std::stoi(row.at(3)));

    return listItem;
  }

  ListItem *findComposite(int productId, int listId) {
    for (auto &listItem : listItems) {
      if (listItem->product.lock()->id == productId &&
          listItem->shoppingList.lock()->id == listId) {
        return listItem.get();
      }
    }

    return nullptr;
  }
};
