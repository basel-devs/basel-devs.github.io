#ifndef BASEL_DEVS_API_TPL_HPP
#define BASEL_DEVS_API_TPL_HPP

#define begin_str() R 

namespace basel {

  constexpr auto api_tpl = R"(
#include <string>
#include <list>
#include <iostream>

struct dev {
  std::size_t meetup_id;
  std::string name;
};

namespace citizens {
  struct devs_tag{};
};


struct basel_t {

  const std::list<dev> operator[] (const citizens::devs_tag) const {
    return {
      dev{0, "Damien Buhl"},
      dev{1, "Patrick Wieder"}
    }; //TODO: Meetup query
  }

};


constexpr citizens::devs_tag devs;

extern "C" void run_user_cmd() {
  basel_t basel;
  {{cmd}}
  ;
}
)";

}

#endif
