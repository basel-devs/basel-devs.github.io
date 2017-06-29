#ifndef BS_PERSON_HPP
#define BS_PERSON_HPP

#include <string>
#include <vector>
#include <boost/variant.hpp>


namespace bs {

  struct cook {
    int michelin_stars;
  };

  struct dev {
    std::vector<std::string> programming_languages;
  };

  struct secretary {
    std::vector<std::string> spoken_languages;
  };

  struct housekeeper {
    bool can_do_electricity;
    bool can_do_plumbing;
    bool can_garden;
    bool can_wash;
  };

  using job_t = boost::variant<cook, dev, secretary, housekeeper>;
  
  struct person {
    std::string name;
    std::string address;
    int age;
    job_t job;
  };

}

#endif
