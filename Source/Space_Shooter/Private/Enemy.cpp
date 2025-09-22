// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "SpaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BoundaryVolume.h"
#include "Components/BoxComponent.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Enemy"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	BoxCollision->SetSimulatePhysics(false);
	BoxCollision->SetCollisionProfileName("OverlapAllDynamic");
	BoxCollision->SetGenerateOverlapEvents(true);
	

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

