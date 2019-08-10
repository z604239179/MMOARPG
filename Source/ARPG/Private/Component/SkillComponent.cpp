// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillComponent.h"
#include "PrimarySkill.h"
#include "MyAssetManager.h"
#include "PassiveSkillBase.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...

}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	ComponentOwner = Cast<ACharacterBase>(GetOwner());

	UMyAssetManager& MyManager = UMyAssetManager::Get();
	// ...
	for (int32 it =0 ;it< SkillIds.Num();++it)
	{
		UPrimarySkill* TempSkill = Cast<UPrimarySkill>(MyManager.GetPrimaryAssetObject(SkillIds[it]));
		if (TempSkill)
		{
			SkillInstance.AddUnique(NewObject<UCharacterSkillBase>(this, TempSkill->SkillClass));
			SkillInstance[it]->InitSkill(ComponentOwner, TempSkill);
			SkillInstance[it]->SkillIndex = it;
		}
	}
	

}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillComponent::CastSkill(uint8 SkillIndex)
{
	if (SkillInstance.Num() > SkillIndex)
	{
		SkillInstance[SkillIndex]->CastSkill();
	}
}

void USkillComponent::CastEnd(uint8 SkillIndex)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("ComponentsSkillEnd"));
	ComponentOwner->CastSkillEnd();
}

bool USkillComponent::AddPassiveSkill( UPassiveSkillBase* SkillRef)
{
	if (SkillRef)
	{
		if (!PassiveSkillList.Contains(SkillRef))
		{
			PassiveSkillList.Add(SkillRef);
			SkillRef->ActivePassiveSkill();
			return true;
		}

		
	}
	return false;
}

bool USkillComponent::RemovePassiveSkill(UPassiveSkillBase* SkillRef)
{
	if (PassiveSkillList.Contains(SkillRef))
	{
		SkillRef->UnActivePassiveSkill();
		PassiveSkillList.Remove(SkillRef);
		return true;
	}
	return false;
}

bool USkillComponent::AddBuffToList(UBuffBase* BuffRef)
{
	if (ActiveBuffList.Contains(BuffRef))
		return false;
	ActiveBuffList.Add(BuffRef);
	return true;
}

bool USkillComponent::RemoveBuffFromList(UBuffBase* BuffRef)
{
	if (ActiveBuffList.Contains(BuffRef))
	{
		ActiveBuffList.Remove(BuffRef);
		return true;
	}
	return false;
}
