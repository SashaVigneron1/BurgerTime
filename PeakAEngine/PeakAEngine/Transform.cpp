#include "PeakAEnginePCH.h"
#include "Transform.h"


Transform::Transform(const glm::vec3 position, GameObject* attachedObj)
	: Component{attachedObj}
	, m_WorldPosition{ position }
	, m_LocalPosition{ position }
{
	
}

Transform::~Transform()
{
	
}


void Transform::Update()
{
	
}

void Transform::FixedUpdate()
{
	
}


void Transform::SetWorldPosition(const float x, const float y, const float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void Transform::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}
