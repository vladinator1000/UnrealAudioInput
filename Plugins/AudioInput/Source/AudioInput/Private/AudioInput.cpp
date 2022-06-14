// Copyright Epic Games, Inc. All Rights Reserved.

#include "AudioInput.h"

DEFINE_LOG_CATEGORY(LogAudioInput);

#define LOCTEXT_NAMESPACE "FAudioInputModule"


void FAudioInputModule::StartupModule()
{
	UE_LOG(LogAudioInput, Warning, TEXT("Audio capture module started."))
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAudioInputModule::ShutdownModule()
{
	UE_LOG(LogAudioInput, Warning, TEXT("Audio capture module shutdown."))
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAudioInputModule, AudioInput)