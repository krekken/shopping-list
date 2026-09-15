#include "ListItemRepository.h"
#include "ProductRepository.h"
class Bootstrap {
public:
  void init() {
    ProductRepository productRepository;
    ShoppingListRepository shoppingListRepository;
    ListItemRepository listItemRepository(productRepository,
                                          shoppingListRepository);

    productRepository.load();
    shoppingListRepository.load();
    listItemRepository.load();
  }
};
