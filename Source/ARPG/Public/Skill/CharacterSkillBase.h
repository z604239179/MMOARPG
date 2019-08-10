// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillCastInterface.h"
#include "CharacterSkillBase.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCharacterSkillBase : public USkillBase,public ISkillCastInterface
{
	GENERATED_BODY()
public:
	UCharacterSkillBase();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Skill")
		class USkillComponent* OwnerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
		float CurrentCD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
		float MaxCD;

	FTimerHandle SkillTimerHandle;

	class ACharacterBase* SkillOwner;
	
	class UPCharacterSkill* SkillInfo;
public:

	UPROPERTY(BlueprintReadOnly)
		uint8 SkillIndex;

	virtual void InitSkill(AActor* Owner, UPrimarySkill* _Info);

	/*施放技能相关*/
	virtual void CastSkill()override;
	virtual void StopCast() override {};
	UFUNCTION()
	virtual void OnCastEnd(UAnimMontage* AnimMontage, bool bInterrupted) override;


	void GetColdDownTime(float &CurrentTime, float &MaxTime);

	UFUNCTION()
		void ColdDown();
};
