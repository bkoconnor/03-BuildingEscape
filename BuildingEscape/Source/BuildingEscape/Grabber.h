// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    float Reach = 110.f;
		
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* InputComponent = nullptr;
    
    // Ray-cast and grab what is in reach
    void Grab();
    void Release();
    
    void FindPhysicsHandleComponent();
    void SetupInputComponent();
    
    //return hit for first physics body in reach
    const FHitResult GetFirstPhysicsBodyInReach();
    
    //returns current reach start
    FVector GetReachLineStart();
    
    //returns current reach end
    FVector GetReachLineEnd();
};
