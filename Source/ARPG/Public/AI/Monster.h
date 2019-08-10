// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBase.h"
#include "Monster.generated.h"

/**
 * 
 */

class AWeapon;

UCLASS()
class ARPG_API AMonster : public AAIBase
{
	GENERATED_BODY()
		
public:
	AMonster();

	void BecomeTarget();

	void UnBecomeTarget();

	virtual void Tick(float DeltaTime) override;

protected:


	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		class UDecalComponent* DecalComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		class UPawnSensingComponent * SensingComp;

		virtual void MultiDeath() override;

	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);

	UFUNCTION()
		void OnHearPlayer(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FTimerHandle TargetResetTimer;

	UFUNCTION()
		void ResetAIState();

};
