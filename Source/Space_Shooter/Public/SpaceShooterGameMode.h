// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SHOOTER_API ASpaceShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpaceShooterGameMode();

protected:
	// Score et vies du joueur
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 MaxScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 InitialLives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	int32 CurrentScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	int32 CurrentLives;

public:
	// Appelée quand une cible est détruite
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void AddPoint();

	// Appelée quand le joueur subit une collision
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void LoseLife();

	// Vérifie conditions de victoire ou défaite
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void CheckGameOver();
};
