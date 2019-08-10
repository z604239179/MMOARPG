// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Components/TimelineComponent.h"
#include "MyPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

UENUM()
enum class ViewState :uint8
{
	UsualView,
	LockingView
};

UCLASS()
class ARPG_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	virtual void InitCharacter() override;

	UFUNCTION(Client,Reliable)
		void ClientInitCharacter();
protected:

	/*ÉãÏñ»úµ¯»É±Û*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmComp;

	/*½ÇÉ«ÉãÏñ»ú*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComp;

	/*ÑªÌõÏÔÊ¾·¶Î§*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Camera")
		class USphereComponent* CheckSphereComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AMyPlayerController* MyController;


	ViewState CurrentViewState;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		UCurveFloat* DefaultCurve;

	FTimeline CameraMoveTimeLine;

	UFUNCTION()
		void CameraMove(float Val);

	UFUNCTION()
		void OnPawnEnterCheckSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnPawnLeaveCheckSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//operator
public:

	UFUNCTION(NetMulticast, Reliable)
		void MoveForward(FVector Direction, float Value);

	UFUNCTION(NetMulticast, Reliable)
		void MoveRight(FVector Direction, float Value);

	UFUNCTION(NetMulticast, Reliable)
		void MoveUp(float Value);

	void ChangeViewState();

protected:
	//attack

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fight")
		float LockDistance;


	void LockTarget();



public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UCameraComponent* GetCameraComp() { return CameraComp; }

	FORCEINLINE APlayerInfoData* GetPlayerInfoData() { return GetController<AMyPlayerController>()->MyData; }

	virtual ACharacterInfoBase* GetCurrentInfoData() override { return GetController()? GetController<AMyPlayerController>()->MyData:nullptr;}

	UFUNCTION(BlueprintCallable)
		float GetActorDeraction();

	virtual void UnLookAtTarget() override;

	virtual void LookAtTarget(ACharacterBase* LookTarget) override;

	class ACharacterBase* FindNearlyMonster();

	AGamingHUD* GetMyHUD() { return MyController ? MyController->GetMyHUD() : nullptr; }
};
