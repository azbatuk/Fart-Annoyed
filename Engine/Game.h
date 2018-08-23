/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Brick.h"
#include "Ball.h"
#include "SpriteCodex.h"
#include "FrameTimer.h"
#include "Paddle.h"
#include "Sound.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr float brickWidth = 40.0f;
	static constexpr float brickHeight = 20.0f;
	static constexpr int nBricksHorizontal = 12;
	static constexpr int nBricksVertical = 4;
	static constexpr int nBricks = nBricksHorizontal * nBricksVertical;
	Brick bricks[nBricks];
	const Color brickColors[4] = { Colors::Red, Colors::Green, Colors::Yellow, Colors::Magenta };
	Ball ball;
	float ballRadius;
	const float gameAreaTopLeftX = (gfx.ScreenWidth - (nBricksHorizontal * brickWidth)) / 2;
	const float gameAreaTopLeftY = 10.0f;
	const Vec2 gameAreaTopLeft = { gameAreaTopLeftX, gameAreaTopLeftY };
	const float padAboveBricks = 60.0f;
	RectF gameArea = { gameAreaTopLeft, Vec2(gameAreaTopLeft.x + nBricksHorizontal * brickWidth, gfx.ScreenHeight)};
	const int borderThickness = 10;
	Paddle paddle;
	FrameTimer ft;
	Sound soundPaddle;
	Sound soundBrick;
	Sound soundWall;
	Sound soundNextRound;
	int lives = 3;
	bool waitTimerStarted = false;
	bool waitForNextRound = false;
	std::chrono::steady_clock::time_point readyWait;
	std::chrono::duration<float> waitDuration;
	const float waitTime = 4.7f;
	bool isGameStarted = false;
	bool isGameOver = false;
	/********************************/
};