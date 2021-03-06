// ©2017 Cody Serino

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitPhysicsHandle();

	void InitInputBindings();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		float reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	void Grab();
	TArray<AActor*>  GetActorsInReach(ECollisionChannel channel = ECollisionChannel::ECC_PhysicsBody);
	AActor* GetActorInReach(ECollisionChannel echannel = ECollisionChannel::ECC_PhysicsBody);
	TArray<FHitResult>  GetHitsInReach(ECollisionChannel channel = ECollisionChannel::ECC_PhysicsBody);
	FHitResult GetHitInReach(ECollisionChannel echannel = ECollisionChannel::ECC_PhysicsBody);
	void Release();
};
