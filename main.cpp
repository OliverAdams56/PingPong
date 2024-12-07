#include <iostream>
#include <raylib.h>
#include <string>
using namespace std;

const int screenWidth = 800;
const int screenHeight = 650;

enum GameScreen{START, PLAY, OVER}; // Game States

// Players scores
int playerOneScore = 0;
int playerTwoScore = 0;

void drawGameBackground(); // Draw the game's background (same throughout)
void drawStartScreen(Font); // Draw the start screen with the "CLICK TO START" text
void drawGameOverScreen(Font); // Draw the game over screen with the "GAME OVER!!!" text
void playGame();

int main()
{
	InitWindow(screenWidth, screenHeight, "Ping Pong"); // window size and name
	GetMonitorCount() >= 2 ? SetWindowMonitor(2) : SetWindowMonitor(0); // check monitor to see how many and which is being used
	SetTargetFPS(60);
	Font ButtonFont = LoadFont("../res/RubikMoonrocks-Regular.ttf"); //the font used through out the entirety of the game
	GameScreen currentScreen = START; //game starts at this screen 

	//this is stuff happening in the game it self
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
			if(IsKeyPressed(KEY_ENTER) || (playerOneScore == 5 || playerTwoScore == 5))
			{
				currentScreen = OVER;
			}
			playGame();
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
	// top line properties 
	int topStartPosX = 0;
	int topStartPosY = 10; //border between screen and line
	int topEndPosX = screenWidth;
	int topEndPosY = 10;  //border between screen and line

	// bottom line properties 
	int bottomStartPosX = 0;
	int bottomStartPosY = screenHeight-10; //border between screen and line
	int bottomEndPosX = screenWidth;
	int bottomEndPosY = screenHeight-10; //border between screen and line

	// Middle line properties 
	int MiddleStartPosX = screenWidth/2;
	int MiddleStartPosY = 10; //border between screen and line
	int MiddleEndPosX = screenWidth/2;
	int MiddleEndPosY = screenHeight-10; //border between screen and line

	DrawLine(topStartPosX, topStartPosY, topEndPosX, topEndPosY, RAYWHITE);
	DrawLine(bottomStartPosX, bottomStartPosY, bottomEndPosX, bottomEndPosY, RAYWHITE);
	DrawLine(MiddleStartPosX, MiddleStartPosY, MiddleEndPosX, MiddleEndPosY, RAYWHITE);
}

void drawStartScreen(Font ButtonFont)
{
	// start text properties
	string startButtonMessage = "PRESS ENTER TO START";
	Vector2 startPosition = {50, 250}; // The text will be drawn a little off center of the screen
	Vector2 startOrigin = { 0.5f, 0.5f }; // centered the center of the text
	float fontRotation = 0.0f;
	float fontSize = 50.0f;
	float fontSpacing = 10.0f;

	// ball properties
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

	// Reset the scores when restarting the game

	// Reset the scores when restarting the game

	string GameOverButtonMessage1 = "GAME OVER!!!";
	string GameOverButtonMessage2 = "PRESS ENTER TO GO AGAIN";
	string GameOverButtonMessage3 = "PRESS Q TO QUIT";
	Vector2 startPosition1 = {195, 250}; // The text will be drawn a little off center of the screen
	Vector2 startPosition2 = {0, 550};
	Vector2 startPosition3 = {185, 600};
	Vector2 startOrigin = { 0.5f, 0.5f }; // centered the center of the text
	float fontRotation = 0.0f;
	float fontSize = 50.0f;
	float fontSpacing = 10.0f;

	DrawTextPro(ButtonFont, GameOverButtonMessage1.c_str(),startPosition1, startOrigin, fontRotation, fontSize, fontSpacing, RED);
	DrawTextPro(ButtonFont, GameOverButtonMessage2.c_str(),startPosition2, startOrigin, fontRotation, fontSize, fontSpacing, WHITE);
	DrawTextPro(ButtonFont, GameOverButtonMessage3.c_str(),startPosition3, startOrigin, fontRotation, fontSize, fontSpacing, GOLD);
}

void playGame()
{
	int gameSpeed = GetRandomValue(1, 5);

	// Ball properties
	static Vector2 ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
	static Vector2 ballSpeed = { 3.0f, 1.0f };
	float ballRadius = 10.0f;

    // Paddle properties
	static float playerOnePaddleY = 250.0f;
	static float playerTwoPaddleY = 250.0f;
	float rectangleWidth = 10.0f;
	float rectangleHeight = 100.0f;
	float roundness = 1.0f;
	int segments = 16;

    // Update ball position
	ballPos.x += ballSpeed.x;
	ballPos.y += ballSpeed.y;

	//player one paddle properties
	if(IsKeyDown(KEY_UP) && playerOnePaddleY >= 10.0f) // the hightest the paddle can go up
	{
		playerOnePaddleY -= 5.0f; // direction and speed of paddle
	}
	if(IsKeyDown(KEY_DOWN) && playerOnePaddleY <= 540.0f) //the lowest the paddle can go down (size of padle - edge of screen (650 - 250) + 90)
	{
		playerOnePaddleY += 5.0f; // direction and speed of paddle
	}
	
	//player two paddle properties
	if (IsKeyDown(KEY_W) && playerTwoPaddleY >= 10.0f) // the hightest the paddle can go up
	{
		playerTwoPaddleY -= 5.0f; // direction and speed of paddle
	}
	if (IsKeyDown(KEY_S) && playerTwoPaddleY <= 540.0f) //the lowest the paddle can go down (size of padle - edge of screen (650 - 250) + 90)
	{
		playerTwoPaddleY += 5.0f; // direction and speed of paddle
	}

	// Ball collision with paddles
	if(CheckCollisionCircleRec(ballPos, ballRadius, {10.0f, playerOnePaddleY, rectangleWidth, rectangleHeight})) //10 - offset from screen
	{
		ballSpeed.x *= -1; // multiply the speed by neg 1 to switch direction

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
	if(CheckCollisionCircleRec(ballPos, ballRadius, {780.0f, playerTwoPaddleY, rectangleWidth, rectangleHeight})) //20 - offset from screen
	{
		ballSpeed.x *= -1; // multiply the speed by neg 1 to switch direction

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

	// Ball out of bounds
	if(ballPos.x > screenWidth) // if ball pass screen on right player one point 
	{
		playerOneScore++; 
		ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
		playerOnePaddleY = 250.0f;
		playerTwoPaddleY = 250.0f;
		ballSpeed.x = GetRandomValue(0, 1) ? 3.0f : -3.0f; // Randomize x-direction
		ballSpeed.y = GetRandomValue(0, 1) ? 1.0f : -1.0f; // Randomize y-direction
		WaitTime(1.0f);
	}
	if(ballPos.x < 0) // if ball pass screen on left player two point
	{
		playerTwoScore++; 
		ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
		playerTwoPaddleY = 250.0f;
		playerOnePaddleY = 250.0f;
		ballSpeed.x = GetRandomValue(0, 1) ? 3.0f : -3.0f; // Randomize x-direction
		ballSpeed.y = GetRandomValue(0, 1) ? 1.0f : -1.0f; // Randomize y-direction
		WaitTime(1.0f);
	}

	//ball collision with top and bottom properties
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
	DrawCircleV(ballPos, ballRadius, WHITE);
	DrawRectangleRounded({10.0f, playerOnePaddleY, rectangleWidth, rectangleHeight}, roundness, segments, BLUE);
	DrawRectangleRounded({screenWidth - 20, playerTwoPaddleY, rectangleWidth, rectangleHeight}, roundness, segments, MAGENTA);
}