// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "GamingHUD.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "ARPGGameModeBase.h"


AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;	
	
	FwdAxis = 0;
	RgtAxis = 0;
	
}

void AMyPlayerController::OnRep_MyData()
{
	MyHUD = Cast<AGamingHUD>(GetHUD());
	if (MyHUD)
	{
		MyHUD->CreateUI();
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyHUD = Cast<AGamingHUD>(GetHUD());
	
}

void AMyPlayerController::LookUp(float Value)
{
	if (GetPawn())
	{
		AddPitchInput(Value);
	}
}

void AMyPlayerController::Turn(float Value)
{
	if (GetPawn())
	{
		AddYawInput(Value);
		
	}
}





void AMyPlayerController::MoveForward(float Value)
{
	if (GetPawn())
	{
		FwdAxis = Value;
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		if (Value != 0)
		{
			if (HasAuthority())
			{
				GetMyCharacter()->MoveForward(Direction, Value);
				return;
			}
			ServerMoveForward(Value, Direction);
		}
	}
}



void AMyPlayerController::ServerMoveForward_Implementation(float Value, FVector mDirection)
{

	GetMyCharacter()->MoveForward(mDirection, Value);
}

bool AMyPlayerController::ServerMoveForward_Validate(float Value, FVector mDirection)
{
	return true;
}

void AMyPlayerController::MoveRight(float Value)
{
	if (GetPawn())
	{
		RgtAxis = Value;
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		if (Value != 0)
		{
			if (HasAuthority())
			{
				GetMyCharacter()->MoveRight(Direction, Value);
				return;
			}
			ServerMoveRight(Value, Direction);
		}
	}
}

void AMyPlayerController::MoveUp(float Value)
{
	if (GetPawn())
	{
		ServerMoveUp(Value);
	}
}

void AMyPlayerController::ServerMoveUp(float Value)
{
	GetMyCharacter()->MoveUp(Value);
}

void AMyPlayerController::ServerMoveRight_Implementation(float Value, FVector mDirection)
{
	GetMyCharacter()->MoveRight(mDirection, Value);
}

bool AMyPlayerController::ServerMoveRight_Validate(float Value, FVector mDirection)
{
	return true;
}

void AMyPlayerController::Run()
{
	if (GetPawn())
	{
		if (HasAuthority())
		{
			GetMyCharacter()->ChangeSpeed(GetMyCharacter()->RunSpeed);
			return;
		}
		ServerRun();
	}
}

void AMyPlayerController::ServerRun_Implementation()
{

	GetMyCharacter()->ChangeSpeed(GetMyCharacter()->RunSpeed);
}

bool AMyPlayerController::ServerRun_Validate()
{
	return true;
}

void AMyPlayerController::EndRun()
{
	if (GetPawn())
	{
		if (HasAuthority())
		{
			GetMyCharacter()->ChangeSpeed(GetMyCharacter()->WalkSpeed);
			return;
		}
		ServerEndRun();
	}
}

void AMyPlayerController::ServerEndRun_Implementation()
{
	GetMyCharacter()->ChangeSpeed(GetMyCharacter()->WalkSpeed);
}

bool AMyPlayerController::ServerEndRun_Validate()
{
	return true;
}


void AMyPlayerController::LockTarget()
{
	if (GetPawn())
	{
		if (GetMyCharacter()->GetActionState(ActionState::Locking))
		{
			GetMyCharacter()->UnLookAtTarget();
		}
		else
		{
			GetMyCharacter()->LookAtTarget(GetMyCharacter()->FindNearlyMonster());
		}
	}
}




void AMyPlayerController::UseLeftWeapon_Implementation()
{
	if (GetPawn())
	{
		GetMyCharacter()->UseWeapon(true);
	}
}

bool AMyPlayerController::UseLeftWeapon_Validate()
{
	return true;
}

void AMyPlayerController::StopLeftWeapon_Implementation()
{
	if (GetPawn())
	{
		GetMyCharacter()->StopUseWeapon(true);
		return;
	}
}

bool AMyPlayerController::StopLeftWeapon_Validate()
{
	return true;
}



void AMyPlayerController::UseRightWeapon_Implementation()
{
	if (GetPawn())
	{
		GetMyCharacter()->UseWeapon(false);
		return;
	}
}

bool AMyPlayerController::UseRightWeapon_Validate()
{
	return true;
}


void AMyPlayerController::StopRightWeapon_Implementation()
{
	if (GetPawn())
	{
		GetMyCharacter()->StopUseWeapon(false);
		return;
	}
}

bool AMyPlayerController::StopRightWeapon_Validate()
{
	return true;
}

void AMyPlayerController::DodgeEvent()
{
	if (GetPawn())
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		FVector DodgeVec;
		if (FwdAxis == 0 && RgtAxis == 0)
		{
			DodgeVec = GetPawn()->GetActorForwardVector();
		}
		else
		{
			DodgeVec = ForwardDirection * FwdAxis + RightDirection * RgtAxis;
		}
		ServerDodge(DodgeVec);
	}
}



