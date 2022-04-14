#include "pch.h"
#include "Commands.h"

#include "PeterPepper.h"

PeterPepper_Die::PeterPepper_Die(PeterPepper* pPeterPepper)
	: m_pPeterPepperComponent{ pPeterPepper }
{
}
PeterPepper_KillEnemy::PeterPepper_KillEnemy(PeterPepper* pPeterPepper)
	: m_pPeterPepperComponent{ pPeterPepper }
{
}

void PeterPepper_Die::Execute()
{
	m_pPeterPepperComponent->Die();
}

void PeterPepper_KillEnemy::Execute()
{
	m_pPeterPepperComponent->KillEnemy();
}