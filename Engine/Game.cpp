/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "Keyboard.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(400.0f, 400.0f), Vec2(1.0f, 1.0f)),
	paddle(Vec2(350.0f, 520.0f))
{
	int i = 0;
	for (int y = 0; y < nBricksVertical; y++)
	{
		const Color c = brickColors[y];
		for (int x = 0; x < nBricksHorizontal; x++)
		{
			bricks[i] = Brick(RectF(gameAreaTopLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), c);
			i++;
		}
	}

	ballRadius = float(ball.GetDiameter() / 2);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	ball.Update(int(ballSpeed) * dt, gameArea);

	paddle.Update(wnd.kbd, dt, gameArea);
	
	for (int i = 0; i < nBricks; i++)
	{
		if (bricks[i].BallCollision(ball))
		{
			if (ball.GetVel().y < 0) {
				ball.ReboundY();
			}
			break;
		}
	}

	if (paddle.BallCollision(ball))
	{
		if (ball.GetVel().y > 0) {
			ball.ReboundY();
		}
	}
}

void Game::ComposeFrame()
{
	gfx.DrawRect(0, 0, int(gameArea.left), int(gameArea.bottom), Colors::Gray);
	gfx.DrawRect(int(gameArea.right), 0, gfx.ScreenWidth, int(gameArea.bottom), Colors::Gray);

	for (int i = 0; i < nBricks; i++)
	{
		bricks[i].Draw(gfx);
	}

	SpriteCodex::DrawBall(ball.GetPos() + Vec2(ballRadius, ballRadius), gfx);

	paddle.Draw(gfx);
}
