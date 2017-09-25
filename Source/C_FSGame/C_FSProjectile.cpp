// Fill out your copyright notice in the Description page of Project Settings.

#include "C_FSGame.h"
#include "C_FSProjectile.h"


// Sets default values
AC_FSProjectile::AC_FSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

// 	static ConstructorHelpers::FClassFinder<UStaticMesh>mesh_01(TEXT("StaticMesh'/Game/FirstPerson/Meshes/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));
// 	TSphere = mesh_01.Class;

// 	ProjectilMehs = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/FirstPerson/Meshes/FirstPersonProjectileMesh.FirstPersonProjectileMesh'")));
// 	UTexture *texture = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), NULL, TEXT("Texture2D'/Game/FirstPerson/Character/Textures/UE4_Mannequin__normals.UE4_Mannequin__normals'")));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>mesh_1(TEXT("StaticMesh'/Game/FirstPerson/Meshes/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));
	ProjectilMehs = mesh_1.Object;

// 	static ConstructorHelpers::FClassFinder<AActor>test(TEXT("Class'/Script/C_FSGame.C_FSProjectile'"));
// 	TSubclassOf<AActor> TTest = test.Class;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3.f;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(20.f);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AC_FSProjectile::OnOverlap);
	CollisionComp->bGenerateOverlapEvents = true;
	RootComponent = CollisionComp;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->AttachToComponent(CollisionComp, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileMesh->SetWorldScale3D(FVector(.1f,.1f,.1f));
	ProjectileMesh->SetStaticMesh(ProjectilMehs);

}

// Called when the game starts or when spawned
void AC_FSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_FSProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AC_FSProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor != NULL && OtherActor != this && OtherComp != NULL)
	{
		OtherComp->AddImpulseAtLocation(GetVelocity()*1000000.f, GetActorLocation());
		Destroy();
	}
}

