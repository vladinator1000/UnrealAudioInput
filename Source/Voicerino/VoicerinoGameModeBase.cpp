// Copyright Epic Games, Inc. All Rights Reserved.


#include "VoicerinoGameModeBase.h"
#include "AudioInput.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

void AVoicerinoGameModeBase::BeginPlay()
{
	const auto GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UAudioInputSubsystem* AudioInput = GameInstance->GetSubsystem<UAudioInputSubsystem>();
	AudioInput->OnSoundDelegate.AddDynamic(this, &AVoicerinoGameModeBase::InputReceived);
}

void AVoicerinoGameModeBase::InputReceived(float Amplitude)
{
	DrawDebugPoint(GetWorld(), FVector(0,0, 50.f), 30.f, FColor::White);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystemToSpawnOnAudioInputReceived, FVector());
}
