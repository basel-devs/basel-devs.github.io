#include <iostream>
#include <functional>
#include <fstream>

#include <mstch/mstch.hpp>
// express-cpp
#include <application/application.hpp>

#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <boost/scope_exit.hpp>

#include <basel/api_tpl.hpp>
#include <basel/url_escape.hpp>

namespace bp = boost::process;
namespace bf = boost::filesystem;
//using fmt = boost::format;

int main(int argc, char** argv) {
  express::application rest_api;

  struct handle_cmd {

    handle_cmd() {}
     
    void operator()(express::request req, express::response res) {
      res.append("Access-Control-Allow-Origin", "*"); 

      auto cmd = basel::url_unescape(req.query["cmd"]);

      std::string api_view{basel::api_tpl};
      mstch::config::escape = [](const std::string& str) { return str; };
      mstch::map context{
        {"cmd", cmd}
      };
      
      //TODO: Compile cmd to js
      auto temp_code_path = bf::unique_path().replace_extension(".cpp");
      auto temp_js_path = bf::unique_path().replace_extension(".js");
      
      BOOST_SCOPE_EXIT(&temp_code_path, &temp_js_path) {
        // Cleanup created temp files
        boost::system::error_code dontcare;
        if (bf::exists(temp_code_path)) { bf::remove(temp_code_path, dontcare); }
        if (bf::exists(temp_js_path)) { bf::remove(temp_js_path, dontcare); }
      } BOOST_SCOPE_EXIT_END

      std::ofstream ofscpp{temp_code_path.native().data()};
      ofscpp << mstch::render(api_view, context);
      ofscpp.close();

      bp::ipstream err;
      bp::child compiler(bp::shell, "em++", 
        "--std=c++14",
        "--bind",
        temp_code_path.native(),
        "-o",
        temp_js_path.native(),
        bp::std_err > err);

      std::string compiler_out(std::istreambuf_iterator<char>{err}, std::istreambuf_iterator<char>{});

      std::cout << compiler_out << std::endl;

//      std::ifstream ifsjs{temp_js_path.native().data()};
//      std::string jscode(std::istreambuf_iterator<char>{ifsjs}, std::istreambuf_iterator<char>{});

      res.sendFile(temp_js_path);
    }

  };

  rest_api.get("/command", handle_cmd{});

  rest_api.default_("index.html");
  rest_api.static_("./");
  rest_api.listen(std::atoi(argv[1]));

  return 0;
}
