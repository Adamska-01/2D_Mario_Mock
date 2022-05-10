#pragma once

//Global enum of keys 
enum KEYS_PRESSED_LIST
{
	KEY_ESCAPE,					//0			
	KEY_SPACE,					//1
	KEY_W,						//2
	KEY_A,						//3
	KEY_D,						//4
	SIZE_OF_KEYS_PRESSED_ENUM	//5
};


class Input
{
public:
	Input();
	~Input();

	void GetInput();
	bool KeyIsPressed(KEYS_PRESSED_LIST key);
private:
	bool m_keysPressed[SIZE_OF_KEYS_PRESSED_ENUM];
};