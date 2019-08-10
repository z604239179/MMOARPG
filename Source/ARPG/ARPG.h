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
	/*生命值*/
	Health UMETA(DisplayName = "Health"),

	/*魔法值*/
	Mana UMETA(DisplayName = "Mana"),

	/*攻击力*/
	ATK UMETA(DisplayName = "ATK"),

	/*防御力*/
	DEF UMETA(DisplayName = "DEF"),

	/*耐力值*/
	STA UMETA(DisplayName = "STA"),

	/*力量*/
	POW UMETA(DisplayName = "POW"),

	/*敏捷*/
	AGI UMETA(DisplayName = "AGI"),

	/*智力*/
	INTE UMETA(DisplayName = "INTE"),

	/*精神*/
	SPR UMETA(DisplayName = "SPR"),

	/*暴击率*/
	CRI UMETA(DisplayName = "CRI"),

	/*暴击率*/
	CRID UMETA(DisplayName = "CRID"),

	/*吸血率*/
	LEC UMETA(DisplayName = "LEC"),

	/*无视护甲率*/
	IGN UMETA(DisplayName = "IGN"),

	MAX
};

