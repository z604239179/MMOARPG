// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ARPG.h"
#include "CharacterInfoBase.h"
#include "HealthComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_API UHealthComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	void InitHealthComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable)
		void ClientInit(ACharacterInfoBase* InitInfo);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitWidget();

	UPROPERTY(Replicated, BlueprintReadOnly)
		float MaxHealth;
	UPROPERTY(Replicated, BlueprintReadOnly)
		float CurrentHealth;
	UPROPERTY(Replicated, BlueprintReadOnly)
		float MaxMana;
	UPROPERTY(Replicated, BlueprintReadOnly)
		float CurrentMana;

	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }
	FORCEINLINE float GetCurrentMana() { return CurrentMana; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetHealthPercent() { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetManaPercent() { return CurrentMana / MaxMana; }

	UFUNCTION(Server, Reliable, WithValidation)
		void SetCurrentHealth(float InValue);

	UFUNCTION(Server, Reliable, WithValidation)
		void SetCurrentMana(float InValue);

	UFUNCTION(Server, Reliable, WithValidation)
		void SetMaxHealth(float InValue);

	UFUNCTION(Server, Reliable, WithValidation)
		void SetMaxMana(float InValue);

protected:
	UFUNCTION()
		void OnValueChanged(EPropertyName ChangedName, const FPropertesValue& ChangedValue);

	UFUNCTION()
		void OnGetDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
};
