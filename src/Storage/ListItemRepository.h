#pragma once

#include "../Objects/ListItem.h"
#include "ProductRepository.h"
#include "SerializableRepository.h"
#include "TsvParser.h"
#include <stdexcept>
#include <string>
#include <vector>

class ListItemRepository : public SerializableRepository {
public:
  void load() override {
    std::string fileName =
        std::string(TsvParser::DATA_FOLDER) + std::string(getFilename());

    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(fileName);

    if (!productRepository.isLoaded()) {
      productRepository.load();
    }

    for (int i = 1; i < parsedData.size(); i++) {
      listItems.push_back(hydrate(parsedData.at(i)));
    }

    loaded = true;
  }

  ListItem *find(int id) {
    if (listItems.empty()) {
      throw std::runtime_error("list items are empty");
    }

    for (auto &listItem : listItems) {
      if (listItem.id == id) {
        return &listItem;
      }
    }

    throw std::runtime_error("list item was not found");
  }

  ListItemRepository(ProductRepository &productRepository)
      : productRepository(productRepository) {}

protected:
  std::string_view getFilename() const override { return "list_items.tsv"; };
  std::vector<std::string> getHeaders() override {
    return {"id", "id_product", "quantity"};
  };

  std::vector<Serializable *> getReposedObjects() override {
    std::vector<Serializable *> items;
    for (auto &listItem : listItems) {
      items.push_back(&listItem);
    }
    return items;
  };

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
