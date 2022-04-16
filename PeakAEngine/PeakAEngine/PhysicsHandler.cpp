#include "PeakAEnginePCH.h"
#include "PhysicsHandler.h"

#include "PhysicsComponent.h"

#include "box2d.h"

class ContactListener final : public b2ContactListener
{
public:
	ContactListener();
	~ContactListener() override;
	ContactListener(const ContactListener& other) = delete;
	ContactListener(ContactListener&& other) noexcept = delete;
	ContactListener& operator=(const ContactListener& other) = delete;
	ContactListener& operator=(ContactListener&& other) noexcept = delete;

	b2World* GetPhysicsWorld() { return m_pb2World; }

	void StopContactListener();
	
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
private:
	b2World* m_pb2World{};
};

void ContactListener::StopContactListener()
{
	m_pb2World->SetContactListener(nullptr);
}

void ContactListener::BeginContact(b2Contact* contact)
{
	auto obj1 = reinterpret_cast<PhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	auto obj2 = reinterpret_cast<PhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

	if (obj1 && obj2)
	{
		if (obj1->OnTriggerEnter != nullptr) obj1->OnTriggerEnter(obj2);
		if (obj2->OnTriggerEnter != nullptr) obj2->OnTriggerEnter(obj1);
	}
}
void ContactListener::EndContact(b2Contact* contact)
{
	auto obj1 = reinterpret_cast<PhysicsComponent*>(contact->GetFixtureA()->GetUserData().pointer);
	auto obj2 = reinterpret_cast<PhysicsComponent*>(contact->GetFixtureB()->GetUserData().pointer);

	if (obj1 && obj2)
	{
		if (obj1->OnTriggerExit != nullptr) obj1->OnTriggerExit(obj2);
		if (obj2->OnTriggerExit != nullptr) obj2->OnTriggerExit(obj1);
	}
}
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2ContactListener::PreSolve(contact, oldManifold);
}
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	b2ContactListener::PostSolve(contact, impulse);
}

ContactListener::ContactListener()
{
	const b2Vec2 gravity = { 0,0 };
	m_pb2World = new b2World(gravity);
	m_pb2World->SetContactListener(this);
}
ContactListener::~ContactListener()
{
	delete m_pb2World;
}

PhysicsHandler::PhysicsHandler()
	: m_pContactListener{new ContactListener{}}
{
}
PhysicsHandler::~PhysicsHandler()
{
	delete m_pContactListener;
}

b2World* PhysicsHandler::GetPhysicsWorld()
{
	return m_pContactListener->GetPhysicsWorld();
}

void PhysicsHandler::StopContactListener()
{
	m_pContactListener->StopContactListener();
}
