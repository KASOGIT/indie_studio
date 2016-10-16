//
// Particle.cpp for  in /home/rascol_b/KJ/cpp_indie_studio
// 
// Made by benjamin rascol
// Login   <rascol_b@epitech.net>
// 
// Started on  Thu Jun  2 22:49:54 2016 benjamin rascol
// Last update Sun Jun  5 10:55:16 2016 Manuel Trambert

#include "Particle.hpp"

bm::Particle::Particle(const irr::core::vector3df &direction, unsigned int min, unsigned int max,
		       const irr::core::vector3df &pos, const bm::Game &info, int Range)
{
  _timer = std::chrono::system_clock::now();
  _particleSystem = info.getScene()->addParticleSystemSceneNode(false);
  _emitter =
    _particleSystem->createBoxEmitter(irr::core::aabbox3d<irr::f32>(pos.X - 5, -2.5, pos.Z - 5, pos.X + 5, 2.5, pos.Z + 5),
				      direction, min, max,
				      irr::video::SColor(0,0,0,0),
				      irr::video::SColor(0,255,255,255),
				      200 * (Range - 1), 220 * (Range - 1), 0,
				      irr::core::dimension2df(5, 5),
				      irr::core::dimension2df(6, 6));
  _particleSystem->setEmitter(_emitter);
  _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, true);
  _particleSystem->setMaterialTexture(0, info.getDriver()->getTexture("lib/irrlicht-1.8.3/media/fire.bmp"));
  _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

bm::Particle::~Particle()
{

}

irr::scene::IParticleSystemSceneNode                *bm::Particle::getParticle() const
{
  return (_particleSystem);
}

irr::scene::IParticleEmitter			*bm::Particle::getEmitter() const
{
  return (_emitter);
}

std::chrono::time_point<std::chrono::system_clock>	bm::Particle::getTimer() const
{
  return (_timer);
}

irr::scene::IParticleSystemSceneNode		*bm::Particle::getSystem() const
{
  return (_particleSystem);
}
