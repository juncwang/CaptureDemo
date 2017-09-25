// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "C_FSPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Controller, Log, All);

/**
 * 
 */
UCLASS()
class C_FSGAME_API AC_FSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AC_FSPlayerController();
	
	virtual void BeginPlay() override;

	void Print_PlayerController(FString _string);
};
