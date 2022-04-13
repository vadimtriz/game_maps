#include "MazeWindow.h"
#include <cmath>

MazeWindow::MazeWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	SDL_SetWindowTitle(_window.get(), "Maze Window");
	_map = std::make_shared<Map>("map.txt");
	_player.spawn(_map);


	SDL_SetRenderDrawBlendMode(_renderer.get(), SDL_BLENDMODE_BLEND);
}

void MazeWindow::draw_minimap(Uint8 alpha)
{
	for (int row = 0; row < _map->height(); ++row) {
		for (int col = 0; col < _map->width(); ++col) {
			if (_map->is_wall(col, row))
				SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, alpha);
			else
				SDL_SetRenderDrawColor(_renderer.get(), 100, 100, 100, alpha);

			SDL_Rect cell_rect { col * 20, row * 20, 20, 20 };
			SDL_RenderFillRect(_renderer.get(), &cell_rect);
		}
	}
	SDL_Point player_line[2];
	player_line[0].x = int(_player.x() * 20);
	player_line[0].y = int(_player.y() * 20);
	player_line[1].x = player_line[0].x + int(30 * cos(_player.dir()));
	player_line[1].y = player_line[0].y + int(30 * sin(_player.dir()));
	SDL_SetRenderDrawColor(_renderer.get(), 200, 200, 96, 255);
	SDL_RenderDrawLines(_renderer.get(), player_line, 2);
	SDL_Rect player_rect { int(_player.x() * 20 - 5), int(_player.y() * 20 - 5),
			11, 11 };
	SDL_SetRenderDrawColor(_renderer.get(), 255, 127, 127, 255);
	SDL_RenderFillRect(_renderer.get(), &player_rect);
}
void MazeWindow::cast_ray(
		double &rx, double &ry,
		double dx, double dy)
{
	do{
		rx += dx;
		ry += dy;
	} while (not _map ->is_wall(rx, ry));
}

void MazeWindow::draw_col (int col, int hh)
{
	SDL_SetRenderDrawColor(_renderer.get(), 32, 32, 192, 255);
	SDL_RenderDrawLine(_renderer.get(),
			col, height()/2-hh/2,
			col, height()/2+hh/2);
}

void MazeWindow::draw_col_textured(
		int col, int hh,
		Texture &tex, double tx)
{
	tex.draw_col(col, height()/2 - hh/2, hh, tx);
}
static constexpr double EPSILON = 0.0001;
void MazeWindow::draw_view()
{
	double Pi = acos(-1.0);
	double alfa = _player.dir();
	double px = _player.x();
	double py = _player.y();
	double betta, gamma;
	double fov = Pi/3;
	double Ds = _width / (2.0 / tan(fov / 2.0));
	double tx, txv, txh;

		SDL_Rect sky_rect {0, 0, width(), height()/2};
		SDL_Rect floor_rect {0, height()/2, width(), height()/2};
		SDL_SetRenderDrawColor(_renderer.get(), 64, 128, 192, 255);
		SDL_RenderFillRect(_renderer.get(), &sky_rect);
		SDL_SetRenderDrawColor(_renderer.get(), 64, 64, 64, 255);
		SDL_RenderFillRect(_renderer.get(), &floor_rect);

		for (int col = 0; col < width(); ++col){
			double rx, ry, dx, dy;
			double Dh, Dv, Dw;
			int h;
			int ctv, cth, ct = 1;
			gamma = atan2(double(col - width()/2), Ds);
			betta = alfa + gamma;
			if (sin(betta)>EPSILON){
				dy = 1;
				dx = 1/tan(betta);
				ry = floor(py)+EPSILON;
				rx = px - (py - ry)*dx;
				cast_ray(rx, ry, dx, dy);
				Dh=hypot(rx-px, ry - py);
				txh = rx - floor(rx);
				cth = _map->cell_type(rx,ry);

			}
			else if (sin(betta)<-EPSILON){
				dy = -1;
				dx = 1/tan(-betta);
				ry = ceil(py)-EPSILON;
				rx = px - (ry - py)*dx;
				cast_ray(rx, ry, dx, dy);
				Dh=hypot(rx-px, ry - py);
				txh = rx - floor(rx);
				Dw = Dh;
				cth = _map->cell_type(rx,ry);
			}
			else{
				Dh = INFINITY;
				txh = 0.0;
				cth=1;
			}
			if (cos(betta)>EPSILON){
				dx = 1;
				dy = tan(betta);
				rx = floor(px)+EPSILON;
				ry = py - (px - rx)*dy;
				cast_ray(rx, ry, dx, dy);
				Dv=hypot(rx-px, ry - py);
				txv = ry - floor(ry);
				ctv = _map->cell_type(rx,ry);
			}
			else if (cos(betta)<-EPSILON){
				dx = -1;
				dy = tan(-betta);
				rx = ceil(px)-EPSILON;
				ry = py - (rx - px)*dy;
				cast_ray(rx, ry, dx, dy);
				Dv=hypot(rx-px, ry - py);
				txv = ry - floor(ry);
				ctv = _map->cell_type(rx,ry);
			}
			else{
				Dv = INFINITY;
				txv = 0.0;
				ctv = 1;
			}
			if (Dv<Dh){
				Dw=Dv;
				tx=txv;
				ct = ctv;
			} else{
				Dw=Dh;
				tx=txh;
				ct = cth;
			}
			h = int (Ds / Dw / cos(gamma));
			switch (ct) {
				case 2: draw_col_textured(col, h, _wall2, tx); break;
				case 3: draw_col_textured(col, h, _wall3, tx); break;
				default:
					draw_col_textured(col, h, _wall1, tx);
		}
	}
}

void MazeWindow::render()
{
	draw_view();
	draw_minimap(197);
}

void MazeWindow::handle_keys(const Uint8 *keys)
{
	if (keys[SDL_SCANCODE_W]) _player.walk_forward();
	if (keys[SDL_SCANCODE_S]) _player.walk_backward();
	if (keys[SDL_SCANCODE_D]) _player.shift_right();
	if (keys[SDL_SCANCODE_A]) _player.shift_left();
	if (keys[SDL_SCANCODE_E]) _player.turn_right();
	if (keys[SDL_SCANCODE_Q]) _player.turn_left();
}
