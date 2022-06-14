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

    static int16 constexpr AudioBufferSize = 16;

	UPROPERTY(EditAnywhere)
    float FilterThreshold = 0.07f;
	
    UPROPERTY(BlueprintAssignable)
    FOnSoundDelegate OnSoundDelegate;

	Audio::FEnvelopeFollowerInitParams EnvelopeFollowerInitParams;
	

private:
    Audio::FAudioCapture AudioCapture;
	Audio::FEnvelopeFollower EnvelopeFollower;
};
