// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/WorldSettings.h"
#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else

	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %S"), *(ControlledTank->GetName()));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		
		//если луч попадает в ландшафт
		//то тогга мы хотим чтобы контролируемый танк наводил прицел на эту точку
	}
}

//получить положение в мире (кардинаты) если луч проходит через прицел true  если попадает в ландшафт
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Нужно найти положение прицела
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	//Дипроэкция положения прицела в мировое напровление 
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	//Посылание луча вдоль напровления нашего взора и смотрим во что мы попали

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector&HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	/*Если посылание луча происходит успешно*/
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		//устанавливаем место попадания
		HitLocation=HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;//посылание луча терпит неудачу
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}