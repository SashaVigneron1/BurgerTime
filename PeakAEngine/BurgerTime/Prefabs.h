#pragma once

class GameObject;
class Scene;
void CreatePeterPepper(Scene* pScene, const glm::vec2& position = {});
void CreateLadder(Scene* pScene, float tileSize, const glm::vec2& position = {});
void CreatePlatform(Scene* pScene, float tileSize, const glm::vec2& position = {});
//void CreateLadderCollection(Scene* pScene, int nrLadders, const glm::vec2& position = {});
