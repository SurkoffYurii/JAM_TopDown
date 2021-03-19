// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown/Enemy/BossSpawnActor.h"
#include "TopDown/Enemy/Enemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TopDown/TopDownCharacter.h"

// Sets default values
ABossSpawnActor::ABossSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TorchValue = 1.f;
	CurrentTorchValue = 0.f;
}


void ABossSpawnActor::TorchActiveted() {
	UE_LOG(LogTemp, Warning, TEXT("SpawAciveted"));

	CurrentTorchValue++;
	if (CurrentTorchValue == TorchValue) {
		BossSpanw();
	}
}

void  ABossSpawnActor::AllEnemyStop() {
	TSubclassOf<AEnemy> ClassToFind;
	ClassToFind = AEnemy::StaticClass();
	TArray<AActor*> FoundActors;
	UE_LOG(LogTemp, Warning, TEXT("StopEnemyStart"));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);
	for (auto& Enemy : FoundActors) {
		//if (Enemy->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass())) {
			if (AEnemy* CurrEnemy = Cast<AEnemy>(Enemy)) {
				CurrEnemy->StopMove();
				UE_LOG(LogTemp, Warning, TEXT("StopEnemy"));
			}
		//}
	}
	TSubclassOf<ATopDownCharacter> ClassToPlayer;
	ClassToPlayer = ATopDownCharacter::StaticClass();
	TArray<AActor*> FoundActorsPlayers;
	//UE_LOG(LogTemp, Warning, TEXT("StopPlayerStart"));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToPlayer, FoundActorsPlayers);
	for (auto& Player : FoundActorsPlayers) {
		//if (Enemy->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass())) {
		if (ATopDownCharacter* CurPlayer = Cast<ATopDownCharacter>(Player)) {
			CurPlayer->SetBossFight(true);
			UE_LOG(LogTemp, Warning, TEXT("StopPlayer"));
		}
		//}
	}

}
void  ABossSpawnActor::AllEnemyGo() {
	TSubclassOf<AEnemy> ClassToFind;
	ClassToFind = AEnemy::StaticClass();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++) {
		//if (Enemy->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass())) {
			if (AEnemy* CurrEnemy = Cast<AEnemy>(FoundActors[i])) {
				CurrEnemy->GoMove();
				UE_LOG(LogTemp, Warning, TEXT("GoEnemy"));
			}
		//}
	}
	TSubclassOf<ATopDownCharacter> ClassToPlayer;
	ClassToPlayer = ATopDownCharacter::StaticClass();
	TArray<AActor*> FoundActorsPlayers;
	//UE_LOG(LogTemp, Warning, TEXT("StopPlayerStart"));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToPlayer, FoundActorsPlayers);
	for (auto& Player : FoundActorsPlayers) {
		//if (Enemy->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass())) {
		if (ATopDownCharacter* CurPlayer = Cast<ATopDownCharacter>(Player)) {
			CurPlayer->SetBossFight(false);
			UE_LOG(LogTemp, Warning, TEXT("StartPlayer"));
		}
		//}
	}
}
// Called when the game starts or when spawned
void ABossSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

