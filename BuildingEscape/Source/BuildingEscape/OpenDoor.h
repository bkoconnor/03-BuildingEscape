// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BluePrintAssignable)
    FDoorEvent OnOpen;
    
    UPROPERTY(BluePrintAssignable)
    FDoorEvent OnClose;
    
private:
	
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    
    UPROPERTY(EditAnywhere)
    float TriggerMass = 30.f;
    
    UPROPERTY(EditAnywhere)
    UMaterialInterface* TriggerMaterial = nullptr;
    
    AActor* Owner = nullptr;
    
    float GetTotalMassOfActorsOnPlate(); //returns total mass in kg
    
    //FORCEINLINE class UStaticMeshComponent* GetMesh() const {return PaintBlobMesh;}
    
    bool DoMaterialsMatchContainer();
	
};
