// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TopDown/Enemy/BossSpanwInterface.h"
#include "BossSpawnActor.generated.h"

UCLASS()
class TOPDOWN_API ABossSpawnActor : public AActor, public IBossSpanwInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSpawnActor();


	UPROPERTY(EditAnywhere, Category = "BossSpawn")
	float TorchValue;

	float CurrentTorchValue;
	void TorchActiveted();

	UFUNCTION(BlueprintImplementableEvent)
	void BossSpanw();


	UFUNCTION(BlueprintCallable, Category = "EnemyMovement")
	void AllEnemyStop();

	UFUNCTION(BlueprintCallable, Category = "EnemyMovement")
	void AllEnemyGo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
