//
// Character.cpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/class/Character
//
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
//
// Started on  Mon May  9 13:18:49 2016 Manuel Trambert
// Last update Sun Jun  5 17:14:02 2016 
//

#include "Game.hpp"
#include "Texture.hpp"
#include "Character.hpp"
#include "Particle.hpp"

bm::Character::Character(bool anti, bool isPlayer)
  :GameObject(1)
{
  _score = 0;
  _exp = 0;
  _isPlayer = isPlayer;
  _command[bm::SPACE] = &Character::putBomb;
  _command[bm::UP] = &Character::MoveUp;
  _command[bm::DOWN] = &Character::MoveDown;
  _command[bm::LEFT] = &Character::MoveLeft;
  _command[bm::RIGHT] = &Character::MoveRight;
  _command[bm::NONE] = &Character::WaitFrames;
  _command[bm::UP2] = &Character::MoveUp;
  _command[bm::DOWN2] = &Character::MoveDown;
  _command[bm::LEFT2] = &Character::MoveLeft;
  _command[bm::RIGHT2] = &Character::MoveRight;
  _command[bm::BOMB2] = &Character::putBomb;
  _waitFrame = 0;
  _nbBomb = 0;
  _maxBomb = 1;
  _move = false;
  _bombRange = 1;
  _alive = true;
  _antialiasing = anti;
  _isPlayer = isPlayer;
}

bm::Character::~Character()
{
  if (_bombs.size() > 0)
     for (auto it = _bombs.begin(); it < _bombs.end(); ++it) {
       _bombs.erase(it);
       delete *it;
     }
}

unsigned int		bm::Character::getTimer() const
{
  return (_timer);
}

void			bm::Character::setTimer(const unsigned int timer)
{
  _timer = timer;
}

void			bm::Character::setPos(const irr::core::vector3df &new_pos)
{
  _pos = new_pos;
}

bool			bm::Character::getAlive() const
{
  return (_alive);
}

irr::scene::ILightSceneNode	*bm::Character::getLight() const
{
  return (_light);
}

void		bm::Character::putBomb(float frameDeltaTime, bm::Game *info)
{
  if (_bombs.size() < _maxBomb)
    {
      irr::core::vector3df	pos = _pos;
      int   x_tmp = (_pos.X / SIZE_BLOCK);
      int   z_tmp = (_pos.Z / SIZE_BLOCK);

      if ((int)pos.X % SIZE_BLOCK >= 5)
	x_tmp++;
      if ((int)pos.Z % SIZE_BLOCK >= 5)
	z_tmp++;
      pos.X = x_tmp * SIZE_BLOCK;
      pos.Z = z_tmp * SIZE_BLOCK - 2.5;
      pos.Y = 2.5;

      bm::Bomb	*new_bomb = new bm::Bomb(this, pos, *info);

      if ((*(*info->getMap())[pos.X / SIZE_BLOCK])[(pos.Z + 2.5) / SIZE_BLOCK] == NULL) {
	_sound.play(bm::BOMB_PLANTED, false, VOL_BOMB);
	_bombs.push_back(new_bomb);
	(*(*info->getMap())[pos.X / SIZE_BLOCK])[(pos.Z + 2.5) / SIZE_BLOCK] = new_bomb;
	_nbBomb += 1;
	_waitFrame = 0;
      }
    }
}

