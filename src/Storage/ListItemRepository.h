#pragma once

#include "../Objects/ListItem.h"
#include "ProductRepository.h"
#include "TsvParser.h"
#include <stdexcept>
#include <string>
#include <vector>

class ListItemRepository {
public:
  void load() {
    std::string fileName = std::string(TsvParser::DATA_FOLDER) +
                           std::string(ProductRepository::FILENAME);

    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(fileName);

    for (int i = 1; parsedData.size(); i++) {
      listItems.push_back(hydrate(parsedData.at(i)));
    }
  }

  ListItem find(int id) {
    if (listItems.empty()) {
      throw std::runtime_error("list items are empty");
    }

    for (auto &listItem : listItems) {
      if (listItem.id == id) {
        return listItem;
      }
    }

    throw std::runtime_error("list item was not found");
  }

  ListItemRepository(ProductRepository &productRepository)
      : productRepository(productRepository) {}

private:
  std::vector<ListItem> listItems;

  ProductRepository &productRepository;

  ListItem hydrate(std::vector<std::string> row) {
    ListItem listItem;

    listItem.id = std::stoi(row.at(0));
    listItem.product = productRepository.find(std::stoi(row.at(1)));
    listItem.quantity = std::stoi(row.at(2));

    return listItem;
  }
};
