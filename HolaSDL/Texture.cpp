#include "Texture.h"
#include <iostream>
#include "checkML.h"

using namespace std;

// borra una textura
void Texture::clean() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

// carga una textura
void Texture::load(string filename, uint nRows, uint nCols) {
		SDL_Surface* tempSurface = IMG_Load(filename.c_str());
		if (tempSurface == nullptr) throw "Error loading surface from " + filename;
		clean();
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (texture == nullptr) throw "Error loading texture from " + filename;
		numRows = nRows;
		numCols = nCols;
		w = tempSurface->w;
		h = tempSurface->h;
		fw = w / numCols;
		fh = h / numRows;
		SDL_FreeSurface(tempSurface);
}

// renderiza una textura entera
void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

// renderiza una parte de una textura
void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	int textW, textH;
	SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);
	srcRect.x = srcRect.y = 0;
	srcRect.w = textW / 3;
	srcRect.h = textH / 2;
	srcRect.x = (textW / 3) * col;
	srcRect.y = (textH / 2) * row;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}