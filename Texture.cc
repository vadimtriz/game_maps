#include <stdexcept>
#include "Texture.h"
#include<SDL2/SDL_image.h>
#include <cmath>

Texture::Texture(std::shared_ptr<SDL_Renderer> ren,
		 const char *filename)
: _renderer(ren)
{
 _texture = std::shared_ptr<SDL_Texture>(
			IMG_LoadTexture(ren.get(), filename),
			SDL_DestroyTexture);
	if (_texture == nullptr)
		throw std::runtime_error(
				std::string("Не удалось загрузить текстуру: ") +
				std::string(SDL_GetError()));
	SDL_QueryTexture(_texture.get(), nullptr, nullptr, &_width, &_height);

}

 void Texture::draw_col(int x, int y, int h, double tx)
{
	int txi = int(floor(tx * width()));
 SDL_Rect src_rect {txi, 0, 1, height()};
 SDL_Rect dst_rect {x, y, 1, h};
	SDL_RenderCopy(_renderer.get(), _texture.get(), &src_rect, &dst_rect);
}
