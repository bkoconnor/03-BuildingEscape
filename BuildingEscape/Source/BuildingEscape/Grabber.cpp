// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
    
    
    

	// ...
	
}

void UGrabber::FindPhysicsHandleComponent()
{
    // look for attached physics handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
    }

}

void UGrabber::SetupInputComponent()
{
    // look for attached input component (appears at run time
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(InputComponent)
    {
        // bind the input axis
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
    }
}



void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
    
    //LINE TRACE and reach any actors with physics body collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    
    if(ActorHit)
    {
        //If we hit something, attach a physics handle
        PhysicsHandle->GrabComponentAtLocationWithRotation(
            ComponentToGrab,
            NAME_None,
            ComponentToGrab->GetOwner()->GetActorLocation(),
            FRotator(0));
    }
}

void UGrabber::Release()
{
    //release physics handle
    PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    
    //if the physics handle is attached
    if(PhysicsHandle->GrabbedComponent)
    {
        //move the object that we are holding
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }


	// ...
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    
    
    
    //setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    //    UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
    //ray cast out to specified reach distance
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT HitResult,
                                            GetReachLineStart(),
                                            GetReachLineEnd(),
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters);
    
    //capture what is hit
    AActor * ActorHit = HitResult.GetActor();
    
    return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
    
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    //Get player view point this frame/tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation);
    return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
    
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    //Get player view point this frame/tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation);
    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
