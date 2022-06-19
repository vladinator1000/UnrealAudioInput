// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AudioCaptureCore.h"
#include "CoreMinimal.h"
#include "Subsystems/AudioEngineSubsystem.h"
#include "AudioInputSubsystem.generated.h"

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

	Audio::FEnvelopeFollowerInitParams EnvelopeFollowerInitParams;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateEnvelopeFollowerParams(float AttackMs, float ReleaseMs, float AnalysisWindowM);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.02, ClampMax = 0.2))
	float FilterThreshold = 0.07f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.0, ClampMax = 2))
	float AttackTimeMsec = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.1, ClampMax = 2))
	float ReleaseTimeMsec = 0.8f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.5, ClampMax = 2))
	float AnalysisWindowMsec = 1.0f;

private:
    Audio::FAudioCapture AudioCapture;
	Audio::FEnvelopeFollower EnvelopeFollower;
	float EnvelopeValue;
};
