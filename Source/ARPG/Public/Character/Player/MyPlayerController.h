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

	/*向前方向的分量*/
	float FwdAxis;

	/*向右方向的分量*/
	float RgtAxis;

	void LookUp(float Value);

	void Turn(float Value);


	/*向前移动的的入口函数*/
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION(Server, WithValidation, Reliable)
		void ServerMoveForward(float Value,FVector mDirection);

	/*向右移动的的入口函数*/
	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION(Server, WithValidation, Reliable)
		void ServerMoveRight(float Value, FVector mDirection);

	UFUNCTION()
		void MoveUp(float Value);

	UFUNCTION()
		void ServerMoveUp(float Value);


	/*跑步*/
	UFUNCTION()
		void Run();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRun();

	UFUNCTION()
		void EndRun();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerEndRun();

	/*视角锁定敌人*/
	void LockTarget();

	/*使用左手武器*/
	UFUNCTION(Server, Unreliable, WithValidation)
		void UseLeftWeapon();

	UFUNCTION(Server, Unreliable, WithValidation)
		void StopLeftWeapon();

	/*使用右手武器*/
	UFUNCTION(Server, Unreliable, WithValidation)
		void UseRightWeapon();

	UFUNCTION(Server, Unreliable, WithValidation)
		void StopRightWeapon();

	/*翻滚事件*/
	UFUNCTION()
		void DodgeEvent();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerDodge(FVector DodgeVec);

	/*跳跃事件*/
	UFUNCTION()
		void JumpEvent();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerJump();

	/*释放技能事件*/
	UFUNCTION(BlueprintCallable)
		void CastSkill(uint8 SkillIndex);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerCastSkill(uint8 SkillIndex);

	/*UI操作*/
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
