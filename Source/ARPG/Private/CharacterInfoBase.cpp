// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInfoBase.h"
#include "Net/UnrealNetwork.h"



void ACharacterInfoBase::TriggerBroadcast_Implementation(EPropertyName ChangedName, FPropertesValue ChangedValue)
{

	ValueChangedHandle.Broadcast(ChangedName, ChangedValue);
}

ACharacterInfoBase::ACharacterInfoBase()
{
		Attributes.Init(FPropertesValue(), (int32)EPropertyName::MAX);

		/*TODO:É¾³ýÄ¬ÈÏÖµ*/
		Attributes[(int32)EPropertyName::Health].BasicValue = 100;
		Attributes[(int32)EPropertyName::Mana].BasicValue = 100;
		Attributes[(int32)EPropertyName::ATK].BasicValue = 20;
		SetReplicates(true);
	
}

float ACharacterInfoBase::GetBasicAttributes(EPropertyName InName) const
{
	if (InName != EPropertyName::MAX)
	{
		return Attributes[(int32)InName].BasicValue;
	}
	return 0;
}

void ACharacterInfoBase::SetBasicAttributes_Implementation(EPropertyName InName, float Invalue)
{
	if (InName != EPropertyName::MAX)
	{
		Attributes[(int32)InName].BasicValue = Invalue;
		TriggerBroadcast(InName, Attributes[(int32)InName]);
	}
}
bool ACharacterInfoBase::SetBasicAttributes_Validate(EPropertyName InName, float Invalue)
{
	return true;
}

float ACharacterInfoBase::GetAttributefromName(EPropertyName InName) const
{
	if (InName != EPropertyName::MAX)
	{
		return Attributes[(int32)InName].AddtiveValue + Attributes[(int32)InName].BasicValue;
	}
	return 0;
}

void ACharacterInfoBase::SetAttributefromName_Implementation(EPropertyName InName, float Invalue)
{
	if (InName != EPropertyName::MAX)
	{
		Attributes[(int32)InName].AddtiveValue = Invalue;
		TriggerBroadcast(InName, Attributes[(int32)InName]);
	}
}
bool ACharacterInfoBase::SetAttributefromName_Validate(EPropertyName InName, float Invalue)
{
	return true;
}


void ACharacterInfoBase::AddAttributefromName_Implementation(EPropertyName InName, float Invalue)
{
	if (InName != EPropertyName::MAX)
	{
		Attributes[(int32)InName].AddtiveValue += Invalue;
		TriggerBroadcast(InName, Attributes[(int32)InName]);
	}
}
bool ACharacterInfoBase::AddAttributefromName_Validate(EPropertyName InName, float Invalue)
{
	return true;
}

void ACharacterInfoBase::SubAttributefromName_Implementation(EPropertyName InName, float Invalue)
{
	if (InName != EPropertyName::MAX)
	{
		Attributes[(int32)InName].AddtiveValue -= Invalue;
		TriggerBroadcast(InName, Attributes[(int32)InName]);
	}
}
bool ACharacterInfoBase::SubAttributefromName_Validate(EPropertyName InName, float Invalue)
{
	return true;
}


void ACharacterInfoBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterInfoBase, Attributes);

}