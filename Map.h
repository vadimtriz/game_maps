#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <cmath>

class Map
{
protected:
	int _width {}, _height {};
	double _start_x {}, _start_y {};
	double _start_a {};
	std::vector<int> _data;
public:
	Map(const char *filename);
	virtual ~Map() = default;

	int height() const { return _height; }
	int width() const  { return _width;  }
	double start_x() const {return _start_x;}
	double start_y() const {return _start_y;}
	double start_a() const {return _start_a;}
	bool is_wall(int x, int y)
	{
		if(x < 0 or x >= _width or y < 0 or y >= _height)
			return true;
		return _data[y * _width + x] != 0;
	}
	bool is_wall(double x, double y)
		{
			return is_wall(int(floor(x)), int(floor(y)));
		}

	int cell_type(int x, int y){
		if (x<0 or x>=_width or y<0 or y>=_height)
			return 1;
		return _data[y*_width +x];
	}
	int cell_type(double x, double y){
		return cell_type(int(floor(x)), int(floor(y)));
	}
};

#endif /* MAP_H_ */
