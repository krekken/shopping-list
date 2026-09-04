#include "src/Objects/ListItem.h"
#include <vector>

struct ShoppingList {
  int id;
  std::vector<ListItem> listItems;
};
