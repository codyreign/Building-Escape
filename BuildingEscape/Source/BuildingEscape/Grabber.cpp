// ©2017 Cody Serino

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::Grab()
{
	auto hr = GetHitInReach();
	auto component = hr.GetComponent();

	if (GetHitInReach().GetActor() != nullptr)
	{
		PhysicsHandle->GrabComponent(
			component,
			NAME_None,
			component->GetOwner()->GetActorLocation(),
			true
		);
	}


	
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	InitPhysicsHandle();
	InitInputBindings();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{
		//Get the players view point
		FVector loc;
		FRotator rot;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT loc, OUT rot);
		FVector LineTraceEnd = loc + rot.Vector() * reach;
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::InitPhysicsHandle()
{
	//point to physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle not found! Please add physics handle component to default pawn instance!"));
	}
}

void UGrabber::InitInputBindings()
{
	//Discover input component, only appears at runtime
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component not found! Please add Input Component to default pawn instance!"));
	}
	else
	{
		/// BIND INPUT AXIS
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

///Grabs all of the objects in reach and in view
TArray<AActor*> UGrabber::GetActorsInReach(ECollisionChannel echannel)
{
	TArray<FHitResult> hit = GetHitsInReach(echannel);
	TArray<AActor*> ActorOut;
	for (int i = 0; i < hit.Num(); i++)
	{
		ActorOut.Add(hit[i].GetActor());
	}
	return ActorOut;
}
///Grabs first objects in reach and in view
AActor* UGrabber::GetActorInReach(ECollisionChannel echannel)
{
	return GetHitInReach(echannel).GetActor();
}
///Grabs all of the objects in reach and in view
TArray<FHitResult> UGrabber::GetHitsInReach(ECollisionChannel echannel)
{

	TArray<FHitResult> hit;
	//Get the players view point
	FVector loc;
	FRotator rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT loc, OUT rot);
	FVector LineTraceEnd = loc + rot.Vector() * reach;
	//Get object in view point using ray casting
	GetWorld()->LineTraceMultiByObjectType(OUT hit, loc, LineTraceEnd, FCollisionObjectQueryParams(echannel), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	return hit;
}
///Grabs first objects in reach and in view
FHitResult UGrabber::GetHitInReach(ECollisionChannel echannel)
{
	FHitResult hit;
	//Get the players view point
	FVector loc;
	FRotator rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT loc, OUT rot);
	FVector LineTraceEnd = loc + rot.Vector() * reach;
	//Get object in view point using ray casting
	GetWorld()->LineTraceSingleByObjectType(OUT hit, loc, LineTraceEnd, FCollisionObjectQueryParams(echannel), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	return hit;
}