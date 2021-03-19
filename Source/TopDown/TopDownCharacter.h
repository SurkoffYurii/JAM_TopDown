// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInterface.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

class AWeapon;
class UHealthComponent;

UCLASS(Blueprintable)
class ATopDownCharacter : public ACharacter, public ICharacterInterface
{
	GENERATED_BODY()

public:
	ATopDownCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	FVector CursorLocation;
	FVector CursorLocatyion() const { return CursorLocation; }


	//Health компонент
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float  PlayerHealth;
	float  CurrentHealth;
	UHealthComponent* HealthComponent;
	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta, FName BoneName, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	bool bDied;
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	float GetHealth() const { return PlayerHealth; }

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	float GetCurrentHealthHealth() const { return CurrentHealth; }

	FTimerHandle TimerHandle_TimeSetHealth;
	void SetHealth();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void Healing(float Healing);

	UFUNCTION(BlueprintImplementableEvent)
	void Died();

	UFUNCTION(BlueprintImplementableEvent)
	void Attack();

	bool bBossSpawn;

	void SetBossFight(bool bBoss);


private:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;


protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachRightSocket;

	AWeapon* BaseWeapon;
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<AWeapon> StarterBaseWeaponClass;

public:
	void StartFire();

	void StopFire();

	void WalkSpeed();
	void StopSpeed();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

