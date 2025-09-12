// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SPACE_SHOOTER_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
    virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<class AEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, Category="Spawning")
	float SpawnInterval;

	FTimerHandle SpawnTimer;

public:
	void SpawnEnemy();
};
