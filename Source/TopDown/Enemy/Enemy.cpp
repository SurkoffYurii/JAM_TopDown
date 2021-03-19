// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown/Enemy/Enemy.h"
#include "TopDown/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "TopDown/CharacterInterface.h"
//#include "Components/CapsuleComponent.h
 #include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Health компонент
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	InteractionObject = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	InteractionObject->SetupAttachment(RootComponent);
	InteractionObject->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);

	BaseSpeed = 300.f;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;

	EnemyHealth = 100.f;

	BaseDamage = 20.f;
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor != NULL) && (OtherActor != this)) {
		if (OtherActor->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass())) {
			UGameplayStatics::ApplyPointDamage(OtherActor, BaseDamage, OtherActor->GetActorLocation(), SweepResult, nullptr, this, EnemyDamageType);
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("You are hitting: %s"), *SweepResult.GetActor()->GetName()));
			UE_LOG(LogTemp, Warning, TEXT("HitPlayer"));
			Attack();
		}
	}
}

void AEnemy::SetHealth() {
	HealthComponent->SetParams(EnemyHealth);
}


void AEnemy::StopMove() {
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
}

void AEnemy::GoMove() {
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();


	//HealthComp
	HealthComponent->OnHealthChanged.AddDynamic(this, &AEnemy::OnHealthChanged);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeSetHealth, this, &AEnemy::SetHealth, 0.2f, false);
	
}


void AEnemy::OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta, FName BoneName, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {
	if (Health <= 0.0f) {
		//Умер
		bDied = true;

		DetachFromControllerPendingDestroy();

		SetLifeSpan(0.1f);
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Bot health: %s"), Health));
		UE_LOG(LogTemp, Warning, TEXT("dead"));
		//GetMovementComponent()->StopMovementImmediately();
		//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


