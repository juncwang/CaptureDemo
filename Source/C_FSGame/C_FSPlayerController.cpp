// Fill out your copyright notice in the Description page of Project Settings.

#include "C_FSGame.h"
#include "C_FSPlayerController.h"
#include "C_FSPlayerCameraManager.h"

DEFINE_LOG_CATEGORY(Controller);



AC_FSPlayerController::AC_FSPlayerController()
{
	PlayerCameraManagerClass = AC_FSPlayerCameraManager::StaticClass();

	//bShowMouseCursor = 1;
}

void AC_FSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Print_PlayerController(TEXT("this is PlayerController"));
}

void AC_FSPlayerController::Print_PlayerController(FString _string)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, _string);
	}
}


