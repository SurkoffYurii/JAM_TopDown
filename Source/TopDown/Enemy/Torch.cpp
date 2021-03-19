// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown/Enemy/Torch.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopDown/TopDownCharacter.h"
#include "DrawDebugHelpers.h"
#include "TopDown/Enemy/Enemy.h"
#include "TopDown/Enemy/BossSpawnActor.h"

// Sets default values
ATorch::ATorch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATorch::OnOverlapBegin);
    CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATorch::OnOverlapEnd);
    CollisionComp->SetSimulatePhysics(false);
    CollisionComp->SetLinearDamping(0.0f);
    CollisionComp->SetEnableGravity(false);
    RootComponent = CollisionComp;

    PowerAppMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PowerAppMesh"));
    PowerAppMesh->SetupAttachment(RootComponent);


    bOverLap = false;
    bActivate = true;

}

void ATorch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    if ((OtherActor != NULL) && (OtherActor != this)) {
        if (OtherActor->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass())) {
            if (ATopDownCharacter* MyPawn = Cast<ATopDownCharacter>(OtherActor)) {
                UE_LOG(LogTemp, Warning, TEXT("TorchActivate"));
                bOverLap = true;
                if (bActivate) {
                    UnHidenWidget();
                }

            }

        }
    }
}

void ATorch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    if ((OtherActor != NULL) && (OtherActor != this)) {
        if (OtherActor->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass())) {
            //if (ATopDownCharacter* MyPawn = Cast<ATopDownCharacter>(OtherActor)) {
                UE_LOG(LogTemp, Warning, TEXT("TorchDiActivate"));
                bOverLap = false;
                HidenWidget();
           // }

        }
    }
}

void ATorch::Activate() { 
    if (ABossSpawnActor* BassSpawn = Cast<ABossSpawnActor>(BossSpawnActor)) {
        BassSpawn->TorchActiveted();
        UE_LOG(LogTemp, Warning, TEXT("BossSpawnActorActivate"));
        HidenWidget();
    }
}

// Called when the game starts or when spawned
void ATorch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


    if (bOverLap) {
        CurrentActivateValue++;
        
    }
    else {
        CurrentActivateValue = 0.f;
    }

    if (CurrentActivateValue == ActivateValue) {
        if (bActivate) {
            bActivate = false;
            Activate();
        }
    }

}

