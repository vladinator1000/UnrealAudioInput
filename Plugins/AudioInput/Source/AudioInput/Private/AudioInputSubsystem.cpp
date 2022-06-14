// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioInputSubsystem.h"
#include "SignalProcessing/Public/DSP/EnvelopeFollower.h"

void UAudioInputSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{	
	Audio::FAudioCaptureDeviceParams Params;
	Params.DeviceIndex = 0;
	
	EnvelopeFollowerInitParams.AttackTimeMsec = 0.5f;
	EnvelopeFollowerInitParams.ReleaseTimeMsec = 1.0f;
	EnvelopeFollowerInitParams.AnalysisWindowMsec = 2.0f;
	EnvelopeFollower = Audio::FEnvelopeFollower(EnvelopeFollowerInitParams);
	
	const FOnSoundDelegate& Delegate = OnSoundDelegate;

	Audio::FOnCaptureFunction OnCapture = [this, Delegate](const float* AudioData, int32 NumFrames, int32 NumChannels, int32 SampleRate, double StreamTime, bool bOverFlow)
	{
		EnvelopeFollower.ProcessAudio(AudioData, NumFrames);
		const TArray<float>& EnvelopeValues = EnvelopeFollower.GetEnvelopeValues();

		for (const float Value : EnvelopeValues)
		{
			const float Amplitude = FMath::Abs(Value);
			if (Amplitude > FilterThreshold)
			{
				FAudioThread::RunCommandOnGameThread([Delegate, Amplitude]()
				{
					Delegate.Broadcast(Amplitude);
				});
			}
		}
	};

	bool IsOpen = AudioCapture.OpenCaptureStream(Params, MoveTemp(OnCapture), AudioBufferSize);
	
	if (IsOpen)
	{
		AudioCapture.StartStream();
		UE_LOG(LogAudioInput, Warning, TEXT("Audio capture stream Opened."))
	} else {
		UE_LOG(LogAudioInput, Warning, TEXT("Could not open audio capture stream."))
	}
	
}

void UAudioInputSubsystem::Deinitialize()
{	
	AudioCapture.CloseStream();
	UE_LOG(LogAudioInput, Warning, TEXT("Audio capture stream Closed"))
}