void            bm::Character::MoveUp(float frameDeltaTime, bm::Game *info)
{
  int   x_tmp = (_pos.X / SIZE_BLOCK) + 0.25;
  int   z_tmp = (_pos.Z / SIZE_BLOCK) + 0.25;
  float abs = fabs((x_tmp * SIZE_BLOCK) - _pos.X);

  if (((int)_pos.Z) % SIZE_BLOCK < 8 && _pos.Z < (z_tmp * SIZE_BLOCK))
    z_tmp--;
  abs /= SIZE_BLOCK;
  if (abs >= 0 && abs <= 0.5 && (x_tmp % 2) == 1
      && ((*(*info->getMap())[x_tmp])[z_tmp + 1] == NULL
	  || (*(*info->getMap())[x_tmp])[z_tmp + 1]->getId() == -500)) {
    if (_move == false) {
      getGraphic()->setMD2Animation(irr::scene::EMAT_RUN);
      _move = true;
    }
    if ((*(*info->getMap())[x_tmp])[z_tmp + 1] != NULL)
      {
	getBonus((*(*info->getMap())[x_tmp])[z_tmp + 1], info);
	(*(*info->getMap())[x_tmp])[z_tmp + 1]->getBlock()->remove();
	(*(*info->getMap())[x_tmp])[z_tmp + 1] = NULL;
      }
    _pos.Z += _moveSpeed * frameDeltaTime;
    _pos.X = x_tmp * SIZE_BLOCK;
    if (_pos.Z > (15 - 2) * SIZE_BLOCK)
      _pos.Z = (15 - 2) * SIZE_BLOCK;
    getGraphic()->setRotation(irr::core::vector3df(0., 270., 0.));
    _waitFrame = 0;
  }
}

void            bm::Character::MoveDown(float frameDeltaTime, bm::Game *info)
{
  int   x_tmp = (_pos.X / SIZE_BLOCK) + 0.25;
  int   z_tmp = (_pos.Z / SIZE_BLOCK) + 0.25;
  float abs = fabs((x_tmp * SIZE_BLOCK) - _pos.X);

  if (((int)_pos.Z) % SIZE_BLOCK > 2 && _pos.Z > (z_tmp * SIZE_BLOCK))
    z_tmp++;
  abs /= SIZE_BLOCK;
  if (abs >= 0 && abs <= 0.5 && (x_tmp % 2) == 1
      && ((*(*info->getMap())[x_tmp])[z_tmp - 1] == NULL
	  || (*(*info->getMap())[x_tmp])[z_tmp - 1]->getId() == -500)) {
    if (_move == false) {
      getGraphic()->setMD2Animation(irr::scene::EMAT_RUN);
      _move = true;
    }
    if ((*(*info->getMap())[x_tmp])[z_tmp - 1] != NULL)
      {
	getBonus((*(*info->getMap())[x_tmp])[z_tmp - 1], info);
	(*(*info->getMap())[x_tmp])[z_tmp - 1]->getBlock()->remove();
	(*(*info->getMap())[x_tmp])[z_tmp - 1] = NULL;
      }
    _pos.Z -= _moveSpeed * frameDeltaTime;
    _pos.X = x_tmp * SIZE_BLOCK;
    if (_pos.Z < SIZE_BLOCK)
      _pos.Z = SIZE_BLOCK;
    getGraphic()->setRotation(irr::core::vector3df(0., 90., 0.));
    _waitFrame = 0;
  }
}

void		bm::Character::getBonus(const GameObject *bonus, const bm::Game *info)
{
  int		typeBonus = (dynamic_cast<const bm::Bonus*>(bonus))->getType();

  _score += BONUS_XP;
  if (typeBonus == 0) {
    if (_bombRange <= info->getMaxRange())
      _bombRange += 1;
    _sound.play(bm::FIRE, false, VOL_BONUS);
  }
  else if (typeBonus == 1) {
    if (_moveSpeed < info->getMaxMoveSpeed())
      _moveSpeed += BONUS_SPEED_UP;
    _sound.play(bm::ITEM_GET, false, VOL_BONUS);
  }
  else {
    if (_maxBomb <= info->getMaxBomb())
      _maxBomb += 1;
    _sound.play(bm::BOMB_UP, false, VOL_BONUS);
  }
}

