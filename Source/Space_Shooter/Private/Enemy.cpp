// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "SpaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BoundaryVolume.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	RootComponent = EnemyMesh;

	EnemyMesh->SetSimulatePhysics(false);
	EnemyMesh->SetCollisionProfileName("BlockAll");

	MoveSpeed = 200.f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	MoveDirection = FVector(FMath::RandRange(-1.f, 1.f), FMath::RandRange(-1.f, 1.f), 0.f).GetSafeNormal();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(MoveDirection * MoveSpeed * DeltaTime, true);

	ABoundaryVolume* Boundary = Cast<ABoundaryVolume>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ABoundaryVolume::StaticClass())
	);

	if (Boundary && !Boundary->IsInsideBoundary(GetActorLocation()))
	{
		Destroy(); // supprime l'ennemi si sorti de la map
	}
}

void AEnemy::OnHitByProjectile()
{
	if (ASpaceShooterGameMode* GM = Cast<ASpaceShooterGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GM->AddPoint();
	}
	Destroy();
}

