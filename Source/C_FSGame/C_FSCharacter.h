// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "C_FSProjectile.h"
#include "C_FSCharacter.generated.h"

UENUM()
enum FSCharacterCameraMode
{
	E_CameraMode_None,
	E_CameraMode_First,
	E_CameraMode_Thirt,
	E_CameraMode_ThirtRot,
	E_CameraMode_Top,
	E_CameraMode_WOW,
	E_CameraMode_Max,
};


UCLASS()
class C_FSGAME_API AC_FSCharacter : public ACharacter
{
	GENERATED_BODY()

		

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		FVector GunOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		USkeletalMeshComponent* Hand;


	UPROPERTY(EditDefaultsOnly, Category = Projcetile)
		TSubclassOf<AC_FSProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		USoundBase *FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		UAnimMontage *FireAnimation;

	UPROPERTY()
		TEnumAsByte<enum FSCharacterCameraMode> CameraMode;

	UPROPERTY()
		float CameraViewDistance;


	UPROPERTY()
		float ZoomBlendStartDis;
	UPROPERTY()
		float ZoomBlenEndDis;
	UPROPERTY()
		float ZoomBlenTimeToGo;

	UPROPERTY()
		FVector SwitchBlendStartLoc;
	UPROPERTY()
		FRotator SwitchBlendStartRot;
	UPROPERTY()
		float SwitchBlenTimeToGo;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraBlendTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraBlendExp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bViewingCharacter;

	// Sets default values for this character's properties
	AC_FSCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void onCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation);

	void MoveForward(float _speed);
	void MoveRight(float _speed);
	void Turn(float _speed);
	void LookUp(float _speed);
	void JumpUp();
	void Fire();
	void CameraChanger();
	void ZoomIn();
	void ZoomOut();
	void RunningGo();
	void RunningStop();

	void Print_Character(FString _string);

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult);

	/*void abc(AActor* a);*/
	void GetCursor();

	void ViewCharacterDown();

	void ViewCharacterUp();

	//UFUNCTION(BlueprintImplementableEvent)

};
