#ifndef PLAYER_H_
#define PLAYER_H_

#include "Map.h"
#include <memory>
class Player
{
public:
	static constexpr double WALK_STEP = 0.05;
	static constexpr double TURN_STEP = 0.04;
protected:
	std::shared_ptr <Map> _map;
	double _x {}, _y {}, _dir {}, _fov{};

	void move(double dir, double dist);

public:
	Player();
	virtual ~Player() = default;

	void spawn(std::shared_ptr<Map> &where);
	void walk_forward (double dist = WALK_STEP);
	void walk_backward (double dist = WALK_STEP);
	void shift_left (double dist = WALK_STEP);
	void shift_right (double dist = WALK_STEP);
	void turn_left (double angle = TURN_STEP);
	void turn_right (double angle = TURN_STEP);

	double dir() const { return _dir; }
	double x() const   { return _x;   }
	double y() const   { return _y;   }

private:
	void move(double dist);
};
#endif /* PLAYER_H_ */
