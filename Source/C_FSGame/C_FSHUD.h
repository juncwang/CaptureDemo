// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "C_FSHUD.generated.h"

/**
 * 
 */
UCLASS()
class C_FSGAME_API AC_FSHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AC_FSHUD();

	void Print_HUD(FString _string);

	virtual void DrawHUD() override;
	
private:

	UTexture2D* CrosshairTex;
	
};
