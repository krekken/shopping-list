#include "../Objects/ShoppingList.h"
#include "ListItemRepository.h"
#include "TsvParser.h"
#include "src/Objects/ListItem.h"
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class ShoppingListRepository {
public:
  static constexpr std::string_view FILENAME = "shopping_lists.tsv";

  void load() {
    std::string filename =
        std::string(TsvParser::DATA_FOLDER) + std::string(FILENAME);
    std::unordered_map<int, ShoppingList> byId;

    std::vector<std::vector<std::string>> parsedData =
        TsvParser::parse(filename);

    for (int i = 1; parsedData.size(); i++) {
      hydrate(byId, parsedData, i);
    }

    for (auto &[id, loadedList] : byId) {
      shoppingLists.push_back(loadedList);
    }
  };
  ShoppingListRepository(ListItemRepository &listItemRepoistory)
      : listItemRepository(listItemRepoistory) {}

private:
  std::vector<ShoppingList> shoppingLists;

  ListItemRepository listItemRepository;

  void hydrate(std::unordered_map<int, ShoppingList> &byId,
               std::vector<std::vector<std::string>> &parsedData, int &i) {
    auto &row = parsedData[i];
    int listId = std::stoi(row.at(0));
    ShoppingList &shoppingList = byId[listId];
    ListItem listItem = listItemRepository.find(std::stoi(row.at(1)));

    shoppingList.listItems.push_back(listItem);
  }
};
