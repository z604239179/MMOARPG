// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "ARPG.h"
#include "AIBase.generated.h"

UENUM(BlueprintType)
enum class EAIState :uint8
{
	Idle,
	Protrol,
	Fight
};

UCLASS()
class ARPG_API AAIBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
		EAIState CurrentState;

	/*如果需要直接将AI放置在场景中，该值必须设置*/
	UPROPERTY(EditDefaultsOnly, Category = "PlaceInWorldSetting")
		FPrimaryAssetId AIInfoClass;
	/****************************************/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State", meta = (EditCondition = "bIsProtrol"))
		TArray<AActor*> ProtrolTarget;

	UPROPERTY(Replicated)
		class ACharacterInfoBase* CurrentInfoData;

private:
	UPROPERTY(Replicated)
		class UPrimaryAI* AIInfo;

public:	

	FORCEINLINE UPrimaryAI* GetBasicAIInfo() { return AIInfo; }
	FORCEINLINE void SetBasicAIInfo(UPrimaryAI* In_Info) {AIInfo = In_Info;}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
		bool bIsProtrol;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitCharacter() override;

	virtual void LookAtTarget(ACharacterBase* LookTarget) override;

	virtual void UnLookAtTarget() override;

	virtual void HandleGetDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;

	FORCEINLINE virtual ACharacterInfoBase* GetCurrentInfoData() override { return CurrentInfoData; }
};
