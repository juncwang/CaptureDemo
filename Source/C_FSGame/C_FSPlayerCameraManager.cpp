// Fill out your copyright notice in the Description page of Project Settings.

#include "C_FSGame.h"
#include "C_FSCharacter.h"
#include "C_FSPlayerCameraManager.h"




AC_FSPlayerCameraManager::AC_FSPlayerCameraManager()
{

}

void AC_FSPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	Print_PlayerCameraManager(TEXT("this is PlayerCameraManager"));
}

void AC_FSPlayerCameraManager::UpdateCamera(float DeltaTime)
{
// 	AC_FSCharacter* myPawn = PCOwner ? Cast<AC_FSCharacter>(PCOwner->GetPawn()) : NULL;
// 	if (mypawn && mypawn-> isfirstperson())
// 	{
// 		const float targetfov = mypawn->istargeting() ? targetingfov : normalfov;
// 		defaultfov = fmath::finterpto(defaultfov, targetfov, deltatime, 20.0f);
// 	}

	Super::UpdateCamera(DeltaTime);

// 	FVector pos(0.f,0.f,0.f);
// 
// 	if (myPawn)
// 	{
// 		switch (myPawn->CameraMode)
// 		{
// 		case E_CameraMode_First:
// 			myPawn->onCameraUpdate(GetCameraLocation(), GetCameraRotation());
// 			break;
// 		case E_CameraMode_Thirt:
// 			pos = GetCameraLocation() - GetCameraRotation().Vector() * myPawn->CameraViewDistance;
// 			myPawn->onCameraUpdate(pos, GetCameraRotation());
// 			break;
// 		default:
// 			break;
// 		}
// 	}

	
}

void AC_FSPlayerCameraManager::Print_PlayerCameraManager(FString _string)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, _string);
	}
}
