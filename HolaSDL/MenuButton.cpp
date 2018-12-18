#include "MenuButton.h"

MenuButton::MenuButton(Texture* t, int x, int y, int w, int h, void(*callback)(SdlApplication* app)) :
	texture(t), x(x), y(y), w(w), h(h), cb(callback) {}

MenuButton::~MenuButton() {
}

void MenuButton::render() {
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = w;
	dstRect.h = h;
	texture->render(dstRect, SDL_FLIP_NONE);
}

bool MenuButton::handleEvents(SDL_Event& e) {
	bool handled = false;
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {    // RATON IZQUIERDO
		SDL_Point p = { e.button.x, e.button.y };
		SDL_Rect r = { x, y, w, h };
		if (SDL_PointInRect(&p, &r)) {
			cb(app);
			handled = true;
		}
		return handled;
	}
}