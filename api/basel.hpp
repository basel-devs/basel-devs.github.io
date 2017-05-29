#ifndef BASEL_HPP
#define BASEL_HPP

#include <string>
#include <basel/basel.hpp>

inline std::string run_user_cmd() {
  using namespace basel;
  basel_t basel;

  auto results = {{cmd}}
  ; // <- for those who forget it too often

  return results;
}

EMSCRIPTEN_BINDINGS(basel_module) {
  emscripten::function("run_user_cmd", &run_user_cmd);
}

#endif
