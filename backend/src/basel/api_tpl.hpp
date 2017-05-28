#ifndef BASEL_DEVS_API_TPL_HPP
#define BASEL_DEVS_API_TPL_HPP


namespace basel {

  constexpr auto api_tpl = R"(
#include <string>
#include <list>
#include <iostream>

#include <emscripten/bind.h>

struct dev {
  std::size_t meetup_id;
  std::string name;
};

namespace citizens {
  struct devs_tag{};
};

struct devs_t {
  std::list<dev> all {
    dev{0, "Damien Buhl"},
    dev{1, "Patrick Wieder"}
  };

  std::string help() {
    return "// This is a full-fledged C++14 environment, <a href="api/basel.hpp">Basel API here</a>.";
  }
};


struct basel_t {

  devs_t devs;
  devs_t& operator[] (const citizens::devs_tag) {
    return devs;
  }

};


constexpr citizens::devs_tag devs;

std::string run_user_cmd() {
  basel_t basel;
  return {{cmd}}
  ;
}

EMSCRIPTEN_BINDINGS(fpb) {
  emscripten::function("run_user_cmd", &run_user_cmd);
}

)";

}

#endif