void            bm::Character::MoveRight(float frameDeltaTime, bm::Game *info)
{
  int   z_tmp = (_pos.Z / SIZE_BLOCK) + 0.3;
  int   x_tmp = (_pos.X / SIZE_BLOCK) + 0.3;
  float abs = fabs((z_tmp * SIZE_BLOCK) - _pos.Z);

  if (((int)_pos.X) % SIZE_BLOCK < 8 && _pos.X < (x_tmp * SIZE_BLOCK))
    x_tmp--;
  abs /= SIZE_BLOCK;
  if (abs >= 0 && abs <= 0.5 && (z_tmp % 2) == 1
      && ((*(*info->getMap())[x_tmp + 1])[z_tmp] == NULL
	  || (*(*info->getMap())[x_tmp + 1])[z_tmp]->getId() == -500)) {
    if (_move == false) {
      getGraphic()->setMD2Animation(irr::scene::EMAT_RUN);
      _move = true;
    }
    if ((*(*info->getMap())[x_tmp + 1])[z_tmp] != NULL)
      {
	getBonus((*(*info->getMap())[x_tmp + 1])[z_tmp], info);
	(*(*info->getMap())[x_tmp + 1])[z_tmp]->getBlock()->remove();
	(*(*info->getMap())[x_tmp + 1])[z_tmp] = NULL;
      }
    _pos.X += _moveSpeed * frameDeltaTime;
    _pos.Z = z_tmp * SIZE_BLOCK;
    if (_pos.X > (21 - 2) * SIZE_BLOCK)
      _pos.Z = (21 - 2) * SIZE_BLOCK;
    getGraphic()->setRotation(irr::core::vector3df(0., 0., 0.));
    _waitFrame = 0;
  }
}

void            bm::Character::MoveLeft(float frameDeltaTime, bm::Game *info)
{
  int   z_tmp = (_pos.Z / SIZE_BLOCK) + 0.26;
  int   x_tmp = (_pos.X / SIZE_BLOCK) + 0.26;
  float abs = fabs((z_tmp * SIZE_BLOCK) - _pos.Z);

  abs /= SIZE_BLOCK;
  if (((int)_pos.X) % SIZE_BLOCK > 2
      && _pos.X > (x_tmp * SIZE_BLOCK))
    x_tmp++;
  if (abs >= 0 && abs <= 0.5 && (z_tmp % 2) == 1
      && ((*(*info->getMap())[x_tmp - 1])[z_tmp] == NULL
	  || (*(*info->getMap())[x_tmp - 1])[z_tmp]->getId() == -500)) {
    if (_move == false) {
      getGraphic()->setMD2Animation(irr::scene::EMAT_RUN);
      _move = true;
    }
    if ((*(*info->getMap())[x_tmp - 1])[z_tmp] != NULL)
      {
	getBonus((*(*info->getMap())[x_tmp - 1])[z_tmp], info);
	(*(*info->getMap())[x_tmp - 1])[z_tmp]->getBlock()->remove();
	(*(*info->getMap())[x_tmp - 1])[z_tmp] = NULL;
      }
    getGraphic()->setRotation(irr::core::vector3df(0., 180., 0.));
    _pos.X -= _moveSpeed * frameDeltaTime;
    _pos.Z = z_tmp * SIZE_BLOCK;
    if (_pos.X < SIZE_BLOCK)
      _pos.X = SIZE_BLOCK;
    _waitFrame = 0;
  }
}

void		bm::Character::WaitFrames(float frameDeltaTime, bm::Game *info)
{
  (void)info;
  getGraphic()->setFrameLoop(0, 250);
  _move = false;
}

const irr::core::vector3df		&bm::Character::getPos() const
{
  return (_pos);
}

bool		bm::Character::checkWichPlayer(const bm::Movements &cmd, unsigned int id) const
{
  if (id == 2)
    return (cmd == bm::UP2
	    || cmd == bm::DOWN2
	    || cmd == bm::LEFT2
	    || cmd == bm::RIGHT2
	    || cmd == bm::BOMB2
	    || cmd == bm::ESCAPE);
  else if (id == 1)
    return (cmd == bm::SPACE
	    || cmd == bm::DOWN
	    || cmd == bm::LEFT
	    || cmd == bm::RIGHT
	    || cmd == bm::UP
	    || cmd == bm::ESCAPE);
  return (false);
}

