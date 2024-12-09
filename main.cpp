#include <iostream>
#include <raylib.h>
#include <string>
using namespace std;

const int screenWidth = 800;
const int screenHeight = 650;

enum GameScreen{START, PLAY, OVER};
bool gamePaused = false;

int playerOneScore = 0;
int playerTwoScore = 0;

void drawGameBackground();
void drawStartScreen(Font);
void drawGameOverScreen(Font);
void playGame(bool);

int main()
{
	InitWindow(screenWidth, screenHeight, "Ping Pong");
	GetMonitorCount() >= 2 ? SetWindowMonitor(1) : SetWindowMonitor(0);
	SetTargetFPS(60);
	Font ButtonFont = LoadFont("../res/RubikMoonrocks-Regular.ttf");
	GameScreen currentScreen = START;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		drawGameBackground();

		switch (currentScreen) 
		{
		case START:
			if (IsKeyPressed(KEY_ENTER))
			{
				currentScreen = PLAY;
			}
			drawStartScreen(ButtonFont);
			break;
		case PLAY:
			if((playerOneScore == 5 || playerTwoScore == 5))
			{
				currentScreen = OVER;
			}
			if(IsKeyPressed(KEY_SPACE))
			{
				gamePaused = !gamePaused;
			}
			else if(IsKeyPressed(KEY_Q))
			{
				EndDrawing();
				UnloadFont(ButtonFont);
				CloseWindow();
				return 0; 
			}
			playGame(gamePaused);
			break;
		case OVER:
			drawGameOverScreen(ButtonFont);
			if (IsKeyPressed(KEY_ENTER))
			{
				currentScreen = START;
				playerOneScore = 0;  
				playerTwoScore = 0;
			}
			else if(IsKeyPressed(KEY_Q))
			{
				EndDrawing();
				UnloadFont(ButtonFont);
				CloseWindow();
				return 0; 
			}
			break;
		}	
		EndDrawing();
	}
	UnloadFont(ButtonFont);
	CloseWindow();

	return 0;
}

void drawGameBackground()
{
	int topStartPosX = 0;
	int topStartPosY = 10;
	int topEndPosX = screenWidth;
	int topEndPosY = 10; 

	int bottomStartPosX = 0;
	int bottomStartPosY = screenHeight-10;
	int bottomEndPosX = screenWidth;
	int bottomEndPosY = screenHeight-10;

	int MiddleStartPosX = screenWidth/2;
	int MiddleStartPosY = 10;
	int MiddleEndPosX = screenWidth/2;
	int MiddleEndPosY = screenHeight-10;

	DrawLine(topStartPosX, topStartPosY, topEndPosX, topEndPosY, RAYWHITE);
	DrawLine(bottomStartPosX, bottomStartPosY, bottomEndPosX, bottomEndPosY, RAYWHITE);
	DrawLine(MiddleStartPosX, MiddleStartPosY, MiddleEndPosX, MiddleEndPosY, RAYWHITE);
}

void drawStartScreen(Font ButtonFont)
{
	string startButtonMessage = "PRESS ENTER TO START";
	Vector2 startPosition = {50, 250};
	Vector2 startOrigin = { 0.5f, 0.5f };
	float fontRotation = 0.0f;
	float fontSize = 50.0f;
	float fontSpacing = 10.0f;

	int ballCenterOnX = screenWidth/2;
	int ballCenterOnY = screenHeight/2;
	float ballRadius = 10;

	DrawTextPro(ButtonFont, startButtonMessage.c_str(),startPosition, startOrigin, fontRotation, fontSize, fontSpacing, GREEN);
	DrawCircle(ballCenterOnX, ballCenterOnY, ballRadius, GOLD);
}

void drawGameOverScreen(Font ButtonFont)
{
	if(playerOneScore > playerTwoScore)
	{
		DrawTextPro(ButtonFont, "Player One Wins",{145, 15}, {0.5f, 0.5f}, 0, 50, 10.0f, BLUE);
	}
	else if(playerTwoScore > playerOneScore)
	{
		DrawTextPro(ButtonFont, "Player Two Wins",{145, 15}, {0.5f, 0.5f}, 0, 50, 10.0f, MAGENTA);
	}
	else
	{
		DrawTextPro(ButtonFont, "!!!! DRAW !!!!",{200, 15}, {0.5f, 0.5f}, 0, 50, 10.0f, PINK);
	}

	string GameOverButtonMessage1 = "GAME OVER!!!";
	string GameOverButtonMessage2 = "PRESS ENTER TO GO AGAIN";
	string GameOverButtonMessage3 = "PRESS Q TO QUIT";
	Vector2 startPosition1 = {195, 250};
	Vector2 startPosition2 = {0, 550};
	Vector2 startPosition3 = {185, 600};
	Vector2 startOrigin = { 0.5f, 0.5f };
	float fontRotation = 0.0f;
	float fontSize = 50.0f;
	float fontSpacing = 10.0f;

	DrawTextPro(ButtonFont, GameOverButtonMessage1.c_str(),startPosition1, startOrigin, fontRotation, fontSize, fontSpacing, RED);
	DrawTextPro(ButtonFont, GameOverButtonMessage2.c_str(),startPosition2, startOrigin, fontRotation, fontSize, fontSpacing, WHITE);
	DrawTextPro(ButtonFont, GameOverButtonMessage3.c_str(),startPosition3, startOrigin, fontRotation, fontSize, fontSpacing, GOLD);
}

