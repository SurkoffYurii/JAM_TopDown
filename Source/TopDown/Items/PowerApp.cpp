// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown/Items/PowerApp.h"
#include "TopDown/TopDownCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
APowerApp::APowerApp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APowerApp::OnOverlapBegin);
    CollisionComp->SetSimulatePhysics(false);
    CollisionComp->SetLinearDamping(0.0f);
    CollisionComp->SetEnableGravity(false);
    RootComponent = CollisionComp;

    PowerAppMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PowerAppMesh"));
    PowerAppMesh->SetupAttachment(RootComponent);

    bHealApp = true;

    Radius = 600.f;
}
void APowerApp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    if ((OtherActor != NULL) && (OtherActor != this)) {
        if (bHealApp) {
            if (OtherActor->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass())) {
                UE_LOG(LogTemp, Warning, TEXT("Heal"));
                if (ATopDownCharacter* MyPawn = Cast<ATopDownCharacter>(OtherActor)) {
                    MyPawn->Healing(BaseHeal);
                    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are Healing: %s"), *OtherActor->GetName()));
                    OneHit();
                }
                //UGameplayStatics::ApplyPointDamage(OtherActor, BaseHeal * -1, OtherActor->GetActorLocation(), SweepResult, nullptr, this, DamageType);
               
            }          
        }
        if (bDetanate) {
            if (OtherActor->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass())) {
                OnDetanate();
                OneHit();
            }
        }
        if (bInteract) {
            if (bUseInteract) {
                if (OtherActor->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass())) {
                    bUseInteract = false;
                    Interact();
                }
            }
        }
        
    }
}

void APowerApp::OnDetanate() {
    TArray<FHitResult> HitActors;

    FVector StartTrace = GetActorLocation();
 

    FCollisionShape CollisionShape;
    CollisionShape.ShapeType = ECollisionShape::Sphere;
    CollisionShape.SetSphere(Radius);
    DrawDebugSphere(GetWorld(), GetActorLocation(), CollisionShape.GetSphereRadius(), 50, FColor::Purple, true, 1.f);
    if (GetWorld()->SweepMultiByChannel(HitActors, StartTrace, StartTrace, FQuat::Identity,ECC_WorldStatic, CollisionShape)) {
        for (auto& Hit : HitActors) {
            if (!Hit.GetActor()->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass())) {
                UGameplayStatics::ApplyPointDamage(Hit.GetActor(), BaseDamage, Hit.GetActor()->GetActorLocation(), Hit, nullptr, this, DamageType);
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *Hit.GetActor()->GetName()));
                UE_LOG(LogTemp, Warning, TEXT("Hit"));

            }
        }

    }
}

void APowerApp::OneHit() {
    //UE_LOG(LogTemp, Warning, TEXT("Hit"));
    SetLifeSpan(0.5f);

}

// Called when the game starts or when spawned
void APowerApp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerApp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

