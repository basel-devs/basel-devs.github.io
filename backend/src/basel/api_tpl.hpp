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
    return "This is a full-fledge C++14 environment, <a href="">API here</a>.";
  }
};


struct basel_t {

  devs_t devs;
  const devs_t operator[] (const citizens::devs_tag) const {
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
