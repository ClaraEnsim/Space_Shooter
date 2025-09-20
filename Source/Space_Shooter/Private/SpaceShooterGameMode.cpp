// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShip.h"
#include "Blueprint/UserWidget.h"

ASpaceShooterGameMode::ASpaceShooterGameMode()
{
	MaxScore = 10;
	InitialLives = 3;
	CurrentScore = 0;
	CurrentLives = InitialLives;
	bGameOver = false;

	DefaultPawnClass = ASpaceship::StaticClass();
	CurrentWidget = nullptr;
}

int32 ASpaceShooterGameMode::GetPoint() { return CurrentScore; }
int32 ASpaceShooterGameMode::GetPointLife() { return CurrentLives; }

void ASpaceShooterGameMode::AddPoint()
{
	if (bGameOver) return;

	CurrentScore++;
	if (CurrentScore >= MaxScore)
	{
		CheckGameOver();
	}
}

void ASpaceShooterGameMode::LoseLife()
{
	if (bGameOver) return;

	CurrentLives--;
	if (CurrentLives <= 0)
	{
		CheckGameOver();
	}
}

void ASpaceShooterGameMode::CheckGameOver()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	bGameOver = true;

	if (PC && PC->GetPawn())
	{
		PC->GetPawn()->DisableInput(PC);
		PC->bShowMouseCursor = true;
	}

	if (CurrentScore >= MaxScore && VictoryScreenClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), VictoryScreenClass);
		if (CurrentWidget) CurrentWidget->AddToViewport();
	}
	else if (CurrentLives <= 0 && GameOverScreenClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverScreenClass);
		if (CurrentWidget) CurrentWidget->AddToViewport();
	}
}

void ASpaceShooterGameMode::ResetGame()
{
	// Supprimer le widget
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	// Réinitialiser les compteurs
	CurrentScore = 0;
	CurrentLives = InitialLives;
	bGameOver = false;

	// Réactiver l’input du joueur
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC && PC->GetPawn())
	{
		PC->GetPawn()->EnableInput(PC);
		PC->bShowMouseCursor = false;
	}

	// Optionnel : repositionner le joueur et respawner les ennemis
	if (ASpaceship* Ship = Cast<ASpaceship>(PC->GetPawn()))
	{
		Ship->SetActorLocation(FVector::ZeroVector); // ou ta position de départ
	}
}


