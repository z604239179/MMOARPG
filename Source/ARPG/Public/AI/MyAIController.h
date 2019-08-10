// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */

UCLASS()
class ARPG_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyAIController();
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree * BehaviorTree;

	class UBlackboardData* Blackboard;


	virtual void BeginPlay() override;

	virtual void Possess(APawn* InPawn) override;


public:


	//FORCEINLINE ACharacterInfoBase* GetCharacterInfo() { return CurrentInfoData; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class AAIBase* AIPawn;



	UFUNCTION(BlueprintCallable)
		class ACharacterBase* FindNearlyPlayer(float FindRadius);

	UFUNCTION(BlueprintCallable)
		void LookAtPlayer(ACharacterBase* LookTarget);

	UFUNCTION(BlueprintCallable)
		void UnLookAtPlayer();

	UFUNCTION(BlueprintPure)
		FVector GetPortrolPoint();


	UFUNCTION(BlueprintCallable)
		bool CastRandomSkill();
};
