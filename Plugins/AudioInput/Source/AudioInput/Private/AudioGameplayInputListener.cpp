// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioGameplayInputListener.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAudioGameplayInputListener::UAudioGameplayInputListener()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAudioGameplayInputListener::UpdateEnvelopeFollowerParams()
{
	AudioInputSubsystem->FilterThreshold = FilterThreshold;
	AudioInputSubsystem->UpdateEnvelopeFollowerParams(AttackTimeMsec, ReleaseTimeMsec, AnalysisWindowMsec);
}

// Called when the game starts
void UAudioGameplayInputListener::BeginPlay()
{
	Super::BeginPlay();

	const auto GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	AudioInputSubsystem = GameInstance->GetSubsystem<UAudioInputSubsystem>();

	UpdateEnvelopeFollowerParams();
}

// Called every frame
void UAudioGameplayInputListener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float Amplitude = AudioInputSubsystem->Poll();
	if (Amplitude > 0.f)
	{
		OnAudioGameplayInputDelegate.Broadcast(Amplitude);
	}
}

