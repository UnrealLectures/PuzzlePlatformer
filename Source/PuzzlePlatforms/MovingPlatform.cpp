// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform(){
  PrimaryActorTick.bCanEverTick = true;

  SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay(){
  Super::BeginPlay();

  // Server Code
  if(HasAuthority()){
    SetReplicates(true);
    SetReplicateMovement(true);
  }

  GlobalStartLocation = GetActorLocation();
  GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime){
  Super::Tick(DeltaTime);

  // Server Code
  if(HasAuthority()){
    FVector Location = GetActorLocation();
    float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
    float JourneyTravelled = (Location - GlobalStartLocation).Size();

    if(JourneyTravelled >= JourneyLength){
      FVector Temp = GlobalTargetLocation;
      GlobalTargetLocation = GlobalStartLocation;
      GlobalStartLocation = Temp;
    }

    FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
    Location += Speed * DeltaTime * Direction; // 5 cm/s * some num sec = 5cm every tick 
    SetActorLocation(Location);
  }
}

