// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "PrimaryNPC.h"
#include "MyAssetManager.h"
#include "PrimaryGoods.h"
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	if (GetBasicAIInfo())
	{
		NPCInfo = Cast<UPrimaryNPC>(GetBasicAIInfo());
	}
}

void ANPC::InitCharacter()
{

}
