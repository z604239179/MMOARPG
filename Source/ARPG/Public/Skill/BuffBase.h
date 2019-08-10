// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "BuffBase.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UBuffBase : public USkillBase
{
	GENERATED_BODY()
protected:
	bool bActive = false;
	class UPBuff* SkillInfo;
	class ACharacterBase* BuffOwner;

	FTimerHandle PersistentHandle;
public:
	UFUNCTION(BlueprintCallable)
	virtual void InitSkill(AActor* Owner, UPrimarySkill* _Info);

	UFUNCTION(BlueprintCallable)
	void ActiveBuff();
	UFUNCTION()
	void UnactiveBuff();
};
