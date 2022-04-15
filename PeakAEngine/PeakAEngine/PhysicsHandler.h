#pragma once

struct b2ContactImpulse;
struct b2Manifold;
class b2Contact;
class b2World;
class ContactListener;

class PhysicsHandler final
{
public:
	PhysicsHandler();
	~PhysicsHandler();
	PhysicsHandler(const PhysicsHandler& other) = delete;
	PhysicsHandler(PhysicsHandler&& other) noexcept = delete;
	PhysicsHandler& operator=(const PhysicsHandler& other) = delete;
	PhysicsHandler& operator=(PhysicsHandler&& other) noexcept = delete;

	b2World* GetPhysicsWorld();
	void StopContactListener();

private:
	ContactListener* m_pContactListener;
};
