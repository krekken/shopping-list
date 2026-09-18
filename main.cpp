#include "ListItemRepository.h"
#include "ProductRepository.h"
#include "ShoppingListRepository.h"
#include "src/Services/ShoppingListService.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  ProductRepository productRepository;
  ShoppingListRepository shoppingListRepository;
  ListItemRepository listItemRepository(productRepository,
                                        shoppingListRepository);
  productRepository.load();
  shoppingListRepository.load();
  listItemRepository.load();

  ShoppingListService shoppingListService(productRepository, listItemRepository,
                                          shoppingListRepository);

  return 0;
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("ShoppingList", "Main");

  return QGuiApplication::exec();
}
