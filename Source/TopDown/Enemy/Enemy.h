// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDown/Enemy/EnemyInterface.h"
#include "Enemy.generated.h"

class UHealthComponent;
class UBoxComponent;

UCLASS()
class TOPDOWN_API AEnemy : public ACharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();



	//Health компонент
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float  EnemyHealth;
	UHealthComponent* HealthComponent;
	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta, FName BoneName, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	bool bDied;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* InteractionObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> EnemyDamageType;

	FTimerHandle TimerHandle_TimeSetHealth;
	void SetHealth();

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float BaseSpeed;

	void StopMove();

	void GoMove();


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void Attack();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
