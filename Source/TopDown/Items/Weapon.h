// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class ATopDownCharacter;
class ABullet;

UCLASS()
class TOPDOWN_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();


	void StartFire();

	void StopFire();


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOffFire;

	FTimerHandle TimerHandle_TimeBetweenShots;
	float LastFireTime;//время последнего выстрела
	float TimeBetweenShots; // Пауза мужду выстреми винтовки

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float  BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FRotator GetMuzzleRotation() const {
		return WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FVector GetMuzzleLocation() const {
		return WeaponMesh->GetSocketLocation(MuzzleSocketName);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileWeapon")
	TSubclassOf<ABullet> BulletActor;


	void Shot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
