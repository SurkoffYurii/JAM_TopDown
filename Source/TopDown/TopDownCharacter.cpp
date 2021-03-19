// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Items/Weapon.h"
#include "HealthComponent.h"



ATopDownCharacter::ATopDownCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->MaxWalkSpeed = 600;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Health компонент
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WeaponAttachRightSocket = "WeaponSocket";

	PlayerHealth = 100.f;

	CurrentHealth = PlayerHealth;
}

void ATopDownCharacter::SetHealth() {
	HealthComponent->SetParams(PlayerHealth);
}
void  ATopDownCharacter::Healing(float Healing) {
	HealthComponent->Heal(Healing);
}

// Called when the game starts or when spawned
void ATopDownCharacter::BeginPlay() {
	Super::BeginPlay();
	

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	BaseWeapon = GetWorld()->SpawnActor<AWeapon>(StarterBaseWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (BaseWeapon) {
		BaseWeapon->SetOwner(this);
		BaseWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachRightSocket);
	}


	//HealthComp
	HealthComponent->OnHealthChanged.AddDynamic(this, &ATopDownCharacter::OnHealthChanged);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeSetHealth, this, &ATopDownCharacter::SetHealth, 0.2f, false);
	HealthComponent->SetParams(PlayerHealth);
}
void ATopDownCharacter::SetBossFight(bool bBoss) {
	bBossSpawn = bBoss;
	if (bBoss) {
		StopSpeed();
	}
	else {
		WalkSpeed();
		
	}
}
void ATopDownCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	
	if (!bBossSpawn) {
		if (CursorToWorld != nullptr)
		{
			if (APlayerController* PC = Cast<APlayerController>(GetController())) {
				FHitResult TraceHitResult;
				PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
				FVector CursorFV = TraceHitResult.ImpactNormal;
				FRotator CursorR = CursorFV.Rotation();
				CursorToWorld->SetWorldLocation(TraceHitResult.Location);
				CursorToWorld->SetWorldRotation(CursorR);
				CursorLocation = TraceHitResult.ImpactNormal;
			}
		}
	}
}


void ATopDownCharacter::StartFire() {
	BaseWeapon->StartFire();
	Attack();
}

void ATopDownCharacter::StopFire() {
	BaseWeapon->StopFire();
}

void ATopDownCharacter::WalkSpeed() {
	GetCharacterMovement()->MaxWalkSpeed = 600;
}
void ATopDownCharacter::StopSpeed() {
	GetCharacterMovement()->MaxWalkSpeed = 0;
}

void ATopDownCharacter::OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta, FName BoneName, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {
	CurrentHealth = Health;
	if (Health <= 0.0f) {
		//Умер
		bDied = true;

		Died();

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}