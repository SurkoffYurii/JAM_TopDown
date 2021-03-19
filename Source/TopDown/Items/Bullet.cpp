// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown/Items/Bullet.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &ABullet::Hit);
    CollisionComp->SetSimulatePhysics(false);
    CollisionComp->SetLinearDamping(0.0f);
    CollisionComp->SetEnableGravity(false);
    RootComponent = CollisionComp;

    BulletEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BulletEffect"));
    BulletEffect->SetupAttachment(RootComponent);

        BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BulletMesh"));
        BulletMesh->SetupAttachment(RootComponent);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 1000.f;
    ProjectileMovement->MaxSpeed = 1000.f;
    ProjectileMovement->bRotationFollowsVelocity = false;
    ProjectileMovement->bInitialVelocityInLocalSpace = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->bIsHomingProjectile = false;
    ProjectileMovement->HomingAccelerationMagnitude = 0.f;
    ProjectileMovement->ProjectileGravityScale = 0.f;
    ProjectileMovement->Velocity = FVector(1, 0, 0);

    //Weapon = CreateDefaultSubobject<AWeapon>(TEXT("Weapon"));

    InitialLifeSpan = 5.0f;

    BaseDamage = 20.f;
}

void ABullet::Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
    if ((OtherActor != NULL) && (OtherActor != this)) {
      /*  FHitResult OutHit;
        FVector ForwardVector = GetActorForwardVector();
        AActor* HitActor = OutHit.GetActor();*/
        if (OtherActor) {
            UGameplayStatics::ApplyPointDamage(OtherActor, BaseDamage, NormalImpulse, Hit, nullptr, this, DamageType);
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *Hit.GetActor()->GetName()));
            UE_LOG(LogTemp, Warning, TEXT("Hit"));

        }
        OneHit();
    }
 // UE_LOG(LogTemp, Warning, TEXT("123"));
}

void ABullet::OneHit() {
    //UE_LOG(LogTemp, Warning, TEXT("Hit"));
    Destroy();

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

