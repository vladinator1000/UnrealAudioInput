// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AudioCaptureCore.h"
#include "CoreMinimal.h"
#include "Subsystems/AudioEngineSubsystem.h"
#include "AudioInputSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSoundDelegate, float, Amplitude);

/**
 * Lets you trigger gameplay using audio input from a microphone.
 */
UCLASS()
class AUDIOINPUT_API UAudioInputSubsystem : public UGameInstanceSubsystem {
  GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
	float Poll() const;

    static int16 constexpr AudioBufferSize = 32;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ClampMin=0.05, ClampMax=0.1))
    float FilterThreshold = 0.07f;
	
	Audio::FEnvelopeFollowerInitParams EnvelopeFollowerInitParams;

private:
    Audio::FAudioCapture AudioCapture;
	Audio::FEnvelopeFollower EnvelopeFollower;
	float EnvelopeValue;
};
