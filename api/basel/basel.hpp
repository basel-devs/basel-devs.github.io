#ifndef BASEL_BASEL_HPP
#define BASEL_BASEL_HPP

/**
 * \brief The Basel simulation model
 */ 
namespace basel {

  namespace citizens {
    struct devs_tag{};
  };

  /**
   * An constant to select the devs
   */
  constexpr citizens::devs_tag devs;

  /**
   * \brief A type centralizing information for basel[devs].
   */
  struct devs_t {

    /**
     * \brief Query the meetup API to get all members
     * \return all basel[devs] out there.
     */
    auto who() const; 

    /**
     * \brief Query the meetup API to get the events planned
     * \return the basel[devs] events to happen.
     */
    auto when() const;

    /**
     * \brief Gives some hints.
     */
    auto why() const;

    /**
     * \return This API description.
     */
    auto help() const;
  };


  struct basel_t {
    devs_t& operator[] (const citizens::devs_tag) { return devs_storage; }
    private:
    devs_t devs_storage{};
  };


}

#include <basel/detail/impl.hpp>
#include <basel/detail/help.hpp>

#endif
