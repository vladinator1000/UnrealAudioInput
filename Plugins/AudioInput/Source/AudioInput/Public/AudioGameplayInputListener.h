// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioInput.h"
#include "Components/ActorComponent.h"
#include "AudioGameplayInputListener.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioGameplayInputDelegate, float, Amplitude);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUDIOINPUT_API UAudioGameplayInputListener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudioGameplayInputListener();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.02, ClampMax = 0.2))
	float FilterThreshold = 0.07f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.0, ClampMax = 2))
	float AttackTimeMsec = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.1, ClampMax = 2))
	float ReleaseTimeMsec = 0.8f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.5, ClampMax = 2))
	float AnalysisWindowMsec = 1.0f;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateEnvelopeFollowerParams();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UAudioInputSubsystem* AudioInputSubsystem;

	UPROPERTY(BlueprintAssignable)
	FOnAudioGameplayInputDelegate OnAudioGameplayInputDelegate;
};
