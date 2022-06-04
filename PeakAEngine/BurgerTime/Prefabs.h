#pragma once
#include "BurgerPiece.h"
#include "BurgerTime.h"

class BurgerCatcher;
enum class PlatformType;
enum class LadderType;
class GameObject;
class Scene;

void CreatePeterPepper(Scene* pScene, const glm::vec2& position = {});
void CreateLadder(Scene* pScene, float tileSize, const glm::vec2& position = {});
void CreatePlatform(Scene* pScene, PlatformType type, float tileSize, const glm::vec2& position = {});
void CreateBurgerIngredient(Scene* pScene, BurgerPieceType type, float tileSize, const glm::vec2& position = {});
BurgerCatcher* CreateBurgerCatcher(Scene* pScene, float tileSize, const glm::vec2& position = {});

void CreateMainMenu(Scene* pScene, BurgerTime* pGame);
void CreateUI(Scene* pScene);
