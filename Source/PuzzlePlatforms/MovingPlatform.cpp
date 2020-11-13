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
}

void AMovingPlatform::Tick(float DeltaTime){
  Super::Tick(DeltaTime);

  // Server Code
  if(HasAuthority()){
    FVector Location = GetActorLocation();
    Location += FVector(Speed * DeltaTime,0,0); // 5 cm/s * some num sec = 5cm every tick 
    SetActorLocation(Location);
  }
}

