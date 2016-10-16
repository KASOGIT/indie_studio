//
// Character.hpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/class/Character
//
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
//
// Started on  Mon May  9 13:16:08 2016 Manuel Trambert
// Last update Sun Jun  5 17:12:00 2016 
//

#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <irrlicht.h>
#include "GameObject.hpp"
#include "Bonus.hpp"
#include "Events.hpp"
#include "Bomb.hpp"
#include "Sound.hpp"

#define SIZE_BLOCK	10

#define	LIFETIME_BONUS	4000
#define ID_BONUS	-500
#define VOL_BOMB	0.2
#define VOL_BONUS	0.2
#define VOL_EXPLO	0.2
#define	VOL_START	0.2

#define BONUS_XP	10
#define KILL_XP		200
#define	XP_UP		5
#define	BONUS_SPEED_UP	10

#define	MAX_LVL		75
#define ANIMATION_SPEED	13

#define DELAY_BOMB	2000

namespace bm {
  class Game;
};

namespace bm {
  class		Character;
};

namespace bm
{
  typedef void (Character::*command_exec)(float, bm::Game*);

  class Character : public GameObject
  {
  public:
    Character(bool, bool);
    ~Character();
  
  public:
    bool				isPlayer() const;
    float				getPosX() const;
    float				getPosZ() const;
    bool				getMove() const;
    std::vector<bm::Bomb*>		getBomb() const;
    unsigned int			getId() const;
    float				getMoveSpeed() const;
    int					getBombRange() const;
    unsigned int			getNbBomb() const;
    unsigned int			getMaxBomb() const;
    bool				getAlive() const;
    unsigned int			getScore() const;
    void				setScore(unsigned int);
    void				setPosX(float);
    void				setPosZ(float);
    void				setMove(bool);
    void				setWait(unsigned int);
    void				setMoveSpeed(float speed);
    void				setBombRange(int);
    void				setNbBomb(unsigned int);
    void				setMaxBomb(unsigned int);
    void				setLight(irr::scene::ILightSceneNode *);
    void				exec_command(const bool *, float, bm::Game*);
    void				exec_command(const bm::Movements, float, bm::Game*);
    void				setExp(const size_t);
    void				setPos(const irr::core::vector3df &);
    size_t				getExp() const;
    const irr::core::vector3df		&getPos() const;
    irr::scene::ILightSceneNode		*getLight() const;
    unsigned int			getTimer() const;
    void				setTimer(const unsigned int);
    void				manageObjects(std::vector<Character*> *, bm::Game*);
    void				getBonus(const GameObject *, const bm::Game *);
    void				init(int, int, unsigned int, int);
    static int				get_rand_bonus(int, int);
    void				setAlive(bool alive);

  protected:
    bool					_isPlayer;
    unsigned int				_lvl;
    unsigned int				_score;
    int						_bombRange;
    std::map<int, command_exec>			_command;
    unsigned int				_nbBomb;
    unsigned int				_maxBomb;
    std::vector<bm::Bomb *>			_bombs;
    int						_exp;
    bool					_move;
    bool					_alive;
    bool					_antialiasing;
    unsigned int				_id;
    bm::Sound					_sound;
    irr::scene::ILightSceneNode			*_light;
  
  private:
    void	        manageBonus(std::vector<Character*> *toCheck, bm::Game *info);
    void	        manageBomb(std::vector<Character*> *toCheck, bm::Game *info);
    void	        checkObjectsZ(const irr::core::vector3df &posBomb, bm::Game *info, int isNeg);
    void	        checkObjectsX(const irr::core::vector3df &posBomb, bm::Game *info, int isNeg);
    bool		checkDmgZoneX(const irr::core::vector3df &posBomb, const Character *toCheck,
				     std::vector<std::vector<GameObject*>*> *objects,
				      int isNeg) const;
    bool		checkDmgZoneZ(const irr::core::vector3df &posBomb, const Character *toCheck,
				      std::vector<std::vector<GameObject*>*> *objects,
				      int isNeg) const;
    void	        setPause(float frameDeltaTime, bm::Game *info);
    void		checkObjects(const irr::core::vector3df &posBomb, bm::Game *info);
    void		MoveUp(float, bm::Game*);
    void		MoveDown(float, bm::Game*);
    void		MoveLeft(float, bm::Game*);
    void		MoveRight(float, bm::Game*);
    void		WaitFrames(float, bm::Game*);
    void		putBomb(float, bm::Game*);
    bool		checkDmg(const irr::core::vector3df &tmpPos, const Character *toCheck,
				 std::vector<std::vector<GameObject*> *> *) const;
    bool		checkWichPlayer(const bm::Movements &cmd, unsigned int id) const;
    bool		checkNone(const bool *keyCodes, unsigned int id) const;
  };
};

#endif /* !CHARACTER_HPP_ */
