#pragma once
#include "PeakAEngine/Command.h"

class PeterPepper_MoveUp final : public Command
{

public:
	PeterPepper_MoveUp(PeterPepper* pPeterPepper);
	virtual ~PeterPepper_MoveUp() override = default;
	PeterPepper_MoveUp(const PeterPepper_MoveUp& other) = delete;
	PeterPepper_MoveUp(PeterPepper_MoveUp&& other) noexcept = delete;
	PeterPepper_MoveUp& operator=(const PeterPepper_MoveUp& other) = delete;
	PeterPepper_MoveUp& operator=(PeterPepper_MoveUp&& other) noexcept = delete;

	virtual void Execute() override;
private:
	PeterPepper* m_pPeterPepperComponent;
};

class PeterPepper_MoveDown final : public Command
{

public:
	PeterPepper_MoveDown(PeterPepper* pPeterPepper);
	virtual ~PeterPepper_MoveDown() override = default;
	PeterPepper_MoveDown(const PeterPepper_MoveDown& other) = delete;
	PeterPepper_MoveDown(PeterPepper_MoveDown&& other) noexcept = delete;
	PeterPepper_MoveDown& operator=(const PeterPepper_MoveDown& other) = delete;
	PeterPepper_MoveDown& operator=(PeterPepper_MoveDown&& other) noexcept = delete;

	virtual void Execute() override;
private:
	PeterPepper* m_pPeterPepperComponent;
};

class PeterPepper_MoveLeft final : public Command
{

public:
	PeterPepper_MoveLeft(PeterPepper* pPeterPepper);
	virtual ~PeterPepper_MoveLeft() override = default;
	PeterPepper_MoveLeft(const PeterPepper_MoveLeft& other) = delete;
	PeterPepper_MoveLeft(PeterPepper_MoveLeft&& other) noexcept = delete;
	PeterPepper_MoveLeft& operator=(const PeterPepper_MoveLeft& other) = delete;
	PeterPepper_MoveLeft& operator=(PeterPepper_MoveLeft&& other) noexcept = delete;

	virtual void Execute() override;
private:
	PeterPepper* m_pPeterPepperComponent;
};

class PeterPepper_MoveRight final : public Command
{

public:
	PeterPepper_MoveRight(PeterPepper* pPeterPepper);
	virtual ~PeterPepper_MoveRight() override = default;
	PeterPepper_MoveRight(const PeterPepper_MoveRight& other) = delete;
	PeterPepper_MoveRight(PeterPepper_MoveRight&& other) noexcept = delete;
	PeterPepper_MoveRight& operator=(const PeterPepper_MoveRight& other) = delete;
	PeterPepper_MoveRight& operator=(PeterPepper_MoveRight&& other) noexcept = delete;

	virtual void Execute() override;
private:
	PeterPepper* m_pPeterPepperComponent;
};