// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkillCastInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USkillCastInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API ISkillCastInterface
{
	GENERATED_BODY()
protected:


	/*释放技能结束代理*/
	FOnMontageEnded EndDelegate;

	bool bCanCast;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	ISkillCastInterface();

	virtual void CastSkill() = 0;

	virtual void StopCast() = 0;

	virtual void OnCastEnd(class UAnimMontage* AnimMontage, bool bInterrupted) = 0;


	FORCEINLINE bool CanCast() const { return bCanCast; }
};
