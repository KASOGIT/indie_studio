/*
** Mutex.hpp for cpp_indie_studio
**
** Made by	Julian Vives
** Login	vives_j
**
** Started on	Sat Jun 04 02:23:12 2016 Julian Vives
** Last update	Sat Jun 04 02:24:16 2016 Julian Vives
*/

#ifndef _MUTEX_HPP
# define _MUTEX_HPP

#include <mutex>

namespace bm {
  class			Mutex : public std::mutex {
  public:
    virtual	~Mutex();
  };
};
#endif
