#ifndef BS_BAD_FROM_JSON_HPP
#define BS_BAD_FROM_JSON_HPP

#include <nlohmann/json.hpp>

#include <person.hpp>

namespace bs {
  using nlohmann::json;

  inline person from_json(const json& j) {
    person p;
    p.name = j.at("name").get<std::string>();
    p.address = j.at("address").get<std::string>();
    p.age = j.at("age").get<int>();

    if (j["job"]["struct"].get<std::string>() == "bs::dev") {
      auto job = dev{};

      for (auto e : j["job"]["programming_languages"]) {
        job.programming_languages.push_back(e.get<std::string>());
      }

      p.job = job;

    } else if (j["job"]["struct"].get<std::string>() == "bs::secretary") {
      auto job = secretary{};

      for (auto e : j["job"]["spoken_languages"]) {
        job.spoken_languages.push_back(e.get<std::string>());
      }

      p.job = job;

    } else if (j["job"]["struct"].get<std::string>() == "bs::cook") {
      auto job = cook{};
      job.michelin_stars = j["job"]["michelin_stars"].get<int>();
      p.job = job;
    }

    return p;
  }


}

#endif
