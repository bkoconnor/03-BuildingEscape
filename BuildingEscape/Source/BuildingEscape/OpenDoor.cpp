// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"
#include "Gameframework/Actor.h"

#define OUT

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
    Owner = GetOwner();
    if(!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
    }
   
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //if(ActorThatOpens != nullptr)
    //{
        if(GetTotalMassOfActorsOnPlate() > TriggerMass)
        {
            OnOpen.Broadcast();
        }
        else
        {
            
                //UE_LOG(LogTemp, Warning, TEXT("CLOSING"));
                OnClose.Broadcast();
        }
    if(DoMaterialsMatchContainer() == true)
    {
        OnOpen.Broadcast();
    }
    else
    {
        OnClose.Broadcast();
    }
    //}
	// ...
    
    //check if its time to close the door
    
    
}

// get material of actors in trigger volume (bowl puzzle)
bool UOpenDoor::DoMaterialsMatchContainer()
{
    TArray<AActor*> OverlappingActors;
    if(!PressurePlate){return false;}
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    UMaterialInterface* TestMaterial;
    //bool flag;
    
    //loop through actors in trigger volumes, set flag to false if one of them does not match the correct bowl
    if(OverlappingActors.Num() == 0){return false;} // if there are no actors in bowls, do not test and return false
    for(const auto& Actor : OverlappingActors)
    {
        TestMaterial = Actor->FindComponentByClass<UStaticMeshComponent>()->GetMaterial(0);
        //if any blocks are not the right material, return false
        if(TestMaterial != TriggerMaterial)
        {
            return false;
        }
        return true;
    }
    return false;
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0.f;
    
    //find all overlapping actors
    TArray<AActor*> OverlappingActors;
    if(!PressurePlate){return TotalMass;}
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    
    //iterate through them adding their mass
    for(const auto& Actor : OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
    }
    
    return TotalMass;
}
