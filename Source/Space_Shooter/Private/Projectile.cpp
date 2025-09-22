// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "BoundaryVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Collision = racine
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    RootComponent = BoxCollision;

    BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    // Mesh attaché au collision
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(BoxCollision);

    ProjectileSpeed = 1000.f;
    LifeTime = 3.f;
    TimeLived = 0.f;

    // Bind overlap
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHitEnemy);
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Déplacement constant vers l’avant
    AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f), true);

    TimeLived += DeltaTime;
    if (TimeLived >= LifeTime)
    {
        Destroy();
    }

    // Vérification hors limites
    ABoundaryVolume* Boundary = Cast<ABoundaryVolume>(
        UGameplayStatics::GetActorOfClass(GetWorld(), ABoundaryVolume::StaticClass())
    );

    if (Boundary && !Boundary->IsInsideBoundary(GetActorLocation()))
    {
        Destroy();
    }
}

void AProjectile::OnHitEnemy(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                             bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag(TEXT("Enemy")))
    {

        if (AEnemy* Enemy = Cast<AEnemy>(OtherActor))
        {
            Enemy->OnHitByProjectile();
        }

        Destroy(); // détruit le projectile seulement si c'est un ennemi
    }
}



