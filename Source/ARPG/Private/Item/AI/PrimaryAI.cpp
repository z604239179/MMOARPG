// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimaryAI.h"

UPrimaryAI::UPrimaryAI()
{

	for (int32 it = 0; it < (int32)EPropertyName::MAX; ++it)
	{
		Attributes.Add((EPropertyName)it, 0);
	}

	AttackRange = 100.f;
}
