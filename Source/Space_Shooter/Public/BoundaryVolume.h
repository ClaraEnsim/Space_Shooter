// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoundaryVolume.generated.h"

UCLASS()
class SPACE_SHOOTER_API ABoundaryVolume : public AActor
{
	GENERATED_BODY()

public:
	ABoundaryVolume();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* Box;

public:
	// Vérifie si un point est à l'intérieur
	bool IsInsideBoundary(const FVector& Position) const;
};