void AMyPlayerController::ServerDodge_Implementation(FVector DodgeVec)
{

	GetMyCharacter()->Dodge(DodgeVec);
}

bool AMyPlayerController::ServerDodge_Validate(FVector DodgeVec)
{
	return true;
}

void AMyPlayerController::JumpEvent()
{
	if (GetPawn())
	{
		if (HasAuthority())
		{
			GetMyCharacter()->Jumping();
			return;
		}
		ServerJump();
	}
}

void AMyPlayerController::ServerJump_Implementation()
{
	GetMyCharacter()->Jumping();
}

bool AMyPlayerController::ServerJump_Validate()
{
	return true;
}


void AMyPlayerController::CastSkill(uint8 SkillIndex)
{
	if (GetPawn())
	{
		if (HasAuthority())
		{
			GetMyCharacter()->CastSkill(SkillIndex);
			return;
		}
		ServerCastSkill(SkillIndex);
	}
}



void AMyPlayerController::ServerCastSkill_Implementation(uint8 SkillIndex)
{
	GetMyCharacter()->CastSkill(SkillIndex);
}

bool AMyPlayerController::ServerCastSkill_Validate(uint8 SkillIndex)
{
	return true;
}


void AMyPlayerController::CallInventory()
{
	if (MyHUD)
	{
		if (MyHUD->CallInventory())
		{
			SetInputMode(FInputModeGameAndUI());
			bShowMouseCursor = true;
			return;
		}
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void AMyPlayerController::CallCharacterPanel()
{
	if (MyHUD)
	{
		if (MyHUD->CallCharacterPanel())
		{
			SetInputMode(FInputModeGameAndUI());
			bShowMouseCursor = true;
			return;
		}
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}


void AMyPlayerController::CallCheatPanel()
{
	if (MyHUD)
	{
		MyHUD->CallCheatPanel();
	}
}

void AMyPlayerController::InitMyPawn(ACharacterBase* aPawn)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.Instigator = Instigator;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want player states to save into a map

	MyData = GetWorld()->SpawnActor<APlayerInfoData>(APlayerInfoData::StaticClass(), SpawnInfo);
	MyData->SetPlayerName(FString::FromInt(NetworkIndex));
	OnRep_MyData();
	aPawn->InitCharacter();

}




APlayerCharacter* AMyPlayerController::GetMyCharacter()
{

	return Cast<APlayerCharacter>(GetPawn());

}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetMyCharacter())
	{
		if (GetMyCharacter()->GetLockingTarget())
		{
			FRotator TempRot = (GetMyCharacter()->GetLockingTarget()->GetActorLocation() - GetMyCharacter()->GetCameraComp()->GetComponentLocation()).Rotation();
			TempRot.Pitch = 0;
			FRotator MyRot= GetControlRotation();
			SetControlRotation(FMath::Lerp(MyRot, TempRot, DeltaSeconds*10));
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	InputComponent->BindAxis("LookUp", this, &AMyPlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &AMyPlayerController::Turn);
	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
	InputComponent->BindAxis("MoveUp", this, &AMyPlayerController::MoveUp);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayerController::Run);
	InputComponent->BindAction("Run", IE_Released, this, &AMyPlayerController::EndRun);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &AMyPlayerController::DodgeEvent);
	InputComponent->BindAction("LockTarget", IE_Pressed, this, &AMyPlayerController::LockTarget);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::JumpEvent);

	InputComponent->BindAction("UseLeftNormal", IE_Pressed, this, &AMyPlayerController::UseLeftWeapon);
	InputComponent->BindAction("UseRightNormal", IE_Pressed, this, &AMyPlayerController::UseRightWeapon);
	InputComponent->BindAction("UseLeftNormal", IE_Released, this, &AMyPlayerController::StopLeftWeapon);
	InputComponent->BindAction("UseRightNormal", IE_Released, this, &AMyPlayerController::StopRightWeapon);


	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMyPlayerController::CallInventory);
	InputComponent->BindAction("CharacterPanel", IE_Pressed, this, &AMyPlayerController::CallCharacterPanel);
	InputComponent->BindAction("Cheat", IE_Pressed, this, &AMyPlayerController::CallCheatPanel);
	
}






void AMyPlayerController::SendMessage_Implementation(const FString& msg)
{
	Cast<AARPGGameModeBase>(GetWorld()->GetAuthGameMode())->BroadcastMessage(msg,NetworkIndex);
}

bool AMyPlayerController::SendMessage_Validate(const FString& msg)
{
	return true;
}


void AMyPlayerController::ReceiveMessage_Implementation(const FString& msg, const FString& InstigaterName)
{
	if (MyHUD)
	{
		MyHUD->AddMessage(msg, InstigaterName);
	}
}


void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps)const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);



	// Value is already updated locally, skip in replication step

	DOREPLIFETIME(AMyPlayerController, MyData);

	DOREPLIFETIME_CONDITION(AMyPlayerController, NetworkIndex, COND_InitialOnly);

	/* If we did not display the current inventory on the player mesh we couldoptimize replication by using this replication condition. */


}