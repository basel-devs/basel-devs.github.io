#ifndef BASEL_DETAIL_HELP_HPP
#define BASEL_DETAIL_HELP_HPP

#include <sstream>
#include <xxhr/xxhr.hpp>
#include <js/htmlencode.hpp>

auto basel::devs_t::help() const {

  using namespace xxhr;

  GET( 
    Url{"https://raw.githubusercontent.com/basel-devs/"
        "basel-devs.github.io/master/api/basel/basel.hpp"}, 
    on_response = [](auto&& resp) {

      using emscripten::val;

      std::string cmd_result = "#cmd_result";
      if (resp.status_code == 200) { 

        std::stringstream html_help;

        html_help <<
          R"(<h1>This is a full <span style="color:green">C++14</span> environment : compile as you type...</h1>
             <pre><code id="help_api" class="cpp hljs">)"
          << js::htmlencode(resp.text) << 
          R"(</code></pre>)"
        ;
        
        val::global("$")(cmd_result).call<val>("html", html_help.str());
        val dom_help_api = val::global("$")(std::string("#help_api")).call<val>("get", 0);

        val::global("hljs").call<val>("highlightBlock", dom_help_api);
      } else {
        val::global("$")(cmd_result).call<val>("html", std::string{R"(<span style="color:red;">Error Loading Resource</span>)"});
      }
    }
  );

  return R"(
  <div class="ui icon message massive">
    <i class="notched circle loading icon"></i>
    <div class="content">
      <div class="header">
        Please wait 
      </div>
      <p>Retrieving the C++ API.</p>
    </div>
  </div>
  )";
}

#endif
