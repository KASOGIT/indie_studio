/*
** Thread.hpp for cpp_indie_studio
**
** Made by	Julian Vives
** Login	vives_j
**
** Started on	Sat Jun 04 01:18:58 2016 Julian Vives
** Last update	Sat Jun 04 14:32:09 2016 Julian Vives
*/

#ifndef _THREAD_HPP_
# define _THREAD_HPP_

# include <thread>
# include <functional>
# include <iostream>
# include "Mutex.hpp"

namespace bm {
  /**
   * @brief		Thread encapsulation of std::thread.
   * You can choose if you want to lock/unlock during the execution or not.
   */
  class			Thread {
  private:
    std::thread			_thread;
    Mutex						_mutex;
    bool            _haveToLock;
  public:
    template <class Fn, class... Args>
    explicit  Thread(Fn &&fn, Args&&... args)
    {
        _thread = std::thread(std::forward<Fn>(fn),
        std::forward<Args>(args)...);
	_haveToLock = false;
    }
    Thread() {
      _haveToLock = false;
    }

    ~Thread() {
      if (_thread.joinable())
        _thread.detach();
    }

    /**
     * @brief	  Locks, joins the thread and unlocks.
     * @return void
     */
     void					launch() {
       if (_haveToLock)
        _mutex.lock();
       _thread.join();
       if (_haveToLock)
         _mutex.unlock();
     }

     void					haveToLock(bool lock) {
       _haveToLock = lock;
     }
    /**
     * @brief   Sets function pointer and its arguments. Templated.
     * @param		Function pointer
     * @param		Arguments
     * @return	void
     */
    template <class Fn, class... Args>
    void	setFunctionToExecute(Fn &&fn, Args&&... args) {
      _thread = std::thread(std::forward<Fn>(fn),
      std::forward<Args>(args)...);
    }
  };
};
#endif
