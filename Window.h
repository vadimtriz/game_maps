#ifndef WINDOW_H_
#define WINDOW_H_
#include <memory>
#include <SDL2/SDL.h>

class Window
{
public:
	 static constexpr int DEFAULT_HEIGHT = 600;
	static constexpr int DEFAULT_WIDTH = 800;

protected:
 std::shared_ptr<SDL_Window> _window;
 std::shared_ptr<SDL_Renderer> _renderer;
	int _width, _height;

public:
	Window(int w = DEFAULT_WIDTH, int h = DEFAULT_HEIGHT);
	virtual ~Window() {}

	virtual void handle_event(const SDL_Event &event) {}
	virtual void handle_keys(const Uint8 *keys) {}
	  virtual void update() {}
	  virtual void render() {}
	void main_loop();

	int height() const
	{
		return _height;
	}

	int width() const
	{
		return _width;
	}
};

#endif /* WINDOW_H_ */
