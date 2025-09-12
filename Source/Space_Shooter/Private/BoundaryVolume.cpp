#include "BoundaryVolume.h"
#include "Components/BoxComponent.h"

ABoundaryVolume::ABoundaryVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	// Crée le box component pour la limite
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundaryBox"));
	RootComponent = Box;

	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Box->SetBoxExtent(FVector(500.f, 500.f, 500.f)); // par défaut, tu peux ajuster dans Blueprint
}

bool ABoundaryVolume::IsInsideBoundary(const FVector& Position) const
{
	if (!Box) return false;

	// Bounding box locale + position
	FVector LocalPos = Box->GetComponentTransform().InverseTransformPosition(Position);
	FVector Extent = Box->GetUnscaledBoxExtent();

	return FMath::Abs(LocalPos.X) <= Extent.X &&
		   FMath::Abs(LocalPos.Y) <= Extent.Y &&
		   FMath::Abs(LocalPos.Z) <= Extent.Z;
}
