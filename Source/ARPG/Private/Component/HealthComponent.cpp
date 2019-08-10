// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "CharacterBase.h"
#include "Net/UnrealNetwork.h"
#include "Damage/DamageTypeBase.h"
#include "UI_HealthBar.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bReplicates = true;
}



void UHealthComponent::InitHealthComponent()
{

	ACharacterInfoBase* TempInfo = Cast<ACharacterBase>(GetOwner())->GetCurrentInfoData();
	MaxHealth = TempInfo->GetAttributefromName(EPropertyName::Health);
	MaxMana = TempInfo->GetAttributefromName(EPropertyName::Mana);
	CurrentHealth = MaxHealth;
	CurrentMana = MaxMana;
	FTimerHandle InitHandle;
	//GetWorld()->GetTimerManager().SetTimer(InitHandle, this, &UHealthComponent::ClientInit, 2.f);
	ClientInit(TempInfo);
}


void UHealthComponent::ClientInit_Implementation(ACharacterInfoBase* InitInfo)
{
	if (InitInfo)
	{
		InitInfo->ValueChangedHandle.AddDynamic(this, &UHealthComponent::OnValueChanged);
		
	}
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	// ...
	Super::BeginPlay();

	Cast<ACharacterBase>(GetOwner())->OnTakeDamage.AddDynamic(this, &UHealthComponent::OnGetDamage);

}



// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetWorld()->GetFirstPlayerController())
	{
		SetWorldRotation(FRotator(0, (GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation() - GetComponentLocation()).Rotation().Yaw, 0));
	}
	// ...
}





void UHealthComponent::InitWidget()
{
	Super::InitWidget();
	UUI_HealthBar* HealthBar = Cast<UUI_HealthBar>(Widget);
	if (HealthBar)
	{
		HealthBar->OwnPawn = Cast<ACharacterBase>(GetOwner());
	}
}



void UHealthComponent::SetCurrentHealth_Implementation(float InValue)
{
	CurrentHealth = InValue >= MaxHealth ? MaxHealth : InValue;
	if (CurrentHealth <= 0)
	{
		Cast<ACharacterBase>(GetOwner())->Death();
	}
}

bool UHealthComponent::SetCurrentHealth_Validate(float InValue)
{
	return true;
}

void UHealthComponent::SetCurrentMana_Implementation(float InValue)
{
	CurrentMana = InValue >= MaxMana ? MaxMana : InValue;
}

bool UHealthComponent::SetCurrentMana_Validate(float InValue)
{
	return true;
}

void UHealthComponent::SetMaxHealth_Implementation(float InValue)
{
	MaxHealth = InValue;
}

bool UHealthComponent::SetMaxHealth_Validate(float InValue)
{
	return true;
}

void UHealthComponent::SetMaxMana_Implementation(float InValue)
{
	MaxMana = InValue;
}

bool UHealthComponent::SetMaxMana_Validate(float InValue)
{
	return true;
}

void UHealthComponent::OnValueChanged(EPropertyName ChangedName, const FPropertesValue& ChangedValue)
{
	switch (ChangedName)
	{
	case EPropertyName::Health:
		SetMaxHealth(ChangedValue.BasicValue + ChangedValue.AddtiveValue);
		break;
	case EPropertyName::Mana:
		SetMaxMana(ChangedValue.BasicValue + ChangedValue.AddtiveValue);
		break;
	default:
		break;
	}
}

void UHealthComponent::OnGetDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	const UDamageTypeBase* TempDamageType = Cast<UDamageTypeBase>(DamageType);
	if (TempDamageType)
	{
		switch (TempDamageType->DamageSubType)
		{
		case EDamageSubType::HealthDamage:
		{
			CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, CurrentHealth - Damage);
			if (CurrentHealth <= 0)
			{
				Cast<ACharacterBase>(GetOwner())->Death();
			}
		}
		break;

		case EDamageSubType::ManaDamage:
		{
			CurrentMana = FMath::Clamp(CurrentMana - Damage, 0.0f, CurrentMana - Damage);

		}
		break;

		case EDamageSubType::StaminaDamage:
		{
			//	Stamina = FMath::Clamp(Stamina - Damage, 0.0f, Stamina - Damage);
		}
		break;
		default:
			break;
		}
	}

}


void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps)const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);



	// Value is already updated locally, skip in replication step

	DOREPLIFETIME(UHealthComponent, MaxHealth);
	DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, MaxMana);
	DOREPLIFETIME(UHealthComponent, CurrentMana);

}
