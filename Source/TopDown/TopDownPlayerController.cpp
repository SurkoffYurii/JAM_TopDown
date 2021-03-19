// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TopDownCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TopDown/Enemy/Enemy.h"
#include "Kismet/KismetMathLibrary.h"


ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDownPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor){
		MoveToMouseCursor();
	}

}

void ATopDownPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATopDownPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATopDownPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("DontMove", IE_Pressed, this, &ATopDownPlayerController::DontCanMove);
	InputComponent->BindAction("DontMove", IE_Released, this, &ATopDownPlayerController::CanMove);

}



void ATopDownPlayerController::MoveToMouseCursor()
{

		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
				// We hit something, move there
				SetNewMoveDestination(Hit.ImpactPoint);
		}
}

void ATopDownPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATopDownPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;

	if (ATopDownCharacter* MyPawn = Cast<ATopDownCharacter>(GetPawn())) {
		if (bCanMove == false) {
			MyPawn->StartFire();
		}
		FHitResult TraceHitResult;
		GetHitResultUnderCursor(ECC_Pawn, true, TraceHitResult);
		AEnemy* Enemy = Cast<AEnemy>(TraceHitResult.GetActor());
		if (Enemy) {
			FRotator NewPalyerRotate = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Enemy->GetActorLocation());
			MyPawn->SetActorRotation(NewPalyerRotate);
			MyPawn->StartFire();
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are targeting: %s"), *Enemy->GetName()));
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("You are targeting: %s"), *TraceHitResult.GetActor()->GetName()));
	}
}

void ATopDownPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
	if (ATopDownCharacter* MyPawn = Cast<ATopDownCharacter>(GetPawn())) {
			MyPawn->StopFire();
	}
}
void ATopDownPlayerController::DontCanMove() {
	bCanMove = false;
	if (ATopDownCharacter* MyPawn = Cast<ATopDownCharacter>(GetPawn())) {
		MyPawn->StopSpeed();
	}
}
void ATopDownPlayerController::CanMove() {
	bCanMove = true;
	if (ATopDownCharacter* MyPawn = Cast<ATopDownCharacter>(GetPawn())) {
		MyPawn->WalkSpeed();
		MyPawn->StopFire();
	}
}