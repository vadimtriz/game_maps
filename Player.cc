#include "Player.h"
#include "utils.h"

Player::Player()
{

}

void Player::spawn(std::shared_ptr<Map> &where)
{
	_map = where;
	if (_map == nullptr)
		return;
	_x = where -> start_x();
	_y = where -> start_y();
	_dir = where -> start_a();
}

void Player::move(double dir, double dist)
{
	if(_map == nullptr) return;
	double nx, ny;
	nx = _x + dist * cos(dir);
	ny = _y + dist * sin(dir);
	if (!_map->is_wall(nx, ny)) {
		_x = nx;
		_y = ny;
	}
}

void Player::walk_forward(double dist)
{
	move(_dir, dist);
}

void Player::walk_backward(double dist)
{
	move(_dir, -dist);
}

void Player::shift_left(double dist)
{
	move(_dir + Pi/2.0, -dist);
}

void Player::shift_right(double dist)
{
	move(_dir + Pi/2.0, dist);
}

void Player::turn_left(double angle)
{
	_dir -= angle;
	while (_dir < 0.0) _dir += 2*Pi;
}

void Player::turn_right(double angle)
{
	_dir += angle;
	while (_dir >= 2*Pi) _dir -= 2*Pi;
}
