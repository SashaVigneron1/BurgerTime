#pragma once
#include "BurgerPiece.h"
#include "BurgerTime.h"

class Ladder;
class BurgerCatcher;
enum class PlatformType;
enum class LadderType;
class GameObject;
class Scene;

void CreatePeterPepper(Scene* pScene, const glm::vec2& position = {}, int controllerId = -1);
void CreateEnemy(Scene* pScene, const glm::vec2& position = {});
Ladder* CreateLadder(Scene* pScene, float tileSize, const glm::vec2& position = {});
GameObject* CreatePlatform(Scene* pScene, PlatformType type, float tileSize, const glm::vec2& position = {});
BurgerPiece* CreateBurgerIngredient(Scene* pScene, BurgerPieceType type, float tileSize, const glm::vec2& position = {});
BurgerCatcher* CreateBurgerCatcher(Scene* pScene, float tileSize, const glm::vec2& position = {});

void CreateMainMenu(Scene* pScene, BurgerTime* pGame);
void CreateUI(Scene* pScene, int indexCount);

void CreateEnemySpawner(Scene* pScene, Level* pLevel, const glm::vec2 position = {});
