#pragma once
#include "PeakAEngine/Command.h"

class PeterPepper_Die final : public Command
{

public:
	// Using component instead of gameobj to prevent GetComponent in hotcodepart

	PeterPepper_Die(PeterPepper* pPeterPepper);
	virtual ~PeterPepper_Die() override = default;
	PeterPepper_Die(const PeterPepper_Die& other) = delete;
	PeterPepper_Die(PeterPepper_Die&& other) noexcept = delete;
	PeterPepper_Die& operator=(const PeterPepper_Die& other) = delete;
	PeterPepper_Die& operator=(PeterPepper_Die&& other) noexcept = delete;

	virtual void Execute() override;

private:
	PeterPepper* m_pPeterPepperComponent;
};
class PeterPepper_KillEnemy final : public Command
{

public:
	// Using component instead of gameobj to prevent GetComponent in hotcodepart

	PeterPepper_KillEnemy(PeterPepper* pPeterPepper);
	virtual ~PeterPepper_KillEnemy() override = default;
	PeterPepper_KillEnemy(const PeterPepper_KillEnemy& other) = delete;
	PeterPepper_KillEnemy(PeterPepper_KillEnemy&& other) noexcept = delete;
	PeterPepper_KillEnemy& operator=(const PeterPepper_KillEnemy& other) = delete;
	PeterPepper_KillEnemy& operator=(PeterPepper_KillEnemy&& other) noexcept = delete;

	virtual void Execute() override;

private:
	PeterPepper* m_pPeterPepperComponent;
};