#ifndef BASEL_DETAIL_IMPL_HPP
#define BASEL_DETAIL_IMPL_HPP

#include <sstream>

#include <js/bind.hpp>
#include <js/string.hpp>

#include <nlohmann/json.hpp>

auto basel::devs_t::who() const {
  using emscripten::val;
  using nlohmann::json;

  auto members = js::to_string(val::global("all_members"));
  
  json o;
  o = json::parse(members);

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

auto basel::devs_t::when() const {
    using emscripten::val;
    using nlohmann::json;

    auto events = js::to_string(val::global("all_events"));

    json o;
    o = json::parse(events);

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

#endif
