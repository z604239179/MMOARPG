// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Water.generated.h"

UCLASS()
class ARPG_API AWater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Propertes")
		class UStaticMeshComponent* WaterPanel;

	UPROPERTY(VisibleDefaultsOnly, Category = "Propertes")
		class UBoxComponent* WaterVolumn;

	UPROPERTY(VisibleDefaultsOnly, Category = "Propertes")
		class UPostProcessComponent* PostProcessComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Propertes")
		class UAudioComponent* AudioComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundBase* HardSplash;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundBase* SoftSplash;


	UFUNCTION()
		void OnSomethingEnterWater(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//UFUNCTION()
	//	void OnSomethingLeaveWater(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//UFUNCTION()
	//	void OnSomethingEnterVolumn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
