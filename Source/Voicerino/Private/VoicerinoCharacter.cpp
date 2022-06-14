// Fill out your copyright notice in the Description page of Project Settings.


#include "VoicerinoCharacter.h"

// Sets default values
AVoicerinoCharacter::AVoicerinoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVoicerinoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoicerinoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVoicerinoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

