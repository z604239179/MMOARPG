// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "PassiveSkillBase.generated.h"

/**
 * 
 */
class UBuffBase;

UCLASS()
class ARPG_API UPassiveSkillBase : public USkillBase
{
	GENERATED_BODY()
protected:
	class UPPassiveSkill* SkillInfo;

	class ACharacterBase* SkillOwner;

	TArray<UBuffBase*> BuffList;

	bool bActive = false;
public:
	UFUNCTION(BlueprintCallable)
	virtual void InitSkill(AActor* Owner, UPrimarySkill* _Info);
	UFUNCTION(BlueprintCallable)
	virtual void ActivePassiveSkill();
	virtual void UnActivePassiveSkill();
};
