#include "Input.h"
#include <SDL.h>


Input::Input()
{
	for (int i = 0; i < KEYS_PRESSED_LIST::SIZE_OF_KEYS_PRESSED_ENUM; i++)
	{
		m_keysPressed[i] = false;
	}
}

Input::~Input()
{
}

void Input::GetInput()
{
	//static means memory is reserved permanently once
	static SDL_Event event;

	//read the keypress for easier debugging
	while (SDL_PollEvent(&event))
	{
		SDL_Keycode keyPressed = event.key.keysym.sym;
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				m_keysPressed[KEY_ESCAPE] = true;
			else if (keyPressed == SDLK_w)
				m_keysPressed[KEY_W] = true;
			else if (keyPressed == SDLK_a)
				m_keysPressed[KEY_A] = true;
			else if (keyPressed == SDLK_SPACE)
				m_keysPressed[KEY_SPACE] = true;
			else if (keyPressed == SDLK_d)
				m_keysPressed[KEY_D] = true;
			else if (keyPressed == SDLK_d)
				m_keysPressed[KEY_D] = true;
			break;

		case SDL_KEYUP:
			if (keyPressed == SDLK_ESCAPE)
				m_keysPressed[KEY_ESCAPE] = false;
			else if (keyPressed == SDLK_w)
				m_keysPressed[KEY_W] = false;
			else if (keyPressed == SDLK_a)
				m_keysPressed[KEY_A] = false;
			else if (keyPressed == SDLK_SPACE)
				m_keysPressed[KEY_SPACE] = false;
			else if (keyPressed == SDLK_d)
				m_keysPressed[KEY_D] = false;
			break;

		case SDL_QUIT:
			m_keysPressed[KEY_ESCAPE] = true;

			//ignore
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
		case SDL_USEREVENT:
		default:
			break;
		}
	}
}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keysPressed[key];
}
