// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"
/**
 * 
 */
UCLASS(Blueprintable)
class ARPG_API USkillBase : public UObject
{
	GENERATED_BODY()
public:

	USkillBase();

private:

	class UPrimarySkill* SkillInfo;

public:
	virtual void InitSkill(AActor* Owner, UPrimarySkill* _Info);

	FORCEINLINE UPrimarySkill* GetBasicSkillInfo() { return SkillInfo; }

};
