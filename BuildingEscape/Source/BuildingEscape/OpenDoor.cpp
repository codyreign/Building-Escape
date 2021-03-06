// ©2017 Cody Serino

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		doorOpen = false;

		float stackMass = 0;
		TArray<AActor*> actors;
		PressurePlate->GetOverlappingActors(OUT actors);
	for (const auto &Actor : actors)
	{
		stackMass+=Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		if (stackMass >= TriggerMass)
		{
			doorOpen = true;
		}
	}


	if (doorOpen)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
	// ...
}

