// Fill out your copyright notice in the Description page of Project Settings.

#include "C_FSGame.h"
#include "C_FSProjectile.h"
#include "C_FSCharacter.h"


// Sets default values
AC_FSCharacter::AC_FSCharacter()
{
	CameraMode = E_CameraMode_First;
	CameraViewDistance = 500.0f;
	bViewingCharacter = false;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint>_projectile(TEXT("Blueprint'/Game/FirstPerson/Character/BP/BP_FSProjectile.BP_FSProjectile'"));
	ProjectileClass = (UClass*)_projectile.Object->GeneratedClass;

	static ConstructorHelpers::FObjectFinder<USoundBase>_soundBase(TEXT("SoundWave'/Game/FirstPerson/Audio/FirstPersonTemplateWeaponFire02.FirstPersonTemplateWeaponFire02'"));
	FireSound = _soundBase.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>_animMontage(TEXT("AnimMontage'/Game/FirstPerson/Animations/First_Montage.First_Montage'"));
	FireAnimation = _animMontage.Object;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>_SkeletalMesh(TEXT("SkeletalMesh'/Game/newCharacter/SK_Mannequin.SK_Mannequin'"));
// 	static ConstructorHelpers::FObjectFinder<UAnimInstance>_AnimBlue(TEXT("AnimBlueprint'/Game/newCharacter/Animations/ThirdAnimBlueprint.ThirdAnimBlueprint'"));
// 	TSubclassOf<UStaticMesh> MyMesh = my_mesh.Class;

	//static ConstructorHelpers::FClassFinder<USkeletalMesh>FinderMesh_01(TEXT("SkeletalMesh'/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
	//TSubclassOf<USkeletalMesh> MeshSub = FinderMesh_01.Class;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetOwnerNoSee(false);
	Mesh1P->AttachToComponent(this->GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//Mesh1P->AttachParent = GetCapsuleComponent();
	Mesh1P->RelativeLocation = FVector(-5.f, 0.f, -85.f);
	//Mesh1P->RelativeRotation = FRotator(0.f, -90.f, 0.f);
	//Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow =0;

	Hand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand_01"));
	Hand->SetOnlyOwnerSee(true);
	Hand->SetOwnerNoSee(false);
	Hand->AttachToComponent(Mesh1P, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Hand_01"));
	Hand->SetRelativeLocation(FVector(-21.876638f, 7.434737f, -24.200697f));
	Hand->SetWorldRotation(FRotator(-119.462051f, 96.980881f,30.718487f));
	Hand->CastShadow = 0;

	GetMesh()->SetSkeletalMesh(_SkeletalMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -87.061768f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	//GetMesh()->SetHiddenInGame(true);
	GetMesh()->SetOnlyOwnerSee(false);
	GetMesh()->SetOwnerNoSee(true);
	//GetMesh()->SetAnimation();

	ZoomBlendStartDis = 0.f;
	ZoomBlenEndDis = 0.f;
	ZoomBlenTimeToGo = 0.f;


	CameraBlendTime = 1.f;
	CameraBlendExp = 2.f;


	SwitchBlendStartLoc = FVector::ZeroVector;
	SwitchBlendStartRot = FRotator::ZeroRotator;
	SwitchBlenTimeToGo = 0.f;

	//this->OnBeginCursorOver.AddDynamic(this, &AC_FSCharacter::abc);
}

// Called when the game starts or when spawned
void AC_FSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Print_Character(TEXT("this is Character"));

}

// Called every frame
void AC_FSCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AC_FSCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AC_FSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AC_FSCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &AC_FSCharacter::Turn);
	InputComponent->BindAxis("LookUp", this, &AC_FSCharacter::LookUp);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AC_FSCharacter::JumpUp);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AC_FSCharacter::Fire);
	InputComponent->BindAction("CameraChanger", IE_Pressed, this, &AC_FSCharacter::CameraChanger);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AC_FSCharacter::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AC_FSCharacter::ZoomOut);

	InputComponent->BindAction("RunningGo", IE_Pressed, this, &AC_FSCharacter::RunningGo);
	InputComponent->BindAction("RunningGo", IE_Released, this, &AC_FSCharacter::RunningStop);

	InputComponent->BindAction("GetCursor", IE_Pressed, this, &AC_FSCharacter::GetCursor);
	InputComponent->BindAction("ViewCharacter", IE_Pressed, this, &AC_FSCharacter::ViewCharacterDown);
	InputComponent->BindAction("ViewCharacter", IE_Released, this, &AC_FSCharacter::ViewCharacterUp);

}	

