// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
#include"Components/DecalComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "PlayerCharacter.h"
#include "Weapon.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	DecalComp=CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComp"));

	DecalComp->SetupAttachment(RootComponent);
	DecalComp->SetRelativeRotation(FRotator(90.f, 0, 0));
	DecalComp->SetRelativeLocation(FVector(0, 0, -120.f));
	DecalComp->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));

	DecalComp->SetVisibility(false);

	SensingComp->SightRadius = 2000.f;


}

void AMonster::BecomeTarget()
{

	DecalComp->SetVisibility(true);
}

void AMonster::UnBecomeTarget()
{

	DecalComp->SetVisibility(false);
}


void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AMonster::BeginPlay()
{
	Super::BeginPlay();
	SensingComp->OnSeePawn.AddDynamic(this, &AMonster::OnSeePlayer);
	SensingComp->OnHearNoise.AddDynamic(this, &AMonster::OnHearPlayer);

}

void AMonster::MultiDeath()
{
	UnBecomeTarget();
	Super::MultiDeath();
}

void AMonster::OnSeePlayer(APawn* Pawn)
{
	if (!GetActionState(ActionState::Dead))
	{
		if (LockingTarget)
		{
			GetWorldTimerManager().ClearTimer(TargetResetTimer);
			GetWorldTimerManager().SetTimer(TargetResetTimer, this, &AMonster::ResetAIState, 5.f, false);
			return;
		}
		ACharacterBase *PlayerPawn = Cast<ACharacterBase>(Pawn);
		if (PlayerPawn->CharacterType == ECharacterType::Player && !PlayerPawn->GetActionState(ActionState::Dead))
		{
			LookAtTarget(PlayerPawn);
			GetWorldTimerManager().SetTimer(TargetResetTimer, this, &AMonster::ResetAIState, 5.f, false);
		}
	}
	else
	{
		SensingComp->SetActive(false);
	}
}

void AMonster::OnHearPlayer(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (!GetActionState(ActionState::Dead))
	{
		ACharacterBase *PlayerPawn = Cast<ACharacterBase>(NoiseInstigator);
		if (PlayerPawn->CharacterType == ECharacterType::Player && !PlayerPawn->GetActionState(ActionState::Dead))
		{
			LookAtTarget(PlayerPawn);
		}
	}
	else
	{
		SensingComp->SetActive(false);
	}
}

void AMonster::ResetAIState()
{
	GetWorldTimerManager().ClearTimer(TargetResetTimer);
	UnLookAtTarget();
}

