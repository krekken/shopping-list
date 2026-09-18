#pragma once

#include "../Objects/ShoppingList.h"
#include "Repository.h"
#include "TsvParser.h"
#include "src/Objects/Serializable.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class ShoppingListRepository : public Repository {
public:
  void deleteItem(int id) override {
    auto iterator =
        std::find_if(shoppingLists.begin(), shoppingLists.end(),
                     [id](const std::shared_ptr<ShoppingList> shoppingList) {
                       return shoppingList->id == id;
                     });

    if (iterator == shoppingLists.end()) {
      throw std::runtime_error("item could not be found");
    }

    shoppingLists.erase(iterator);
  }

  void load() override {
    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(getPath());

    for (int i = 1; i < parsedData.size(); i++) {
      shoppingLists.push_back(hydrate(parsedData, i));
    }

    loaded = true;
  };

  ShoppingList *find(int id) override {
    if (shoppingLists.empty()) {
      throw std::runtime_error("list items are empty");
    }

    for (auto &listItem : shoppingLists) {
      if (listItem->id == id) {
        return listItem.get();
      }
    }

    throw std::runtime_error("shopping list was not found");
  }

  std::shared_ptr<ShoppingList> findShared(int id) {
    if (shoppingLists.empty()) {
      throw std::runtime_error("shopping list are empty");
    }

    for (auto &listItem : shoppingLists) {
      if (listItem->id == id) {
        return listItem;
      }
    }

    throw std::runtime_error("shopping list was not found");
  }

protected:
  std::vector<std::shared_ptr<Serializable>> getReposedObjects() override {
    std::vector<std::shared_ptr<Serializable>> items;

    for (auto &shoppingList : shoppingLists) {
      items.push_back(shoppingList);
    }

    return items;
  }

  std::string_view getFilename() const override {
    return "shopping_lists.tsv";
  };

  std::vector<std::string> getHeaders() override { return {"id", "name"}; }

private:
  std::vector<std::shared_ptr<ShoppingList>> shoppingLists;

  std::shared_ptr<ShoppingList>
  hydrate(std::vector<std::vector<std::string>> &parsedData, int &i) {
    auto &row = parsedData[i];
    int listId = std::stoi(row.at(0));

    auto shoppingList = std::make_shared<ShoppingList>();

    shoppingList->id = std::stoi(row.at(0));
    shoppingList->name = row.at(1);

    return shoppingList;
  }
};
