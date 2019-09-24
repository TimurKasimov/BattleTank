// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "TankPlayerController.generated.h"


 
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	//метод перемещ€ет ствол туда где перекрестие пересекаетс€ с миром
	void AimTowardsCrosshair();

	//ћы возвращ€ем внешний пареметр будет True если будет попадание в ландшафт
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector&HitLocation) const;
};

