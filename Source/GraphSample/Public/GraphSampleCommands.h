// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GraphSampleStyle.h"

class FGraphSampleCommands : public TCommands<FGraphSampleCommands>
{
public:

	FGraphSampleCommands()
		: TCommands<FGraphSampleCommands>(TEXT("GraphSample"), NSLOCTEXT("Contexts", "GraphSample", "GraphSample Plugin"), NAME_None, FGraphSampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};