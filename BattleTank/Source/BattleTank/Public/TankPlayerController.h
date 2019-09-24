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

public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	//метод перемещ€ет ствол туда где перекрестие пересекаетс€ с миром
	void AimTowardsCrosshair();

	//ћы возвращ€ем внешний пареметр будет True если будет попадание в ландшафт
	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