bool		bm::Character::checkNone(const bool *keyCodes, unsigned int id) const
{
  for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i += 1) {

    bm::Movements cmd = (bm::Movements)i;

    if (id == 2
	&& (cmd == bm::UP2
	    || cmd == bm::DOWN2
	    || cmd == bm::LEFT2
	    || cmd == bm::RIGHT2
	    || cmd == bm::BOMB2
	    || cmd == bm::ESCAPE) && keyCodes[cmd] == true)
      return (true);
    else if (id == 1
	     && (cmd == bm::SPACE
		 || cmd == bm::DOWN
		 || cmd == bm::LEFT
		 || cmd == bm::RIGHT
		 || cmd == bm::UP
		 || cmd == bm::ESCAPE) && keyCodes[cmd] == true)
      return (true);
  }
  return (false);
}

void            bm::Character::exec_command(const bool *keyCodes,
					    float frameDeltaTime,
					    bm::Game *info)
{
  if (checkNone(keyCodes, _id) == false) {

    command_exec	exec = _command[bm::NONE];

    if (exec)
      (this->*exec)(frameDeltaTime, info);
  }
  else {
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i += 1) {

      bm::Movements	cmd = (bm::Movements)i;

      if (keyCodes[i] == true
	  && (checkWichPlayer(cmd, _id) == true)) {

	command_exec	exec;

	exec = _command[cmd];
	if (exec)
	  (this->*exec)(frameDeltaTime, info);
      }
    }
  }
}

void            bm::Character::exec_command(const bm::Movements command,
					    float frameDeltaTime,
					    bm::Game *info)
{
  command_exec	exec;

  exec = _command[command];
  if (exec)
    (this->*exec)(frameDeltaTime, info);
}

void			bm::Character::init(int x, int z, unsigned int id, int exp)
{
  _id = id;
  _exp = exp;
  _score = 0;
  _lvl = exp / 1000;
  if (_lvl > MAX_LVL)
    _lvl = MAX_LVL;
  _moveSpeed = 50.f;
  _graphic->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  _graphic->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
  _graphic->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, _antialiasing);
  _graphic->setPosition(irr::core::vector3df(x, 0, z));
  _pos.X = x;
  _pos.Y = 0;
  _pos.Z = z;
  _graphic->setMD2Animation(irr::scene::EMAT_STAND);
  _graphic->setAnimationSpeed(ANIMATION_SPEED);
}

size_t			bm::Character::getExp() const
{
  return (_exp);
}

void			bm::Character::setExp(const size_t exp)
{
  _exp = exp;
}

void			bm::Character::setLight(irr::scene::ILightSceneNode *light)
{
  _light = light;
}

bool		bm::Character::checkDmgZoneZ(const irr::core::vector3df &posBomb, const Character *toCheck, std::vector<std::vector<GameObject*>*> *objects, int isNeg) const
{
  irr::core::vector3df	pos = toCheck->getPos();

  pos.X = pos.X / SIZE_BLOCK + 0.5;
  pos.Z = pos.Z / SIZE_BLOCK + 0.5;

  for (int i = 1; i <= _bombRange; i += 1) {
    if (((isNeg == -1 && posBomb.Z / SIZE_BLOCK + (i * isNeg) >= 0)
	 || (i > 0 && posBomb.Z / SIZE_BLOCK + i < 15))
	&& (*(*objects)[posBomb.X / SIZE_BLOCK])[posBomb.Z / SIZE_BLOCK + (i * isNeg)] != NULL
	&& (*(*objects)[posBomb.X / SIZE_BLOCK])[posBomb.Z / SIZE_BLOCK + (i * isNeg)]->getId() == -1)
      break;
    if ((((int)pos.X) == ((int)posBomb.X) / SIZE_BLOCK)
	&& ((int)pos.Z) == ((int)posBomb.Z) / SIZE_BLOCK + (i * isNeg))
      return (true);
  }
  if (isNeg == 1)
    return (checkDmgZoneZ(posBomb, toCheck, objects, -1));
  return (false);
}

