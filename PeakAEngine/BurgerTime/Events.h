#pragma once

enum class Event
{
	OnPlayerDied = 0,

	OnUsePepper = 10,
	OnBurgerPieceDown = 11,

	OnBurgerFell = 10,
	OnBurgerFellOneEnemy = 11,
	OnBurgerFellTwoEnemies = 12,
	OnBurgerFellThreeEnemies = 13,
	OnBurgerFellFourEnemies = 14,
	OnBurgerFellFiveEnemies = 15,
	OnBurgerFellSixEnemies = 16,



	OnGameStarted = 20,
	GameOver = 21,
	OnLevelComplete = 22




};