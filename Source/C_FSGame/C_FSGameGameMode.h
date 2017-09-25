// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
//#include "ProceduralMeshComponent.h"
#include "C_FSGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class C_FSGAME_API AC_FSGameGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AC_FSGameGameMode();

	virtual void BeginPlay() override;

	void Print_GameMode(FString _string);

	//UProceduralMeshComponent *mesh;
	
};