bool		bm::Character::checkDmgZoneX(const irr::core::vector3df &posBomb,
					     const Character *toCheck,
					     std::vector<std::vector<GameObject*>*> *objects, int isNeg) const
{
  irr::core::vector3df	pos = toCheck->getPos();

  pos.X = pos.X / SIZE_BLOCK + 0.5;
  pos.Z = pos.Z / SIZE_BLOCK + 0.5;

  for (int i = 1; i <= _bombRange; i += 1) {
    if (((isNeg == -1 && posBomb.X / SIZE_BLOCK  + (i * isNeg) >= 0)
	 || (i > 0 && posBomb.X / SIZE_BLOCK + i < 15))
	&& (*(*objects)[posBomb.X / SIZE_BLOCK + (i * isNeg)])[posBomb.Z / SIZE_BLOCK] != NULL
	&& (*(*objects)[posBomb.X / SIZE_BLOCK + (i * isNeg)])[posBomb.Z / SIZE_BLOCK]->getId() == -1)
      break;
    if ((((int)pos.X) == ((int)posBomb.X) / SIZE_BLOCK + (i * isNeg))
	&& ((int)pos.Z) == ((int)posBomb.Z) / SIZE_BLOCK)
      return (true);
  }
  if (isNeg == 1)
    return (checkDmgZoneX(posBomb, toCheck, objects, -1));
  return (checkDmgZoneZ(posBomb, toCheck, objects, 1));
}

bool		bm::Character::checkDmg(const irr::core::vector3df &posBomb,
					const Character *toCheck,
					std::vector<std::vector<GameObject*> *> *objects) const
{
  irr::core::vector3df		pos = toCheck->getPos();
  int			        tmp;

  tmp = (toCheck->getPos().X / SIZE_BLOCK) + 0.5;
  pos.X = tmp;
  tmp = (toCheck->getPos().Z / SIZE_BLOCK) + 0.5;
  pos.Z = tmp;

  if ((((int)pos.X) == ((int)posBomb.X) / SIZE_BLOCK) && ((int)pos.Z) == ((int)posBomb.Z) / SIZE_BLOCK)
    return (true);
  return (checkDmgZoneX(posBomb, toCheck, objects, 1));
}

int                     bm::Character::get_rand_bonus(int mod, int proba)
{
  static unsigned int   incr = 1;
  int                   bonus;

  srand(time(NULL) + incr);
  incr += rand();
  bonus = rand() % 100;
  if (incr >= UINT_MAX - 1)
    incr = 1;
  if (bonus < proba)
    {
      bonus = rand() % mod;
      return (bonus);
    }
  return (-1);
}

void		bm::Character::checkObjectsZ(const irr::core::vector3df &posBomb, bm::Game *info, int isNeg)
{
  irr::core::vector3df	tmpPos(posBomb);
  int	i;

  for (i = 1; i <= _bombRange; i += 1)
    {
      if ((isNeg == 1 && posBomb.Z + i < 15) || (isNeg == -1 && posBomb.Z - i >= 0)) {
	if ((*(*info->getMap())[posBomb.X])[posBomb.Z + (i * isNeg)] != NULL
	    && (*(*info->getMap())[posBomb.X])[posBomb.Z + (i * isNeg)]->getId() == -1)
	  break;
	if ((*(*info->getMap())[posBomb.X])[posBomb.Z + (i * isNeg)] != NULL
	    && (*(*info->getMap())[posBomb.X])[posBomb.Z + (i * isNeg)]->getId() > 0)
	  {
	    irr::core::vector3df tmp(posBomb.X * SIZE_BLOCK, 0, ((posBomb.Z + (i * isNeg)) * SIZE_BLOCK));

	    (*(*info->getMap())[posBomb.X])[posBomb.Z + (i * isNeg)]->getBlock()->remove();
	    (*(*info->getMap())[posBomb.X])[posBomb.Z + (i * isNeg)] = NULL;
	    _score += XP_UP;
	    srand(time(NULL));

	    int myRand = bm::Character::get_rand_bonus(3, 15 + _lvl);

	    if (myRand >= 0) {
	      (*(*info->getMap())[posBomb.X])[posBomb.Z + (i * isNeg)] = new bm::Bonus(10,
										       *info,
										       tmp,
										       myRand);
	    }
	  }
      }
    }
  tmpPos.X *= SIZE_BLOCK;
  tmpPos.Z *= SIZE_BLOCK;
  if (i > 1)
    info->getParticle()->push_back(new Particle(irr::core::vector3df(0, 0, (0.06 * isNeg)), 100, 300, tmpPos, *info, i));
  if (isNeg == 1)
    checkObjectsZ(posBomb, info, -1);
}

