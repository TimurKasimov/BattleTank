// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/WorldSettings.h"
#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() 
{
	Super:: BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %S"),*(ControlledTank->GetName()));
	}

}
ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}
