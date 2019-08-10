// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "Components/BoxComponent.h"
#include "DamageBoxBase.generated.h"

UCLASS()
class ARPG_API ADamageBoxBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageBoxBase();
		

	class ACharacterBase* DamageSource;

	TSubclassOf<UDamageType> MyDamageType;

	class AWeapon* SourceWeapon;

	void InitDamageBox(TSubclassOf<UDamageType> DamageType, FVector BoxSize = FVector(3.f,3.f,3.f));
protected:

	virtual void BeginPlay()override;

	FTimerHandle timerhandle;

	UPROPERTY()
		TArray<ACharacterBase*> DamagedPawn;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
		UBoxComponent * DamageBox;

	UFUNCTION()
		virtual void OnDamageActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
