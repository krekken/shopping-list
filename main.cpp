#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <cstdio>

int main(int argc, char *argv[]) {
  printf("hello world\n");
  return 0;
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("ShoppingList", "Main");

  return QGuiApplication::exec();
}