void playGame(bool gamePaused)
{
	Color transparentGrey = {255, 255, 255, 100};
	int gameSpeed = GetRandomValue(1, 5);

	static Vector2 ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
	static Vector2 ballSpeed = { 3.0f, 1.0f };
	float ballRadius = 10.0f;

	static float playerOnePaddleY = 250.0f;
	static float playerTwoPaddleY = 250.0f;
	float rectangleWidth = 10.0f;
	float rectangleHeight = 100.0f;
	float roundness = 1.0f;
	int segments = 16;

	if(gamePaused)
	{
		DrawText(("PAUSED"), 300, 250, 50, RED);
		DrawText(to_string(playerOneScore).c_str(), 365, 13, 50, transparentGrey);
		DrawText(to_string(playerTwoScore).c_str(), 410, 13, 50, transparentGrey);
		DrawCircleV(ballPos, ballRadius, transparentGrey);
		DrawRectangleRounded({10.0f, playerOnePaddleY, rectangleWidth, rectangleHeight}, roundness, segments, transparentGrey);
		DrawRectangleRounded({screenWidth - 20, playerTwoPaddleY, rectangleWidth, rectangleHeight}, roundness, segments, transparentGrey);
	}
	else
	{
		ballPos.x += ballSpeed.x;
		ballPos.y += ballSpeed.y;

		if(IsKeyDown(KEY_UP) && playerOnePaddleY >= 10.0f)
		{
			playerOnePaddleY -= 5.0f;
		}
		if(IsKeyDown(KEY_DOWN) && playerOnePaddleY <= 540.0f)
		{
			playerOnePaddleY += 5.0f;
		}


		if (IsKeyDown(KEY_W) && playerTwoPaddleY >= 10.0f)
		{
			playerTwoPaddleY -= 5.0f;
		}
		if (IsKeyDown(KEY_S) && playerTwoPaddleY <= 540.0f)
		{
			playerTwoPaddleY += 5.0f;
		}

		if(CheckCollisionCircleRec(ballPos, ballRadius, {10.0f, playerOnePaddleY, rectangleWidth, rectangleHeight}))
		{
			ballSpeed.x *= -1;

			float hitPos = (ballPos.y - playerOnePaddleY) / rectangleHeight;

			if (hitPos < 0.23f)
			{
				ballSpeed.y = -fabs(ballSpeed.y) * 1.25f;
			} else if (hitPos > 0.76f)
			{ 
				ballSpeed.y = fabs(ballSpeed.y) * 1.25f;
			} else 
			{ 
				ballSpeed.y *= 1.05f;
			}
		}
		if(CheckCollisionCircleRec(ballPos, ballRadius, {780.0f, playerTwoPaddleY, rectangleWidth, rectangleHeight}))
		{
			ballSpeed.x *= -1;

			float hitPos = (ballPos.y - playerTwoPaddleY) / rectangleHeight;

			if (hitPos < 0.23f)
			{
				ballSpeed.y = -fabs(ballSpeed.y) * 1.25f;
			} else if (hitPos > 0.76f)
			{ 
				ballSpeed.y = fabs(ballSpeed.y) * 1.25f;
			} else 
			{ 
				ballSpeed.y *= 1.05f;
			}
		}

		if(ballPos.x > screenWidth)
		{
			playerOneScore++; 
			ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
			playerOnePaddleY = 250.0f;
			playerTwoPaddleY = 250.0f;
			ballSpeed.x = GetRandomValue(0, 1) ? 3.0f : -3.0f;
			ballSpeed.y = GetRandomValue(0, 1) ? 1.0f : -1.0f;
			WaitTime(1.0f);
		}
		if(ballPos.x < 0)
		{
			playerTwoScore++; 
			ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
			playerTwoPaddleY = 250.0f;
			playerOnePaddleY = 250.0f;
			ballSpeed.x = GetRandomValue(0, 1) ? 3.0f : -3.0f;
			ballSpeed.y = GetRandomValue(0, 1) ? 1.0f : -1.0f;
			WaitTime(1.0f);
		}

		if(ballPos.y <= 20)
		{
			ballSpeed.y *= -1;
		}
		if(ballPos.y >= screenHeight-20)
		{
			ballSpeed.y *= -1;
		}

		DrawText(to_string(playerOneScore).c_str(), 365, 13, 50, BLUE);
		DrawText(to_string(playerTwoScore).c_str(), 410, 13, 50, MAGENTA);
		DrawText(("Q - QUIT"), 10, 0, 10, transparentGrey);
		DrawText(("SPACE - PAUSE"), 75, 0, 10, transparentGrey);
		DrawCircleV(ballPos, ballRadius, WHITE);
		DrawRectangleRounded({10.0f, playerOnePaddleY, rectangleWidth, rectangleHeight}, roundness, segments, BLUE);
		DrawRectangleRounded({screenWidth - 20, playerTwoPaddleY, rectangleWidth, rectangleHeight}, roundness, segments, MAGENTA);
	}
}