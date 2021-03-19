// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torch.generated.h"


class ABossSpawnActor;
UCLASS()
class TOPDOWN_API ATorch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorch();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BossSpawnActor")
	ABossSpawnActor* BossSpawnActor;

	UPROPERTY(EditDefaultsOnly, Category = "BossSpawnActor")
	TSubclassOf<ABossSpawnActor> StarterBossSpawnActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* PowerAppMesh;

	bool bOverLap;
	bool bActivate;
	UPROPERTY(EditDefaultsOnly, Category = "Torch")
	float ActivateValue;
	float CurrentActivateValue = 0.f;
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	float Activatedpercent() const { return CurrentActivateValue/ActivateValue; }
	void Activate();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void HidenWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void UnHidenWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
