#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <SDL2/SDL.h>
#include <memory>

class Texture
{
protected:
 std::shared_ptr<SDL_Renderer> _renderer;
 std::shared_ptr<SDL_Texture> _texture;
	int _width, _height;
public:
	Texture(std::shared_ptr<SDL_Renderer> _ren,
			 const char *filename);
	virtual ~Texture() = default;

	int height() const { return _height;}
	int width() const { return _width;}

	void draw_col(int x, int y, int h, double tx);
};

#endif /* TEXTURE_H_ */
