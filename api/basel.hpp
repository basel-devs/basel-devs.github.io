#include <string>
#include <list>
#include <iostream>

#include <js/bind.hpp>
#include <xxhr/xxhr.hpp>

#include <nlohmann/json.hpp>

/**
 * \brief The Basel simulation model
 */ 
namespace basel_city {

  /**
   * \brief Represents a basel developer 
   */
  struct dev {
    std::size_t meetup_id;
    std::string name;
  };

  namespace citizens {
    struct devs_tag{};
  };

  /**
   * \brief A type centralizing information of devs.
   */
  struct devs_t {

    //TODO: Authenticate on meetup
    //https://secure.meetup.com/oauth2/authorize?client_id=p2rsgro3qe2gnvp61fap9urid5&response_type=token&redirect_uri=https://basel-devs.github.io 

    auto who() {
      using emscripten::val;
      using nlohmann::json;
      std::string members = val::global("all_members").as<std::string>();

      

      return members;//R"(<div class="ui loader"></div>)";
    }

    auto when() {
      using emscripten::val;
      std::string events= val::global("all_events").as<std::string>();
      return events;//R"(<div class="ui loader"></div>)";
    }

    auto why() {
      return "/* Because API is art. */";
    }

    auto help() {
      return R"(// This is a full-fledged C++14 environment, <a href="api/basel.hpp">Basel API here</a>.)";
    }
  };


  struct basel_t {

    devs_t devs;
    devs_t& operator[] (const citizens::devs_tag) {
      return devs;
    }

  };


  constexpr citizens::devs_tag devs;

}

std::string run_user_cmd() {
  using namespace basel_city;
  basel_t basel;

  auto results = {{cmd}}
  ; // <- for those who forgot it too often

  return results;
}

EMSCRIPTEN_BINDINGS(fpb) {
  emscripten::function("run_user_cmd", &run_user_cmd);
}


