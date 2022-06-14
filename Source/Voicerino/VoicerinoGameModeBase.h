// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/GameModeBase.h"
#include "VoicerinoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VOICERINO_API AVoicerinoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void InputReceived(float Amplitude);

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* NiagaraSystemToSpawnOnAudioInputReceived;
};
