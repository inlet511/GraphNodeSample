// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GraphSample.h"
#include "GraphSampleStyle.h"
#include "GraphSampleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EdGraph/EdGraph.h"
#include "GraphEditor.h"
#include "EdGraph/EdGraphSchema.h"
#include "MySchema.h"
#include "MyNodeFactory.h"
#include "EdGraphUtilities.h"

static const FName GraphSampleTabName("GraphSample");

#define LOCTEXT_NAMESPACE "FGraphSampleModule"

void FGraphSampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	GraphObject = nullptr;

	FGraphSampleStyle::Initialize();
	FGraphSampleStyle::ReloadTextures();

	FGraphSampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGraphSampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FGraphSampleModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FGraphSampleModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FGraphSampleModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GraphSampleTabName, FOnSpawnTab::CreateRaw(this, &FGraphSampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FGraphSampleTabTitle", "GraphSample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShareable(new FMyNodeFactory));
}

void FGraphSampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FGraphSampleStyle::Shutdown();

	FGraphSampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GraphSampleTabName);

}

TSharedRef<SDockTab> FGraphSampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FGraphSampleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("GraphSample.cpp"))
		);


	if (GraphObject != nullptr)
	{
		//GraphObject->ConditionalBeginDestroy();
		GraphObject = nullptr;
	}
	GraphObject = NewObject<UEdGraph>();
	GraphObject->Schema = UMySchema::StaticClass();
	GraphObject->AddToRoot();

	GraphEditorSlate = SNew(SGraphEditor).GraphToEdit(GraphObject);
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				GraphEditorSlate.ToSharedRef()
			]
		];
}

void FGraphSampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(GraphSampleTabName);
}

void FGraphSampleModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FGraphSampleCommands::Get().OpenPluginWindow);
}

void FGraphSampleModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FGraphSampleCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGraphSampleModule, GraphSample)