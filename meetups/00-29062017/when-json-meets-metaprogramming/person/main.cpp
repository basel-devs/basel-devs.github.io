#include <iostream>

#include <person.hpp>
#include <good_from_json.hpp>

int main(int argc, const char* argv[]) {
  using nlohmann::json;
  using namespace bs;
 
  auto some_input = R"(
  {
    "name" : "Ferran Adrià",
    "address" : "17480 Girona, Spain",
    "age" : 55,
    "job" : {
      "struct" : "bs::cook",
      "michelin_stars" : 3
    }
  }
  )";


  {
    auto p = pre::json::from_json<person>(json::parse(some_input));
    std::cout << "We are looking at " << p.name << " aged of " << p.age << ", increment age ? " << std::endl;
    std::cin >> p.age;

    std::cout << pre::json::to_json(p).dump(2) << std::endl;
  }
  return 0;
}