void		bm::Character::checkObjectsX(const irr::core::vector3df &posBomb, bm::Game *info, int isNeg)
{
  irr::core::vector3df	tmpPos(posBomb);
  int	i;

  for (i = 1; i <= _bombRange; i += 1)
    {
      if ((isNeg == 1 && posBomb.X + i < 21) || (isNeg == -1 && posBomb.X - i >= 0)) {
	if ((*(*info->getMap())[posBomb.X + (i * isNeg)])[posBomb.Z] != NULL
	    && (*(*info->getMap())[posBomb.X + (i * isNeg)])[posBomb.Z]->getId() == -1)
	  break;
	if ((*(*info->getMap())[posBomb.X + (i * isNeg)])[posBomb.Z] != NULL
	    && (*(*info->getMap())[posBomb.X + (i * isNeg)])[posBomb.Z]->getId() > 0)
	  {
	    irr::core::vector3df tmp((posBomb.X + (i * isNeg)) * SIZE_BLOCK, 0, posBomb.Z * SIZE_BLOCK);

	    (*(*info->getMap())[posBomb.X + (i * isNeg)])[posBomb.Z]->getBlock()->remove();
	    (*(*info->getMap())[posBomb.X + (i * isNeg)])[posBomb.Z] = NULL;
	    _score += XP_UP;
	    srand(time(NULL));

	    int myRand = bm::Character::get_rand_bonus(3, 15 + _lvl);

	    if (myRand >= 0) {
	      (*(*info->getMap())[posBomb.X + (i * isNeg)])[posBomb.Z] = new bm::Bonus(10,
										       *info,
										       tmp,
										       myRand);
	    }
	  }
      }
    }
  tmpPos.X *= SIZE_BLOCK;
  tmpPos.Z *= SIZE_BLOCK;
  if (i > 1)
    info->getParticle()->push_back(new Particle(irr::core::vector3df(0.06 * isNeg, 0, 0), 100, 300, tmpPos, *info, i));
  if (isNeg == 1)
    checkObjectsX(posBomb, info, -1);
}

void			bm::Character::checkObjects(const irr::core::vector3df &posBomb,
						    bm::Game *info)
{
  int			i;
  irr::core::vector3df	tmpPos(posBomb);

  tmpPos.X /= SIZE_BLOCK;
  tmpPos.Z /= SIZE_BLOCK;
  checkObjectsZ(tmpPos, info, 1);
  checkObjectsX(tmpPos, info, 1);
}

