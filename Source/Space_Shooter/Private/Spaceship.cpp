// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "Components/BoxComponent.h"
#include "Projectile.h"
#include "BoundaryVolume.h"
#include "SpaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASpaceship::ASpaceship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	
	CollisionBox->SetCollisionProfileName(TEXT("Pawn"));
	CollisionBox->SetGenerateOverlapEvents(true);

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetupAttachment(RootComponent);
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MoveSpeed = 600.f;
	FireRate = 0.25f;
	LastFireTime = -FireRate;

	AutoPossessPlayer = EAutoReceiveInput::Player0;


	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpaceship::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Vérifier limites
	ABoundaryVolume* Boundary = Cast<ABoundaryVolume>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ABoundaryVolume::StaticClass())
	);

	if (Boundary && !Boundary->IsInsideBoundary(GetActorLocation()))
	{
		// On recadre le vaisseau à l’intérieur
		FVector NewLocation = GetActorLocation();
		FBox Bounds = Boundary->GetComponentsBoundingBox();

		// Clamp les positions dans la box
		NewLocation.X = FMath::Clamp(NewLocation.X, Bounds.Min.X, Bounds.Max.X);
		NewLocation.Y = FMath::Clamp(NewLocation.Y, Bounds.Min.Y, Bounds.Max.Y);

		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ASpaceship::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceship::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceship::FireProjectile);
}

void ASpaceship::MoveForward(float Value)
{
	AddActorLocalOffset(FVector(Value * MoveSpeed * GetWorld()->GetDeltaSeconds(), 0.f, 0.f), true);
}

void ASpaceship::MoveRight(float Value)
{
	AddActorLocalOffset(FVector(0.f, Value * MoveSpeed * GetWorld()->GetDeltaSeconds(), 0.f), true);
}

void ASpaceship::FireProjectile()
{
	GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Red,"FireProjectile1");
	if (ProjectileClass && GetWorld()->TimeSeconds - LastFireTime >= FireRate)
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Red,"FireProjectile2");
		FVector SpawnLocation = GetActorLocation() + FVector(100.f, 0.f, 0.f);
		FRotator SpawnRotation = GetActorRotation();

		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		LastFireTime = GetWorld()->TimeSeconds;
	}
}

void ASpaceship::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor->ActorHasTag(TEXT("Enemy")))
	{
		if (ASpaceShooterGameMode* GM = Cast<ASpaceShooterGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			GM->LoseLife();
		}
	}
}

