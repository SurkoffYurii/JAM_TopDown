// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerApp.generated.h"

UCLASS()
class TOPDOWN_API APowerApp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerApp();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* PowerAppMesh;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Interact")
	bool bInteract;
	UFUNCTION(BlueprintImplementableEvent)
	void Interact();
	bool bUseInteract;

	UPROPERTY(EditDefaultsOnly, Category = "HealApp")
	bool bHealApp;
	UPROPERTY(EditDefaultsOnly, Category = "HealApp")
	float BaseHeal;

	UPROPERTY(EditDefaultsOnly, Category = "Detanate")
	bool bDetanate;
	UPROPERTY(EditDefaultsOnly, Category = "Detanate")
	float BaseDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Detanate")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditDefaultsOnly, Category = "Detanate")
	float Radius;
	void OnDetanate();

	void OneHit();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
