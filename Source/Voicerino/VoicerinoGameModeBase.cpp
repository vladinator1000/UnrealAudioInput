// Copyright Epic Games, Inc. All Rights Reserved.


#include "VoicerinoGameModeBase.h"
#include "AudioInput.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

AVoicerinoGameModeBase::AVoicerinoGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVoicerinoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	const auto GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	AudioInputSubsystem = GameInstance->GetSubsystem<UAudioInputSubsystem>();
	AudioInputSubsystem->FilterThreshold = 0.06f;
}

void AVoicerinoGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const float AudioInputAmplitude = AudioInputSubsystem->Poll();
	if(AudioInputAmplitude > 0.f)
	{
		InputReceived(AudioInputAmplitude);
	}
}


void AVoicerinoGameModeBase::InputReceived(float Amplitude)
{
	const FVector Location = FVector(0,0, 500.f * Amplitude);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystemToSpawnOnAudioInputReceived, Location);
}
