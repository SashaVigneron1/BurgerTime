#include "pch.h"
#include "Ladder.h"

Ladder::Ladder(GameObject* pGameObject, LadderPiece piece)
	: Component{pGameObject}
	, m_LadderPiece{piece}
{
}

Ladder::~Ladder()
{
}
