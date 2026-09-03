#include "../Objects/Product.h"
#include "TsvParser.h"
#include <string_view>
#include <vector>

class ProductRepository {
public:
  static constexpr std::string_view FILENAME = "products.tsv";
  void load();
  void save();
  void upsert();
  Product find(int id);

private:
  std::vector<Product> products;
  Product hydrate(std::vector<std::string>);
};
