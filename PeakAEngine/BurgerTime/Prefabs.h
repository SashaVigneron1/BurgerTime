#pragma once

enum class PlatformType;
enum class LadderType;
class GameObject;
class Scene;
void CreatePeterPepper(Scene* pScene, const glm::vec2& position = {});
void CreateLadder(Scene* pScene, LadderType type, float tileSize, const glm::vec2& position = {});
void CreatePlatform(Scene* pScene, PlatformType type, float tileSize, const glm::vec2& position = {});
//void CreateLadderCollection(Scene* pScene, int nrLadders, const glm::vec2& position = {});
