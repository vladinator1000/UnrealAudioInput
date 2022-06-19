// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioInputSubsystem.h"
#include "SignalProcessing/Public/DSP/EnvelopeFollower.h"

void UAudioInputSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Audio::FAudioCaptureDeviceParams Params;
	Params.DeviceIndex = 0;
	
	EnvelopeFollowerInitParams.AttackTimeMsec = AttackTimeMsec;
	EnvelopeFollowerInitParams.ReleaseTimeMsec = ReleaseTimeMsec;
	EnvelopeFollowerInitParams.AnalysisWindowMsec = AnalysisWindowMsec;
	EnvelopeFollower = Audio::FEnvelopeFollower(EnvelopeFollowerInitParams);

	Audio::FOnCaptureFunction OnCapture = [this](const float* AudioData, const int32 NumFrames, int32 NumChannels, int32 SampleRate, double StreamTime, bool bOverFlow)
	{
		EnvelopeFollower.ProcessAudio(AudioData, NumFrames);
		const TArray<float>& EnvelopeValues = EnvelopeFollower.GetEnvelopeValues();

		EnvelopeValue = 0;

		for (const float Value : EnvelopeValues)
		{
			const float Amplitude = FMath::Abs(Value);
			if (Amplitude > FilterThreshold)
			{
				EnvelopeValue = Amplitude;
			}
		}
	};
	
	bool IsOpen = AudioCapture.OpenCaptureStream(Params, MoveTemp(OnCapture), AudioBufferSize);
	
	if (IsOpen)
	{
		AudioCapture.StartStream();
		UE_LOG(LogAudioInput, Log, TEXT("Audio capture stream Opened."))
	} else {
		UE_LOG(LogAudioInput, Error, TEXT("Could not open audio capture stream."))
	}
	
}

void UAudioInputSubsystem::Deinitialize()
{	
	AudioCapture.CloseStream();
	Super::Deinitialize();
}

float UAudioInputSubsystem::Poll() const
{
	return EnvelopeValue;
}

void UAudioInputSubsystem::UpdateEnvelopeFollowerParams(float AttackMs, float ReleaseMs, float AnalysisWindowMs)
{
	if (AudioCapture.IsStreamOpen())
	{
		AudioCapture.StopStream();
	}

	Audio::FEnvelopeFollowerInitParams Params;
	Params.AttackTimeMsec = AttackMs;
	Params.ReleaseTimeMsec = ReleaseMs;
	Params.AnalysisWindowMsec = AnalysisWindowMs;
	
	EnvelopeFollower.Init(Params);

	AudioCapture.StartStream();
}

