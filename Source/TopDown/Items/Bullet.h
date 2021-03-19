// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TOPDOWN_API ABullet : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABullet();

    // Event to Detect When an Actor Overlaps the Missile Class
    UFUNCTION()
    void Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    TSubclassOf<UDamageType> DamageType;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class USphereComponent* CollisionComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
    UParticleSystemComponent* BulletEffect;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    class UStaticMeshComponent* BulletMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(EditDefaultsOnly, Category = "FX")
    class UParticleSystem* ExplosionParticles;

    // Sounds
    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    class USoundBase* ExplosionSound;


    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float BaseDamage;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    class AWeapon* Weapon;

    UPROPERTY(EditAnywhere, Category = "Projectile ")
    float Radius;

    void OnDetanate();
    void OneHit();

    float Timer = 0.f;
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
