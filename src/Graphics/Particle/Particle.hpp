//
// Particle.hpp for  in /home/rascol_b/KJ/cpp_indie_studio
// 
// Made by benjamin rascol
// Login   <rascol_b@epitech.net>
// 
// Started on  Thu Jun  2 22:48:30 2016 benjamin rascol
// Last update Sun Jun  5 10:55:18 2016 Manuel Trambert
//

#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

#include <chrono>
#include <irrlicht.h>
#include "Game.hpp"
#include "Bomb.hpp"

namespace bm
{
  class Particle
  {
  public:
    Particle(const irr::core::vector3df &direction, unsigned int min, unsigned int max,
	     const irr::core::vector3df &pos, const bm::Game &, int Range);
    ~Particle();
    irr::scene::IParticleEmitter			*getEmitter() const;
    irr::scene::IParticleSystemSceneNode		*getSystem() const;
    std::chrono::time_point<std::chrono::system_clock>	getTimer() const;
    irr::scene::IParticleSystemSceneNode		*getParticle() const;
  private:
    irr::scene::IParticleEmitter			*_emitter;
    irr::scene::IParticleSystemSceneNode		*_particleSystem;
    std::chrono::time_point<std::chrono::system_clock>	_timer;
  };
};

#endif /* !PARTICLE_HPP_ */
