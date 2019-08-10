// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ARPG.h"
#include "CharacterInfoBase.generated.h"

/**
 * 
 */
USTRUCT()
struct FPropertesValue
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY()
		float BasicValue;
	UPROPERTY()
		float AddtiveValue;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValueChanged, EPropertyName,ChangedName, const FPropertesValue&,ChangedValue);


UCLASS()
class ARPG_API ACharacterInfoBase : public AInfo
{
	GENERATED_BODY()
protected:
	//使用EPropertyName来访问
	UPROPERTY(Replicated)
	TArray<FPropertesValue> Attributes;

	UFUNCTION(Client, Reliable)
		void TriggerBroadcast(EPropertyName ChangedName, FPropertesValue ChangedValue);
public:
	FString CharacterName;

	ACharacterInfoBase();

	UPROPERTY()
		FOnValueChanged ValueChangedHandle;

	FORCEINLINE TArray<FPropertesValue>& GetAttributes() { return Attributes; }
 
	float GetBasicAttributes(EPropertyName InName) const;
	UFUNCTION(Server,Reliable,WithValidation)
	void SetBasicAttributes(EPropertyName InName, float Invalue);

	UFUNCTION(BlueprintCallable)
	float GetAttributefromName(EPropertyName InName) const;
	UFUNCTION(Server, Reliable, WithValidation)
	void SetAttributefromName(EPropertyName InName, float Invalue);

	UFUNCTION(Server, Reliable, WithValidation)
	void AddAttributefromName(EPropertyName InName, float Invalue);
	UFUNCTION(Server, Reliable, WithValidation)
	void SubAttributefromName(EPropertyName InName, float Invalue);
	/*void InitPlayerAttribute(
		float Health,
		float Mana,
		float ATK,
		float DEF,
		float STA,
		float POW,
		float AGI,
		float INTE,
		float SPR,
		float CRI,
		float LEC,
		float IGN);
*/
	FORCEINLINE AController* GetController() { return Cast<AController>(GetOwner()); }

	FORCEINLINE APawn* GetPawn() { return GetController()->GetPawn(); }
};
