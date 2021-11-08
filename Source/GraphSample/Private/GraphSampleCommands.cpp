// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GraphSampleCommands.h"

#define LOCTEXT_NAMESPACE "FGraphSampleModule"

void FGraphSampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "GraphSample", "Bring up GraphSample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
