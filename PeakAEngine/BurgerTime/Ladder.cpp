#include "pch.h"
#include "Ladder.h"

Ladder::Ladder(GameObject* pGameObject, LadderType piece)
	: Component{pGameObject}
	, m_LadderPiece{piece}
{
}

Ladder::~Ladder()
{
}
