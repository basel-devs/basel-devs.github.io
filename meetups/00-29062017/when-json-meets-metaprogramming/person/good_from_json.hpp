#ifndef BS_GOOD_FROM_JSON_HPP
#define BS_GOOD_FROM_JSON_HPP

#include <pre/json/from_json.hpp>
#include <pre/json/to_json.hpp>

BOOST_FUSION_ADAPT_STRUCT(bs::cook, michelin_stars)
BOOST_FUSION_ADAPT_STRUCT(bs::dev, programming_languages)
BOOST_FUSION_ADAPT_STRUCT(bs::secretary, spoken_languages)

BOOST_FUSION_ADAPT_STRUCT(bs::housekeeper, can_do_electricity, can_do_plumbing, can_garden, can_wash)

BOOST_FUSION_ADAPT_STRUCT(bs::person, name, address, age, job)

#endif
