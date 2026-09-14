#pragma once

#include "src/Objects/ListItem.h"
#include <string>
#include <vector>

class ShoppingList {
public:
  int id;
  std::string name;
  std::vector<ListItem *> listItems;
};
