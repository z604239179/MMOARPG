// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSkillBase.h"
#include "SkillComponent.generated.h"
class UAnimInstance;
class UPassiveSkillBase;
class UBuffBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	ACharacterBase* ComponentOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
		TArray<FPrimaryAssetId> SkillIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
		TArray<UCharacterSkillBase*> SkillInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
		TArray<UPassiveSkillBase*> PassiveSkillList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
		TArray<UBuffBase*> ActiveBuffList;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void CastSkill(uint8 SkillIndex);

	UFUNCTION()
		void CastEnd(uint8 SkillIndex);

	UFUNCTION(BlueprintCallable)
		bool AddPassiveSkill(UPassiveSkillBase* SkillRef);
	UFUNCTION(BlueprintCallable)
		bool RemovePassiveSkill(UPassiveSkillBase* SkillRef);

	bool AddBuffToList(UBuffBase* BuffRef);
	bool RemoveBuffFromList(UBuffBase* BuffRef);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE TArray<UCharacterSkillBase*>& GetSkillArray() { return SkillInstance; }

		
};