void AC_FSCharacter::RunningGo()
{
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	GetMesh()->GlobalAnimRateScale = 1.5f;
	Mesh1P->GlobalAnimRateScale = 1.5f;
	Hand->GlobalAnimRateScale = 1.5f;
}

void AC_FSCharacter::RunningStop()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetMesh()->GlobalAnimRateScale = 1.0f;
	Mesh1P->GlobalAnimRateScale = 1.0f;
	Hand->GlobalAnimRateScale = 1.0f;
}

void AC_FSCharacter::ZoomIn()
{
	if (CameraMode != E_CameraMode_First)
	{
		ZoomBlenTimeToGo = CameraBlendTime;
		ZoomBlendStartDis = CameraViewDistance;
		ZoomBlenEndDis = CameraViewDistance - 200.f;

		//CameraViewDistance = CameraViewDistance - 200.f;
		//CameraViewDistance = FMath::Clamp<float>(ZoomBlenEndDis, 200.f, 2000.f);
	}
}


void AC_FSCharacter::ZoomOut()
{
	if (CameraMode != E_CameraMode_First)
	{
		ZoomBlenTimeToGo = CameraBlendTime;
		ZoomBlendStartDis = CameraViewDistance;
		ZoomBlenEndDis = CameraViewDistance + 200.f;

		//CameraViewDistance = CameraViewDistance + 200.f;
		//CameraViewDistance = FMath::Clamp<float>(ZoomBlenEndDis, 200.f, 2000.f);
	}
}



void AC_FSCharacter::onCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation)
{
	USkeletalMeshComponent* DefMesh1P = Cast<USkeletalMeshComponent>(GetClass()->GetDefaultSubobjectByName(TEXT("Mesh1P")));
	const FMatrix DefMeshLS = FRotationTranslationMatrix(DefMesh1P->RelativeRotation, DefMesh1P->RelativeLocation);
	const FMatrix LocalToWorld = ActorToWorld().ToMatrixWithScale();

	const FRotator RotCameraPitch(CameraRotation.Pitch, 0.f, 0.f);
	const FRotator RotCameraYaw(0.f, CameraRotation.Yaw, 0.f);

	const FMatrix LeveledCameraLS = FRotationTranslationMatrix(RotCameraYaw, CameraLocation) * LocalToWorld.Inverse();
	const FMatrix PitchedCameraLS = FRotationMatrix(RotCameraPitch) * LeveledCameraLS;
	const FMatrix MeshRelativeToCamera = DefMeshLS * LeveledCameraLS.Inverse();
	const FMatrix PitchedMesh = MeshRelativeToCamera * PitchedCameraLS;

	Mesh1P->SetRelativeLocationAndRotation(PitchedMesh.GetOrigin(), PitchedMesh.Rotator());
}


