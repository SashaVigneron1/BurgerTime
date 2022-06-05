#include "pch.h"
#include "Commands.h"

#include "PeterPepper.h"

PeterPepper_MoveUp::PeterPepper_MoveUp(PeterPepper* pPeterPepper)
	: m_pPeterPepperComponent{ pPeterPepper }
{
}
void PeterPepper_MoveUp::Execute()
{
	m_pPeterPepperComponent->MoveUp();
}

PeterPepper_MoveDown::PeterPepper_MoveDown(PeterPepper* pPeterPepper)
	: m_pPeterPepperComponent{ pPeterPepper }
{
}
void PeterPepper_MoveDown::Execute()
{
	m_pPeterPepperComponent->MoveDown();
}


PeterPepper_MoveLeft::PeterPepper_MoveLeft(PeterPepper* pPeterPepper)
	: m_pPeterPepperComponent{ pPeterPepper }
{
}
void PeterPepper_MoveLeft::Execute()
{
	m_pPeterPepperComponent->MoveLeft();
}


PeterPepper_MoveRight::PeterPepper_MoveRight(PeterPepper* pPeterPepper)
	: m_pPeterPepperComponent{ pPeterPepper }
{
}
void PeterPepper_MoveRight::Execute()
{
	m_pPeterPepperComponent->MoveRight();
}

PeterPepper_SprayPepper::PeterPepper_SprayPepper(PeterPepper* pPeterPepper)
	: m_pPeterPepperComponent{ pPeterPepper }
{
}
void PeterPepper_SprayPepper::Execute()
{
	m_pPeterPepperComponent->SprayPepper();
}


