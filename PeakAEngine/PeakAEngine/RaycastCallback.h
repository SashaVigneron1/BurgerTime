#pragma once

#include "structs.h"
#include <b2_world_callbacks.h>
#include <b2_contact.h>

#include "PhysicsComponent.h"


class GameObject;

class RaycastCallback final : public b2RayCastCallback
{
public:
	RaycastCallback() = default;
	~RaycastCallback() override = default;
	RaycastCallback(const RaycastCallback& other) = delete;
	RaycastCallback(RaycastCallback&& other) noexcept = delete;
	RaycastCallback& operator=(const RaycastCallback& other) = delete;
	RaycastCallback& operator=(RaycastCallback&& other) noexcept = delete;

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, float fraction) override
    {
        m_fixture = fixture;
        auto obj1 = reinterpret_cast<PhysicsComponent*>(fixture->GetBody()->GetUserData().pointer);
        m_pOther = obj1->GetGameObject();
        m_point = Vector2f{ point.x, point.y };
        m_normal = Vector2f{ normal.x, normal.y };
        m_fraction = fraction;
        return fraction;
    }

    GameObject* m_pOther;
    b2Fixture* m_fixture;
    Vector2f m_point;
    Vector2f m_normal;
    float m_fraction;
private:

};

