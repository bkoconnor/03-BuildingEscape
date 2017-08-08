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
    if(GetMaterialOfActor() != nullptr)
    {
        OnOpen.Broadcast();
        //UE_LOG(LogTemp, Warning, TEXT("opening cabinet"));
    }
    //}
	// ...
    
    //check if its time to close the door
    
    
}

// get material of actors in trigger volume (bowl puzzle)
UMaterialInterface* UOpenDoor::GetMaterialOfActor()
{
    TArray<AActor*> OverlappingActors;
    if(!PressurePlate){return nullptr;}
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    UMaterialInterface* TestMaterial;
    bool flag = true;
    
    //loop through actors in trigger volumes, set flag to false if one of them does not match the correct bowl
    for(const auto& Actor : OverlappingActors)
    {
        TestMaterial = Actor->FindComponentByClass<UStaticMeshComponent>()->GetMaterial(0);
        if(TestMaterial != TriggerMaterial)
        {
            flag = false;
        }
    }
    if(flag == false)
    {
        return nullptr;
    }
    else
    {
        return TestMaterial;
    }
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
