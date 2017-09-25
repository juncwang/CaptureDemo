// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "C_FSPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class C_FSGAME_API AC_FSPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AC_FSPlayerCameraManager();

	virtual void BeginPlay() override;

	virtual void UpdateCamera(float DeltaTime) override;
	
	void Print_PlayerCameraManager(FString _string);
};
