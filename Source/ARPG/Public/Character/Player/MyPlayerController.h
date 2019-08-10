// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerInfoData.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
class APlayerCharacter;
UCLASS()
class ARPG_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

public:
	UPROPERTY(Replicated)
		uint8 NetworkIndex;

	UPROPERTY(ReplicatedUsing = OnRep_MyData)
		class APlayerInfoData* MyData;
	
	UFUNCTION()
		virtual void OnRep_MyData();
protected:

	class AGamingHUD* MyHUD;

	virtual void BeginPlay() override;

	/*��ǰ����ķ���*/
	float FwdAxis;

	/*���ҷ���ķ���*/
	float RgtAxis;

	void LookUp(float Value);

	void Turn(float Value);


	/*��ǰ�ƶ��ĵ���ں���*/
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION(Server, WithValidation, Reliable)
		void ServerMoveForward(float Value,FVector mDirection);

	/*�����ƶ��ĵ���ں���*/
	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION(Server, WithValidation, Reliable)
		void ServerMoveRight(float Value, FVector mDirection);

	UFUNCTION()
		void MoveUp(float Value);

	UFUNCTION()
		void ServerMoveUp(float Value);


	/*�ܲ�*/
	UFUNCTION()
		void Run();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRun();

	UFUNCTION()
		void EndRun();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerEndRun();

	/*�ӽ���������*/
	void LockTarget();

	/*ʹ����������*/
	UFUNCTION(Server, Unreliable, WithValidation)
		void UseLeftWeapon();

	UFUNCTION(Server, Unreliable, WithValidation)
		void StopLeftWeapon();

	/*ʹ����������*/
	UFUNCTION(Server, Unreliable, WithValidation)
		void UseRightWeapon();

	UFUNCTION(Server, Unreliable, WithValidation)
		void StopRightWeapon();

	/*�����¼�*/
	UFUNCTION()
		void DodgeEvent();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerDodge(FVector DodgeVec);

	/*��Ծ�¼�*/
	UFUNCTION()
		void JumpEvent();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerJump();

	/*�ͷż����¼�*/
	UFUNCTION(BlueprintCallable)
		void CastSkill(uint8 SkillIndex);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerCastSkill(uint8 SkillIndex);

	/*UI����*/
	UFUNCTION()
		void CallInventory();

	UFUNCTION()
		void CallCharacterPanel();

	UFUNCTION()
		void CallCheatPanel();

public:

	void InitMyPawn(class ACharacterBase* aPawn);


	FORCEINLINE AGamingHUD* GetMyHUD() { return MyHUD; }

	APlayerCharacter* GetMyCharacter();


	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
	UFUNCTION(Server, WithValidation, Reliable)
		void SendMessage(const FString& msg);

	UFUNCTION(Client, Reliable)
		void ReceiveMessage(const FString& msg, const FString& InstigaterName);

};
