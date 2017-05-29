#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <locale>
#include <codecvt> 

#include <js/bind.hpp>
#include <xxhr/xxhr.hpp>

#include <nlohmann/json.hpp>


/**
 * \brief The Basel simulation model
 */ 
namespace basel_city {

  namespace citizens {
    struct devs_tag{};
  };

  /**
   * \brief A type centralizing information for basel[devs].
   */
  struct devs_t {

    auto who() {
      using emscripten::val;
      using nlohmann::json;

      std::wstring string_to_convert = val::global("all_members").as<std::wstring>();
      
      using convert_type = std::codecvt_utf8<wchar_t>;
      std::wstring_convert<convert_type, wchar_t> converter;
      std::string members = converter.to_bytes( string_to_convert );

      json o;
      try {
        o = json::parse(members);
        std::cout << "PARSED "<< std::endl;
      } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
      }

      std::stringstream response_html;
      response_html << R"(
      <div class="ui cards">
      )";

      for (auto& member : o["data"]) {
        std::string img_src = (member["photo"]["thumb_link"].is_null()) ? "" : member["photo"]["thumb_link"]; 
        response_html << 
          R"(
            <div class="card">
              <div class="content">
                <div class="header">
                  <img class="ui avatar image" src=")" << img_src << R"(">
                  <span>)" << member["name"].get<std::string>() << R"(</span> 
                </div>
                <div class="meta">
                  )" << member["city"].get<std::string>() << R"(
                </div>
              </div>
            </div>
            )";
      }

      response_html << R"(
      </div>)";

      return response_html.str();
    }

    auto when() {
      using emscripten::val;
      using nlohmann::json;

      std::wstring string_to_convert = val::global("all_events").as<std::wstring>();
      
      using convert_type = std::codecvt_utf8<wchar_t>;
      std::wstring_convert<convert_type, wchar_t> converter;
      std::string events = converter.to_bytes( string_to_convert );

      json o;
      try {
        o = json::parse(events);
      } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
      }

      std::stringstream response_html;
      response_html << R"(
      <div class="ui cards">
      )";

      for (auto& event : o["data"]) {

        response_html << 
          R"(
            <div class="card">
              <div class="content">
                <div class="header">
                  )" << event["name"].get<std::string>() << R"(
                </div>
                <div class="meta">
                </div>
                <div class="description">
                  <a href=")" << event["link"].get<std::string>() << R"(" target="_blank">When &amp; Where ?</a>
                </div>
              </div>
              <div class="extra content">
                <i class="user icon"></i>
                )" << event["yes_rsvp_count"].get<int>() << R"( Going
              </div>
            </div>
            )";
      }

      response_html << R"(
      </div>)";

      return response_html.str();
    }

    auto why() {
      return "/* Because API is art. */";
    }

    auto help() {
      return R"(// This is a full-fledged <span style="color: green;">C++14</span> environment, <a href="api/basel.hpp">Basel API here</a>.)";
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
  ; // <- for those who forget it too often

  return results;
}

EMSCRIPTEN_BINDINGS(fpb) {
  emscripten::function("run_user_cmd", &run_user_cmd);
}


