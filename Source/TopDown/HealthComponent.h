// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FOnHealthChangedSignature, UHealthComponent*, OwningHealthComp, float, Health, float, HealthDelta, FName, BoneName, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS(ClassGroup = (SWCWONLINE), meta = (BlueprintSpawnableComponent))
class TOPDOWN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float DefaultHealth;

	UPROPERTY(BlueprintReadOnly, Category = "HealthComponent")
	float Health;

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void SetParams(float fHealth);

	UPROPERTY(BlueprintAssignable, Category = "HealthComponent")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintReadOnly, Category = "HealthComponent")
	bool bIsDead;


	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void Heal(float fHealAmount);
protected:
	UFUNCTION()
	void HandleTakePointDamage(AActor* DamagedActor,
			float Damage,
			class AController* InstigatedBy,
			FVector HitLocation,
			class UPrimitiveComponent* FHitComponent,
			FName BoneName,
			FVector ShotFromDirection,
			const class UDamageType* DamageType,
			AActor* DamageCauser);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
