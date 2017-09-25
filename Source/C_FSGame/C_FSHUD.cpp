// Fill out your copyright notice in the Description page of Project Settings.

#include "C_FSGame.h"
#include "C_FSHUD.h"




AC_FSHUD::AC_FSHUD()
{
	Print_HUD("this is AC_FSHUD");
	static ConstructorHelpers::FObjectFinder<UTexture2D>O_T2D(TEXT("Texture2D'/Game/FirstPerson/Textures/FirstPersonCrosshair.FirstPersonCrosshair'"));
	CrosshairTex = O_T2D.Object;
}

void AC_FSHUD::Print_HUD(FString _string)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 9.f, FColor::Blue, _string);
	}
}

void AC_FSHUD::DrawHUD()
{
	Super::DrawHUD();

	const FVector2D Center(Canvas->ClipX*.5f, Canvas->ClipY*.5f);

	const FVector2D CrossHairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth()*.5f)), (Center.Y - (CrosshairTex->GetSurfaceHeight()*.5f)));

	FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
