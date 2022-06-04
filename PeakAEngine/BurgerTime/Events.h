#pragma once

enum class Event
{
	OnPlayerDied = 0,

	OnBurgerFell = 1,
	OnEnemyDied = 2,
	OnBurgerPieceDown = 4,

	OnGameStarted = 3,

	OnUsePepper = 5,

	OnLevelComplete = 5,
	GameOver = 7


};