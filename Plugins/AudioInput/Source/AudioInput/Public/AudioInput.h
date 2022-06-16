// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AudioInputSubsystem.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAudioInput, Log, All)

class FAudioInputModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
