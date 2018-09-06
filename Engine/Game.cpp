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
	paddle(Vec2(350.0f, 520.0f)),
	soundPaddle(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	soundWall(L"Sounds\\wall.wav"),
	soundNextRound(L"Sounds\\ready.wav"),
	soundGameOver(L"Sounds\\game_over.wav")
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

	ResetBall();
}

void Game::Go()
{
	gfx.BeginFrame();	

	/*
	Increase the number of steps UpdateModel()
	is executed each pass to improve collision 
	detection accuracy.
	*/
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
	if (isGameStarted && !isGameOver && !waitForNextRound)
	{
		ball.Update(dt);

		// wallHitResult: 0=none 1=hit wall 2=hit bottom
		const int wallHitResult = ball.WallCollision(gameArea);
		if (wallHitResult == 1) // hit side or top wall
		{
			soundWall.Play();

			// Only reset cooldown if not still colliding with Ball.
			// Helps prevent Ball from getting trapped between Paddle and Wall.
			if (! paddle.GetRect().isRectOverlapping(ball.GetRect()))
			{
				paddle.ResetCooldown();
			}
		}
		else if (wallHitResult == 2) // hit bottom
		{
			lives -= 1;
			if (lives == 0)
			{
				soundGameOver.Play();
				isGameOver = true;
			}
			else
			{
				soundNextRound.Play();
				waitForNextRound = true;
			}
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

					// Find the Brick that is closer to the Ball's center and undestroy the other Brick that is farther
					if (firstDistance < secondDistance)
					{
						// First brick is closer, undestroy the second
						bricks[i].SetDestroyed(false);
					}
					else
					{
						// Second brick is closer, undestroy the first
						bricks[firstCollisionIndex].SetDestroyed(false);
					}
				}
			}
		}
		if (firstCollision)
		{
			soundBrick.Play();
			paddle.ResetCooldown();
		}

		if (paddle.BallCollision(ball))
		{
			soundPaddle.Play();
		}
	}
	else if (waitForNextRound && !isGameOver)
	{
		if ((curWaitTime += dt) > waitTime)
		{
			waitForNextRound = false;
			curWaitTime = 0.0f;
			ResetBall();
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

void Game::ResetBall()
{
	ball = Ball(Graphics::GetScreenRect().GetCenter(), Vec2(-0.55f, -1.0f));
}

void Game::ComposeFrame()
{
	if (isGameStarted)
	{
		// Draw Walls
		gfx.DrawRect(int(gameArea.left - borderThickness), int(gameArea.top - borderThickness), int(gameArea.left), gfx.ScreenHeight, Colors::Gray);
		gfx.DrawRect(int(gameArea.left - borderThickness), int(gameArea.top - borderThickness), int(gameArea.right + borderThickness), int(gameArea.top), Colors::Gray);
		gfx.DrawRect(int(gameArea.right), int(gameArea.top - borderThickness), int(gameArea.right + borderThickness), gfx.ScreenHeight, Colors::Gray);

		// Draw Bricks
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}

		// Draw Ball
		SpriteCodex::DrawBall(ball.GetPos() + Vec2(ballRadius, ballRadius), gfx);

		// Draw Paddle
		paddle.Draw(gfx);

		if (isGameOver)
		{
			// Draw Game Over sprite
			SpriteCodex::DrawGameOver(Vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
		}
		else if (waitForNextRound)
		{
			// Draw Get Ready sprite
			SpriteCodex::DrawReady(Vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
		}

		// Draw Lives
		const int livesPadding = 2;
		for (int i = 0; i < lives; i++)
		{
			gfx.DrawRect(RectF(gameArea.left    + i * 50, 
							   gfx.ScreenHeight - 20, 
							   gameArea.left    + 40 + i * 50, 
							   gfx.ScreenHeight - 10).GetExpanded(livesPadding) ,
						Colors::Cyan);
		}
	}
	else
	{
		// Draw right-angled triangles for test
		//gfx.DrawIsoRightTriUL(100, 100, 50, Colors::White);
		//gfx.DrawIsoRightTriUR(200, 100, 50, Colors::White);
		//gfx.DrawIsoRightTriBL(100, 200, 50, Colors::White);
		//gfx.DrawIsoRightTriBR(200, 200, 50, Colors::White);

		// Draw Game Title sprite
		SpriteCodex::DrawTitle(Vec2(400.0f, 300.0f), gfx);
	}
}
