#include "ListItemRepository.h"
#include "src/Storage/ShoppingListRepository.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  ProductRepository pRep;
  ListItemRepository liRep(pRep);
  ShoppingListRepository slRep(liRep);

  slRep.load();
  return 0;
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("ShoppingList", "Main");

  return QGuiApplication::exec();
}
