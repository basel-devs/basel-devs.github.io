#include <iostream>
#include <functional>
#include <fstream>

#include <boost/algorithm/string/trim.hpp>
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
namespace ba = boost::algorithm;

constexpr auto CACHE_PATH = "cache";

int main(int argc, char** argv) {
  express::application rest_api;

  struct handle_cmd {

    bf::path cache_path_for(const std::string& cmd) {
      bf::path cache_file(CACHE_PATH); 
      cache_file /= std::to_string(std::hash<std::string>()(cmd)) + ".js";
      return cache_file;
    }

    handle_cmd() {
      bf::create_directories(CACHE_PATH);
    }
     
    void operator()(express::request req, express::response res) {
      res.append("Access-Control-Allow-Origin", "*"); 

      auto cmd = ba::trim_copy(basel::url_unescape(req.query["cmd"]));

      auto cache_file = cache_path_for(cmd);
      if (bf::exists(cache_file)) {
        std::cout << "Cache hit for " << cmd << std::endl;
        res.sendFile(cache_file);
      } else {
        std::cout << "Compiling " << cmd << std::endl;

        std::ifstream ifs_api{"api/basel.hpp"};
        std::string api_view(std::istreambuf_iterator<char>{ifs_api}, std::istreambuf_iterator<char>{});
        mstch::config::escape = [](const std::string& str) { return str; };
        mstch::map context{
          {"cmd", cmd}
        };
        
        auto temp_code_path = bf::unique_path().replace_extension(".cpp");
        
        BOOST_SCOPE_EXIT(&temp_code_path) {
          // Cleanup created temp files
          boost::system::error_code dontcare;
          if (bf::exists(temp_code_path)) { bf::remove(temp_code_path, dontcare); }
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
          cache_file.native(),
          "-Iapi/",
          "-Iapi/xxhr/deps",
          bp::std_err > err);

        std::string compiler_out(std::istreambuf_iterator<char>{err}, std::istreambuf_iterator<char>{});
        compiler.wait();

        std::cout << "Compiler said : " << compiler.exit_code() << " -- " << compiler_out << std::endl;

        using express::http_status;
        if (!bf::exists(cache_file)) {
          res.send(http_status::http_not_found, compiler_out);
        } else {
          res.sendFile(cache_file);
        }
      }
    }

  };

  rest_api.get("/command", handle_cmd{});

  rest_api.default_("index.html");
  rest_api.static_("./");
  rest_api.listen(std::atoi(argv[1]));

  return 0;
}
