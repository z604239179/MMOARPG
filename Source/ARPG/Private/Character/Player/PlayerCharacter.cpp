// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "Monster.h"
#include "EngineUtils.h"
#include "Weapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CheckSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("CheckSphereComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;


	CheckSphereComp->SetupAttachment(RootComponent);
	CheckSphereComp->SetSphereRadius(1500.f);
	CheckSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CheckSphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Item, ECR_Overlap);

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CharacterType = ECharacterType::Player;
	CurrentViewState = ViewState::UsualView;
	
	LockDistance = 5000.0f;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 88.f));
}

void APlayerCharacter::InitCharacter()
{
	if (HasAuthority())
	{
//		CurrentInfoData = GetController<AMyPlayerController>()->MyData;


		Super::InitCharacter();
	}
}

void APlayerCharacter::ClientInitCharacter_Implementation()
{

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CheckSphereComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &APlayerCharacter::OnPawnEnterCheckSphere);
	CheckSphereComp->OnComponentEndOverlap.AddUniqueDynamic(this, &APlayerCharacter::OnPawnLeaveCheckSphere);
	MyController = Cast<AMyPlayerController>(GetController());
	if (DefaultCurve)
	{
		FOnTimelineFloat HandleTimeline;
		HandleTimeline.BindUFunction(this, FName("CameraMove"));
		CameraMoveTimeLine.AddInterpFloat(DefaultCurve, HandleTimeline);
		CameraMoveTimeLine.SetLooping(false);
	}	
	
	//ClientInitCharacter();
}

void APlayerCharacter::CameraMove(float Val)
{

	SpringArmComp->TargetArmLength = FMath::Lerp(300.f, 200.f, Val);
	CameraComp->SetRelativeLocation(FMath::Lerp(FVector::ZeroVector, FVector(0, -60.f, 0), Val));
}


void APlayerCharacter::OnPawnEnterCheckSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACharacterBase* OverlapCharacter = Cast<ACharacterBase>(OtherActor);
	if (OverlapCharacter)
	{
		//OverlapCharacter->GetHealthBarWidget()->GetUserWidgetObject()
		OverlapCharacter->GetHealthComponent()->SetVisibility(true);
	}
}

void APlayerCharacter::OnPawnLeaveCheckSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacterBase* OverlapCharacter = Cast<ACharacterBase>(OtherActor);
	if (OverlapCharacter)
	{
		OverlapCharacter->GetHealthComponent()->SetVisibility(false);
	}
}

void APlayerCharacter::MoveForward_Implementation(FVector Direction, float Value)
{

	AddMovementInput(Direction, Value);

}


void APlayerCharacter::MoveRight_Implementation(FVector Direction, float Value)
{

	AddMovementInput(Direction, Value);

}




void APlayerCharacter::MoveUp_Implementation(float Value)
{

	AddMovementInput(GetActorUpVector(), Value);

}

void APlayerCharacter::ChangeViewState()
{
	switch (CurrentViewState)
	{
	case ViewState::UsualView:
		CameraMoveTimeLine.PlayFromStart();
		CurrentViewState = ViewState::LockingView;
		break;
	case ViewState::LockingView:
		CameraMoveTimeLine.ReverseFromEnd();
		CurrentViewState = ViewState::UsualView;
		break;
	default:
		break;
	}
}

class ACharacterBase* APlayerCharacter::FindNearlyMonster()
{
	ACharacterBase* MonsterTarget=nullptr;
	float BetweenDistance = LockDistance;
	TSubclassOf<AMonster> MonsterClass = AMonster::StaticClass();
	for (TActorIterator<AMonster> it(GetWorld(), MonsterClass); it; ++it)
	{
		AMonster* FindTarget = *it;
		if (((FindTarget->GetActorLocation() - GetActorLocation()).Size() < BetweenDistance)&&!FindTarget->GetActionState(ActionState::Dead))
		{
			MonsterTarget = FindTarget;
			BetweenDistance = (FindTarget->GetActorLocation() - GetActorLocation()).Size();
		}

	}
	return MonsterTarget;
}

void APlayerCharacter::LockTarget()
{
	if (GetActionState(ActionState::Locking))
	{
		UnLookAtTarget();
	}
	else LookAtTarget(FindNearlyMonster());
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraMoveTimeLine.TickTimeline(DeltaTime);

}



float APlayerCharacter::GetActorDeraction()
{
	
	float TempPawnYaw = GetMovementComponent()->Velocity.Rotation().Yaw;
	float TempCtrlYaw = GetActorRotation().Yaw;
	return FMath::FindDeltaAngleDegrees(TempPawnYaw, TempCtrlYaw);

}


void APlayerCharacter::UnLookAtTarget()
{
	AMonster* LookingMonster = Cast<AMonster>(LockingTarget);
	if (LookingMonster)
	{		
		LookingMonster->UnBecomeTarget();
	}
	ChangeViewState();
	Super::UnLookAtTarget();
}

void APlayerCharacter::LookAtTarget(ACharacterBase* LookTarget)
{
	if (LookTarget&&!LookTarget->GetActionState(ActionState::Dead))
	{
		Super::LookAtTarget(LookTarget);
		AMonster* LookingMonster = Cast<AMonster>(LookTarget);
		if (!LookingMonster->GetActionState(ActionState::Dead))
		{
			LookingMonster->BecomeTarget();
		}
		ChangeViewState();
	}
}


