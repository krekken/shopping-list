#include "../Objects/ShoppingList.h"
#include "ListItemRepository.h"
#include "Repository.h"
#include "TsvParser.h"
#include "src/Objects/ListItem.h"
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class ShoppingListRepository : public Repository {
public:
  void load() override {
    std::string filename =
        std::string(TsvParser::DATA_FOLDER) + std::string(getFilename());
    std::unordered_map<int, ShoppingList> byId;

    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(filename);

    for (int i = 1; i < parsedData.size(); i++) {
      hydrate(byId, parsedData, i);
    }

    for (auto &[id, loadedList] : byId) {
      shoppingLists.push_back(loadedList);
    }

    loaded = true;
  };

  ShoppingListRepository(ListItemRepository &listItemRepository)
      : listItemRepository(listItemRepository) {}

protected:
  std::string_view getFilename() const override {
    return "shopping_lists.tsv";
  };

  std::vector<std::string> getHeaders() override {
    return {"id", "id_list_item"};
  }

private:
  std::vector<ShoppingList> shoppingLists;

  ListItemRepository &listItemRepository;

  void hydrate(std::unordered_map<int, ShoppingList> &byId,
               std::vector<std::vector<std::string>> &parsedData, int &i) {
    auto &row = parsedData[i];
    int listId = std::stoi(row.at(0));
    ShoppingList &shoppingList = byId[listId];
    if (!listItemRepository.isLoaded()) {
      listItemRepository.load();
    }
    ListItem *listItem = listItemRepository.find(std::stoi(row.at(1)));

    shoppingList.listItems.push_back(listItem);
  }
};
