// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
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

protected: // Score et vies du joueur

	//Maximum de points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 MaxScore;

	//Initialisation des vies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 InitialLives;

	//compteur de points
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	int32 CurrentScore;

	//compteur de vies
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	int32 CurrentLives;

	// Référence vers le Widget de victoire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> VictoryScreenClass;

	// Référence vers le Widget de GameOver
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> GameOverScreenClass;

	// Instance du widget courant affiché
	UUserWidget* CurrentWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay")
	bool bGameOver; // Bloque les inputs et actions

public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int32 GetPoint();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int32 GetPointLife();
	
	// Appelée quand une cible est détruite
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void AddPoint();

	// Appelée quand le joueur subit une collision
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void LoseLife();

	// Vérifie conditions de victoire ou défaite
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void CheckGameOver();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ResetGame(); // Réinitialise le jeu pour Replay
};
