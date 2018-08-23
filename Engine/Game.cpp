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
	ball(Vec2(300.0f, 300.0f), Vec2(1.0f, 1.0f)),
	paddle(Vec2(350.0f, 520.0f)),
	soundPaddle(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	soundWall(L"Sounds\\coin.wav"),
	soundNextRound(L"Sounds\\ready.wav")
{
	int i = 0;
	for (int y = 0; y < nBricksVertical; y++)
	{
		const Color c = brickColors[y];
		for (int x = 0; x < nBricksHorizontal; x++)
		{
			bricks[i] = Brick(RectF(Vec2(gameAreaTopLeft.x, gameAreaTopLeft.y + padAboveBricks) + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), c);
			i++;
		}
	}

	ballRadius = float(ball.GetDiameter() / 2);
}

void Game::Go()
{
	gfx.BeginFrame();	

	// Increase the number of steps UpdateModel()
	// is executed each pass to improve collision 
	// detection accuracy.
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (ball.GetPos().y >= gfx.ScreenHeight - ball.GetDiameter() && startNextRound == false)
	{
		lives -= 1;
		if (lives == 0)
		{
			isGameOver = true;
		}
		else
		{
			startNextRound = true;
		}
	}

	if (isGameStarted && !isGameOver && !startNextRound)
	{
		ball.Update(dt);
		if (ball.WallCollision(gameArea))
		{
			paddle.ResetCooldown();
			//soundWall.Play();
		}

		paddle.Update(wnd.kbd, dt);
		paddle.WallCollision(gameArea);

		// Check if ball hit any brick
		bool firstCollision = false;
		int firstCollisionIndex = 0;
		for (int i = 0; i < nBricks; i++)
		{
			if (bricks[i].BallCollision(ball))
			{
				if (!firstCollision)
				{
					firstCollisionIndex = i;
					firstCollision = true;
				}
				else
				{
					// There is a second collision, meaning ball hit two bricks which are side by side simultaneously.
					// Find which brick's center is closer to the ball's center and destroy that one.

					//Vec2 ballCenter		= ball.GetCenter();
					//Vec2 brick1Center		= bricks[firstCollisionIndex].GetCenter();
					//Vec2 brick2Center		= bricks[i].GetCenter();
					//Vec2 ball2Brick1		= ballCenter - brick1Center;
					//Vec2 ball2Brick2		= ballCenter - brick2Center;
					//float distance1		= ball2Brick1.GetLengthSq();
					//float distance2		= ball2Brick2.GetLengthSq();

					float firstDistance = (ball.GetCenter() - bricks[firstCollisionIndex].GetCenter()).GetLengthSq();
					float secondDistance = (ball.GetCenter() - bricks[i].GetCenter()).GetLengthSq();

					// Undestroy the brick that is farther from the ball's center
					if (firstDistance < secondDistance)
					{
						// First brick is closer, undestroy the second
						bricks[i].SetDestroyed(false);
					}
					else
					{
						// Secong brick is closer, undestroy the first
						bricks[firstCollisionIndex].SetDestroyed(false);
					}
				}
			}
		}
		if (firstCollision)
		{
			paddle.ResetCooldown();
			soundBrick.Play();
		}

		if (paddle.BallCollision(ball))
		{
			soundPaddle.Play();
		}
	}
	else if (startNextRound && !isGameOver)
	{
		if (!waitTimerStarted)
		{
			soundNextRound.Play();
			readyWait = std::chrono::steady_clock::now();
			waitDuration = std::chrono::steady_clock::now() - readyWait;
			waitTimerStarted = true;
		}
		else
		{
			waitDuration = std::chrono::steady_clock::now() - readyWait;
		}

		if (waitDuration.count() > waitTime)
		{
			startNextRound = false;
			waitTimerStarted = false;
			ball.NewRound(Vec2(300.0f, 300.0f), Vec2(1.0f, 1.0f));
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isGameStarted = true;
		}
	}
}

void Game::ComposeFrame()
{
	if (isGameStarted)
	{
		gfx.DrawRect(int(gameArea.left - borderThickness), int(gameArea.top - borderThickness), int(gameArea.left), gfx.ScreenHeight, Colors::Gray);
		gfx.DrawRect(int(gameArea.left - borderThickness), int(gameArea.top - borderThickness), int(gameArea.right + borderThickness), int(gameArea.top), Colors::Gray);
		gfx.DrawRect(int(gameArea.right), int(gameArea.top - borderThickness), int(gameArea.right + borderThickness), gfx.ScreenHeight, Colors::Gray);

		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}

		SpriteCodex::DrawBall(ball.GetPos() + Vec2(ballRadius, ballRadius), gfx);

		paddle.Draw(gfx);

		if (isGameOver)
		{
			SpriteCodex::DrawGameOver(Vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
		}
		else if (startNextRound)
		{
			SpriteCodex::DrawReady(Vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
		}

	}
	else
	{
		SpriteCodex::DrawTitle(Vec2(400.0f, 300.0f), gfx);
	}
}
