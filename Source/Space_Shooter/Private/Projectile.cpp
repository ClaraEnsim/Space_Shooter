// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "BoundaryVolume.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMesh->SetSimulatePhysics(false);
	ProjectileMesh->SetCollisionProfileName("BlockAll");

	ProjectileSpeed = 1000.f;
	LifeTime = 3.f;
	TimeLived = 0.f;

	OnActorHit.AddDynamic(this, &AProjectile::OnHitEnemy);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f), true);

	TimeLived += DeltaTime;
	if (TimeLived >= LifeTime)
	{
		Destroy();
	}

	ABoundaryVolume* Boundary = Cast<ABoundaryVolume>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ABoundaryVolume::StaticClass())
	);

	if (Boundary && !Boundary->IsInsideBoundary(GetActorLocation()))
	{
		Destroy(); // supprime l'ennemi si sorti de la map
	}

}

void AProjectile::OnHitEnemy(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Enemy")))
	{
		if (AEnemy* Enemy = Cast<AEnemy>(OtherActor))
		{
			Enemy->OnHitByProjectile();
		}
		Destroy();
	}
}

