// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown/Items/Weapon.h"
#include "TopDown/TopDownCharacter.h"
#include "TopDown/Items/Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	RootComponent = WeaponMesh;

	MuzzleSocketName = "MuzzleSocket";

	BaseDamage = 20.f;

}
void AWeapon::StartFire() {
	//таймер на автоматическу стрельбу
	float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.f);
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &AWeapon::Shot, TimeBetweenShots, true, FirstDelay);
}

void AWeapon::Shot() {
	
		FVector Origin = GetMuzzleLocation();
		AActor* MyOwner = GetOwner();
		FVector EyeLocation;
		FRotator EyeRotation;

		if (ATopDownCharacter* Character = Cast<ATopDownCharacter>(GetOwner())) {
			EyeLocation = Character->CursorLocatyion();
		}

		FVector ShootDir;

		
		if (BulletActor) {
			FTransform SpawnTM(WeaponMesh->GetSocketRotation(MuzzleSocketName), WeaponMesh->GetSocketLocation(MuzzleSocketName));
			ABullet* Bullet = Cast<ABullet>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, BulletActor, SpawnTM));
			UE_LOG(LogTemp, Warning, TEXT("SHOOTING Bullet"));
			if (Bullet) {
				//Projectile->SetInstigator(GetInstigator());
				Bullet->SetOwner(this);
				//Projectile->SetParams(Bullet);
				
				UGameplayStatics::FinishSpawningActor(Bullet, SpawnTM);

			}
		}
		//ServerProjectile(Origin, EyeRotation);
		//LastFireTime = GetWorld()->TimeSeconds;
		//FRotator MuzzleRotation = GetMuzzleRotation();
		//NetMulticastPlayFireEffects(Origin, MuzzleRotation);
		//FireAnim();

		LastFireTime = GetWorld()->TimeSeconds;

}


void AWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
	//bIsFire = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();


	TimeBetweenShots = 60 / RateOffFire;
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