void AC_FSCharacter::MoveForward(float _speed)
{
	if (Controller && Controller->IsLocalController())
	{ 
		if (_speed != 0.f)
		{
			//const FRotator Rotation = GetControlRotation();
			//FRotator YawRotation(0, Rotation.Yaw, 0);

			//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			//AddMovementInput(Direction, _speed);

			FRotator Rotator;
			if (CameraMode == E_CameraMode_WOW)
			{
				if (bViewingCharacter)
				{
					Rotator = GetActorRotation();
				}
				else
				{
					Rotator = GetControlRotation();
				}
			}
			else
			{
				Rotator = GetControlRotation();
			}
			FRotator YawRotation(0, Rotator.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			AddMovementInput(Direction, _speed);

		}
	}
}

void AC_FSCharacter::MoveRight(float _speed)
{
	if (Controller && Controller->IsLocalController())
	{
		if (_speed != 0.f)
		{
// 			const FRotator Rotation = GetControlRotation();

			FRotator Rotator;
			if (CameraMode == E_CameraMode_WOW)
			{
				if (bViewingCharacter)
				{
					Rotator = GetActorRotation();
				}
				else
				{
					Rotator = GetControlRotation();
				}
			}
			else
			{
				Rotator = GetControlRotation();
			}


 			FRotator YawRotation(0, Rotator.Yaw, 0);



			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(Direction, _speed);
		}
	}
}

void AC_FSCharacter::Turn(float _speed)
{
	if (Controller && Controller->IsLocalController())
	{
		if (_speed != 0.f)
		{
			APlayerController* const playController = CastChecked<APlayerController>(Controller);
			playController->AddYawInput(_speed);
		}
	}
}

void AC_FSCharacter::LookUp(float _speed)
{
	if (Controller && Controller->IsLocalController())
	{
		if (_speed != 0.f)
		{
			APlayerController* const playController = CastChecked<APlayerController>(Controller);
			playController->AddPitchInput(-_speed);
		}
	}
}

void AC_FSCharacter::JumpUp()
{
	bPressedJump = true;
}

void AC_FSCharacter::Fire()
{
	if (ProjectileClass !=NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (GetWorld())
		{
			World->SpawnActor<AC_FSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation != NULL)
	{
		UAnimInstance *AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AC_FSCharacter::CameraChanger()
{
	SwitchBlenTimeToGo = CameraBlendTime;
	SwitchBlendStartLoc = Cast<APlayerController>(GetController())->PlayerCameraManager->GetCameraLocation();
	SwitchBlendStartRot = Cast<APlayerController>(GetController())->PlayerCameraManager->GetCameraRotation();

	CameraMode = (enum FSCharacterCameraMode)(CameraMode + 1);
	if (CameraMode >= E_CameraMode_Max)
	{
		CameraMode = E_CameraMode_First;
	}

	switch (CameraMode)
	{
		case E_CameraMode_First:
			// Character 是否跟随 Controller 旋转
			bUseControllerRotationPitch = false;
			bUseControllerRotationRoll = false;
			bUseControllerRotationYaw = true;

			GetCharacterMovement()->bOrientRotationToMovement = false;
			GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

			CameraMode = E_CameraMode_First;
			GetMesh()->SetOwnerNoSee(true);
			GetMesh()->SetOnlyOwnerSee(false);
			Hand->SetOwnerNoSee(false);
			Hand->SetOnlyOwnerSee(true);
			Mesh1P->SetOwnerNoSee(false);
			Mesh1P->SetOnlyOwnerSee(true);
			break;

		case E_CameraMode_Thirt:
			GetMesh()->SetOwnerNoSee(false);
			GetMesh()->SetOnlyOwnerSee(false);
			Hand->SetOwnerNoSee(true);
			Hand->SetOnlyOwnerSee(true);
			Mesh1P->SetOwnerNoSee(true);
			Mesh1P->SetOnlyOwnerSee(true);

			// Character 是否跟随 Controller 旋转
			bUseControllerRotationPitch = false;
			bUseControllerRotationRoll = false;
			bUseControllerRotationYaw = false;

			// 移动方向为当前 Controller 方向
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
			//CharacterMovement->bOrientRotationToMovement = true;
			//CharacterMovement->RotationRate = FRotator(0.f, 540.f, 0.f);
			break;

		case E_CameraMode_ThirtRot:
			GetMesh()->SetOwnerNoSee(false);
			GetMesh()->SetOnlyOwnerSee(false);
			Hand->SetOwnerNoSee(true);
			Hand->SetOnlyOwnerSee(true);
			Mesh1P->SetOwnerNoSee(true);
			Mesh1P->SetOnlyOwnerSee(true);

			// Character 是否跟随 Controller 旋转
			bUseControllerRotationPitch = false;
			bUseControllerRotationRoll = false;
			bUseControllerRotationYaw = true;

			// 移动方向为当前 Controller 方向
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
			//CharacterMovement->bOrientRotationToMovement = true;
			//CharacterMovement->RotationRate = FRotator(0.f, 540.f, 0.f);
			break;

		case E_CameraMode_Top:
			GetMesh()->SetOwnerNoSee(false);
			GetMesh()->SetOnlyOwnerSee(false);
			Hand->SetOwnerNoSee(true);
			Hand->SetOnlyOwnerSee(true);
			Mesh1P->SetOwnerNoSee(true);
			Mesh1P->SetOnlyOwnerSee(true);

			// Character 是否跟随 Controller 旋转
			bUseControllerRotationPitch = false;
			bUseControllerRotationRoll = false;
			bUseControllerRotationYaw = false;

			// 移动方向为当前 Controller 方向
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
			//CharacterMovement->bOrientRotationToMovement = true;
			//CharacterMovement->RotationRate = FRotator(0.f, 540.f, 0.f);
			break;

		case E_CameraMode_WOW:
			GetMesh()->SetOwnerNoSee(false);
			GetMesh()->SetOnlyOwnerSee(false);
			Hand->SetOwnerNoSee(true);
			Hand->SetOnlyOwnerSee(true);
			Mesh1P->SetOwnerNoSee(true);
			Mesh1P->SetOnlyOwnerSee(true);

			// Character 是否跟随 Controller 旋转
			bUseControllerRotationPitch = false;
			bUseControllerRotationRoll = false;
			bUseControllerRotationYaw = false;

			// 移动方向为当前 Controller 方向
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
			//CharacterMovement->bOrientRotationToMovement = true;
			//CharacterMovement->RotationRate = FRotator(0.f, 540.f, 0.f);
			break;

		default:
			break;
	}
	
}

void AC_FSCharacter::Print_Character(FString _string)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, _string);
	}
}

void AC_FSCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo & OutResult)
{


	FVector CameraLoc(0.f, 0.f, 0.f);
	FRotator CameraRot(0.f, 0.f, 0.f);
	FVector Pos(0.f, 0.f, 0.f);

	switch (CameraMode)
	{
	case E_CameraMode_First:
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		onCameraUpdate(CameraLoc, CameraRot);
		Pos = CameraLoc;
		break;
	case E_CameraMode_Thirt:
		CameraLoc = GetActorLocation();
		CameraRot = GetControlRotation();
		Pos = CameraLoc - CameraRot.Vector() * CameraViewDistance;
		break;
	case E_CameraMode_ThirtRot:
		CameraLoc = GetActorLocation();
		CameraRot = GetControlRotation();
		Pos = CameraLoc - CameraRot.Vector() * CameraViewDistance;
		break;
	case E_CameraMode_Top:
		Pos.X = 0.f;
		Pos.Y = 0.f;
		Pos.Z = CameraViewDistance;
		CameraLoc = GetActorLocation();
		CameraRot = FRotator(-90.f, 0.f, 0.f);
		Pos = CameraLoc + Pos;
		GetController()->SetControlRotation(FRotator(0.f, 0.f, 0.f));
		break;
	case E_CameraMode_WOW:
		CameraLoc = GetActorLocation();
		CameraRot = GetControlRotation();
		Pos = CameraLoc - CameraRot.Vector() * CameraViewDistance;
		break;
	default:
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		Pos = CameraLoc;
		break;
	}
	//=========================================相机碰撞检测================================================================================

	FCollisionQueryParams BoxParams(TEXT("Camera"), false, this);
	FHitResult Result;
	if (CameraLoc != Pos)
	{
		GetWorld()->SweepSingleByChannel(Result, CameraLoc, Pos, FQuat::Identity, ECC_Camera, FCollisionShape::MakeBox(FVector(12.f)), BoxParams);
	}

	//=========================================相机切换平滑处理================================================================================

	SwitchBlenTimeToGo -= DeltaTime;
	if (SwitchBlenTimeToGo > 0.f)
	{
		float Dur = (CameraBlendTime - SwitchBlenTimeToGo) / CameraBlendTime;
		Pos = FMath::Lerp(SwitchBlendStartLoc, Pos, FMath::Pow(Dur, 1.f / CameraBlendExp));
		CameraRot = FMath::Lerp(SwitchBlendStartRot, CameraRot, FMath::Pow(Dur, 1.f / CameraBlendExp));
	}



	//=========================================相机缩放平滑处理================================================================================

	ZoomBlenTimeToGo -= DeltaTime;
	if (ZoomBlenTimeToGo > 0.f)
	{
		float Dur = (CameraBlendTime - ZoomBlenTimeToGo)/CameraBlendTime;
		CameraViewDistance = FMath::Lerp(ZoomBlendStartDis, ZoomBlenEndDis, FMath::Pow(Dur, 1.f / CameraBlendExp));
	}

	//GetController()->

	CameraViewDistance = FMath::Clamp<float>(CameraViewDistance, 200.f, 2000.f);

	OutResult.Location = (Result.GetActor() == NULL) ? Pos : Result.Location;
	//OutResult.Location = Pos;
	OutResult.Rotation = CameraRot;
}

void AC_FSCharacter::GetCursor()
{
	APlayerController *playCon = Cast<APlayerController>(GetController());
	FHitResult SelfHitresult;
	playCon->GetHitResultUnderCursor(ECC_Camera, false, SelfHitresult);

	FVector SelfLocation = SelfHitresult.Location;
	Print_Character("SelfLocation.X" + FString::SanitizeFloat(SelfLocation.X));
	Print_Character("SelfLocation.Y" + FString::SanitizeFloat(SelfLocation.Y));
	Print_Character("SelfLocation.Z" + FString::SanitizeFloat(SelfLocation.Z));
}

void AC_FSCharacter::ViewCharacterDown()
{
	if (CameraMode == E_CameraMode_WOW)
	{
		bViewingCharacter = true;
	}
}

void AC_FSCharacter::ViewCharacterUp()
{
	if (CameraMode == E_CameraMode_WOW)
	{
		bViewingCharacter = false;
	}
}

// void AC_FSCharacter::abc(AActor* a)
// {
// 
// }


