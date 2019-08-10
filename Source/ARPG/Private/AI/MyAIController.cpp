// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EngineUtils.h"
#include "PlayerCharacter.h"
#include "PrimaryAI.h"
#include "AIBase.h"

AMyAIController::AMyAIController()
{
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);

		if (BehaviorTree->BlackboardAsset)
		{
			Blackboard = BehaviorTree->BlackboardAsset;
		}
	}


}




void AMyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	AIPawn = Cast<AAIBase>(GetPawn());
}

ACharacterBase* AMyAIController::FindNearlyPlayer(float FindRadius)
{
	APlayerCharacter * ResultPlayer = nullptr;
	float ResultPlayerDistance = FindRadius;
	for (TActorIterator<APlayerCharacter> it(GetWorld(), APlayerCharacter::StaticClass()); it;++it)
	{
		APlayerCharacter* FindPlayerResult = *it;
		float BetweenDistance = (FindPlayerResult->GetActorLocation() - GetPawn()->GetActorLocation()).Size();
		if (BetweenDistance<ResultPlayerDistance)
		{
			ResultPlayer = FindPlayerResult;
			ResultPlayerDistance = BetweenDistance;
		}
	}
	return ResultPlayer;
}

void AMyAIController::LookAtPlayer(ACharacterBase* LookTarget)
{
	AIPawn->LookAtTarget(LookTarget);
}

void AMyAIController::UnLookAtPlayer()
{
	AIPawn->UnLookAtTarget();
}

FVector AMyAIController::GetPortrolPoint()
{
	FVector TargetPoint(AIPawn->GetActorLocation());
	TargetPoint.X += FMath::RandRange(-800.f, 800.f);
	TargetPoint.Y += FMath::RandRange(-800.f, 800.f);
	return TargetPoint;
}



bool AMyAIController::CastRandomSkill()
{
	for (uint8 it = 0; it < AIPawn->GetSkillComponent()->GetSkillArray().Num(); ++it)
		if (AIPawn->GetSkillComponent()->GetSkillArray()[it]->CanCast())
		{
			AIPawn->CastSkill(it);
			return true;
		}
	return false;
}