void		bm::Character::manageBomb(std::vector<Character*> *toCheck, bm::Game *info)
{
  auto it = _bombs.begin();
  bool erased = false;
  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

  while (it != _bombs.end())
    {
      int timeSpent = std::chrono::duration_cast<std::chrono::milliseconds> (end - (*it)->getTimer()).count();
      if (timeSpent >= DELAY_BOMB)
	{
	  irr::core::vector3df	tmpPos((*it)->getPos().X,
				       (*it)->getPos().Y,
				       (*it)->getPos().Z);

	  tmpPos.Z += 2.5;
	  checkObjects(tmpPos, info);
	  for (std::vector<Character*>::iterator it1 = toCheck->begin();
	       it1 < toCheck->end(); ++it1)
	    {
	      if ((*it1)->getAlive() == true
		  && checkDmg(tmpPos, (*it1), info->getMap()) == true)
		{
		  if ((*it1) != (*it)->getOwner())
		    (*it)->getOwnerUnconst()->setScore((*it)->getOwner()->getScore() + KILL_XP);
		  (*it1)->getGraphic()->remove();
		  (*it1)->setGraphic(NULL);
		  (*it1)->_alive = false;
		}
	    }
	  _sound.play(bm::EXPLOSION, false, VOL_EXPLO);
	  (*it)->getGraphic()->remove();
	  (*(*info->getMap())[tmpPos.X / SIZE_BLOCK])[(tmpPos.Z) / SIZE_BLOCK] = NULL;
	  erased = true;
	  _nbBomb -= 1;
	}
      it = erased == false ? (it + 1) : _bombs.erase(it);
      erased = false;
    }
}

void		bm::Character::manageBonus(std::vector<Character*> *toCheck, bm::Game *info)
{
  std::chrono::time_point<std::chrono::system_clock> end
    = std::chrono::system_clock::now();

  for (auto it = info->getMap()->begin(); it != info->getMap()->end(); ++it)
    {
      for (auto it2 = (*it)->begin(); it2 != (*it)->end(); ++it2)
	{
	  if ((*it2) != NULL && (*it2)->getId() == ID_BONUS) {
	    bm::Bonus	*tmp = (dynamic_cast<Bonus*>(*it2));

	    int timeSpent =
	      std::chrono::duration_cast<std::chrono::milliseconds> (end - tmp->getTimer()).count();
	    if (timeSpent >= LIFETIME_BONUS) {
	      tmp->getBlock()->remove();
	      (*it2) = NULL;
	    }
	  }
	}
    }
}

void		bm::Character::manageObjects(std::vector<Character*> *toCheck, bm::Game *info)
{
  manageBomb(toCheck, info);
  manageBonus(toCheck, info);
}

float		bm::Character::getPosX() const
{
  return (_pos.X);
}

float		bm::Character::getPosZ() const
{
  return (_pos.Z);
}

void		bm::Character::setPosX(float x)
{
  _pos.X = x;
}

void		bm::Character::setPosZ(float z)
{
  _pos.Z = z;
}

void		bm::Character::setWait(unsigned int wait)
{
  _waitFrame = wait;
}

void		bm::Character::setBombRange(int Range)
{
  _bombRange = Range;
}

void		bm::Character::setNbBomb(unsigned int nb)
{
  _nbBomb = nb;
}

void		bm::Character::setMaxBomb(unsigned int max)
{
  _maxBomb = max;
}

bool		bm::Character::getMove() const
{
  return (_move);
}

std::vector<bm::Bomb*>		bm::Character::getBomb() const
{
  return (_bombs);
}

int				bm::Character::getBombRange() const
{
  return (_bombRange);
}

unsigned int			bm::Character::getNbBomb() const
{
  return (_nbBomb);
}

unsigned int			bm::Character::getMaxBomb() const
{
  return (_maxBomb);
}

float				bm::Character::getMoveSpeed() const
{
  return (_moveSpeed);
}

void	bm::Character::setMoveSpeed(float speed)
{
  _moveSpeed = speed;
}

unsigned int			bm::Character::getScore() const {
  return (_score);
}

void				bm::Character::setScore(unsigned int score) {
  _score = score;
}

unsigned int			bm::Character::getId() const {
  return (_id);
}

bool				bm::Character::isPlayer() const {
  return (_isPlayer);
}

void				bm::Character::setAlive(bool alive)
{
  this->_alive = alive;
}
