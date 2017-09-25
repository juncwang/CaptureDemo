// Fill out your copyright notice in the Description page of Project Settings.

#include "C_FSGame.h"
#include "C_FSCharacter.h"
#include "C_FSPlayerController.h"
#include "C_FSHUD.h"
#include "C_FSGameGameMode.h"




AC_FSGameGameMode::AC_FSGameGameMode()
{
	//DefaultPawnClass = AC_FSCharacter::StaticClass();
	// 使用创建蓝图自定义Pawn
	static ConstructorHelpers::FObjectFinder<UBlueprint>BP_Character(TEXT("Blueprint'/Game/FirstPerson/Character/BP/BP_FSCharacter.BP_FSCharacter'"));
	if (BP_Character.Object != NULL)
	{
		DefaultPawnClass = (UClass*)BP_Character.Object->GeneratedClass;
	}

	PlayerControllerClass = AC_FSPlayerController::StaticClass();

	//static ConstructorHelpers::FClassFinder<AC_FSHUD>C_HUD(TEXT("Class'/Script/C_FSGame.C_FSHUD'"));
	HUDClass = AC_FSHUD::StaticClass();

/*	DefaultPawnClass = Cast<APawn>(StaticLoadObject(APawn::StaticClass(), NULL, TEXT("Blueprint'/Game/FirstPerson/Character/BP/BP_FSCharacter.BP_FSCharacter'")));*/
}

void AC_FSGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	Print_GameMode(TEXT("this is GameMode"));
}

void AC_FSGameGameMode::Print_GameMode(FString _string)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, _string);
	}
}
