// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define ECC_DamageBox ECC_GameTraceChannel1
#define ECC_Beem ECC_GameTraceChannel2
#define ECC_Item ECC_GameTraceChannel3

#define ST_Wood SurfaceType1
#define ST_Stone SurfaceType2
#define ST_Sand SurfaceType3
#define ST_Water SurfaceType4



UENUM()
enum class EEquipmentPart : uint8
{
	Head,
	Armor,
	Pant,
	Shoes,
	Left,
	Right,
	Ring,
	NeckLace,
	Max
};



UENUM()
enum class EEquipmentType : uint8
{
	None,
	Head,
	Armor,
	Pant,
	Shoes,
	Ring,
	NeckLace,

	Weapon,
	Sword,
	Shield,
	TwoHand,
	Bow,
	Lswd

};

UENUM()
enum class EPropertyName :uint8
{
	/*����ֵ*/
	Health UMETA(DisplayName = "Health"),

	/*ħ��ֵ*/
	Mana UMETA(DisplayName = "Mana"),

	/*������*/
	ATK UMETA(DisplayName = "ATK"),

	/*������*/
	DEF UMETA(DisplayName = "DEF"),

	/*����ֵ*/
	STA UMETA(DisplayName = "STA"),

	/*����*/
	POW UMETA(DisplayName = "POW"),

	/*����*/
	AGI UMETA(DisplayName = "AGI"),

	/*����*/
	INTE UMETA(DisplayName = "INTE"),

	/*����*/
	SPR UMETA(DisplayName = "SPR"),

	/*������*/
	CRI UMETA(DisplayName = "CRI"),

	/*������*/
	CRID UMETA(DisplayName = "CRID"),

	/*��Ѫ��*/
	LEC UMETA(DisplayName = "LEC"),

	/*���ӻ�����*/
	IGN UMETA(DisplayName = "IGN"),

	MAX
};

