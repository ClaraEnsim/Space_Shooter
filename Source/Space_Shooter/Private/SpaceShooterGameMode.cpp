// Fill out your copyright notice in the Description page of Project Settings.


#include "Space_Shooter/Public/SpaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"

ASpaceShooterGameMode::ASpaceShooterGameMode()
{
	MaxScore = 10;
	InitialLives = 3;
	CurrentScore = 0;
	CurrentLives = InitialLives;
}

void ASpaceShooterGameMode::AddPoint()
{
	CurrentScore++;

	if (CurrentScore >= MaxScore)
	{
		CheckGameOver();
	}
}

void ASpaceShooterGameMode::LoseLife()
{
	CurrentLives--;

	if (CurrentLives <= 0)
	{
		CheckGameOver();
	}
}

void ASpaceShooterGameMode::CheckGameOver()
{
	if (CurrentScore >= MaxScore)
	{
		UE_LOG(LogTemp, Warning, TEXT("Victoire ! Score atteint."));
		// TODO : déclencher un écran de victoire via Blueprint ou HUD
	}
	else if (CurrentLives <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Over ! Plus de vies."));
		// TODO : déclencher un écran de défaite via Blueprint ou HUD
	}
}


