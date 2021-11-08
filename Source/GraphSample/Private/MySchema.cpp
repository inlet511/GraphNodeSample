#include "MySchema.h"
#include "ScopedTransaction.h"
#include "EdGraph/EdGraph.h"
#include "MyNode.h"
#include "MultiBoxBuilder.h"
#include "SImage.h"
#include "SlateIcon.h"

#define LOCTEXT_NAMESPACE "GraphSampleSchema"

UEdGraphNode* FMySchemaAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	UEdGraphNode* UEResultNode = nullptr;
	if (NodeHelloWorld != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("FF", "Hello:NewNode"));
		ParentGraph->Modify();

		if (FromPin != nullptr)
		{
			FromPin->Modify();
		}

		NodeHelloWorld->Rename(nullptr, ParentGraph);
		ParentGraph->AddNode(NodeHelloWorld, true, bSelectNewNode);
		NodeHelloWorld->CreateNewGuid();
		NodeHelloWorld->PostPlacedNewNode();
		NodeHelloWorld->AllocateDefaultPins();
		NodeHelloWorld->AutowireNewNode(FromPin);

		NodeHelloWorld->NodePosX = Location.X;
		NodeHelloWorld->NodePosY = Location.Y;

		NodeHelloWorld->SetFlags(RF_Transactional);

		UEResultNode = NodeHelloWorld;
	}
	return UEResultNode;
}

void UMySchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FMySchemaAction> NewNodeAction(
		new FMySchemaAction(
			LOCTEXT("A", "Graph Node"),
			LOCTEXT("Desc", "MyTest Description"),
			LOCTEXT("NewGraphText", " Add a Node"),
			0));

	NewNodeAction->NodeHelloWorld = NewObject<UMyNode>(ContextMenuBuilder.OwnerOfTemporaries);
	ContextMenuBuilder.AddAction(NewNodeAction);
}



void UMySchema::GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const
{
	MenuBuilder->BeginSection(TEXT("Hall"));
	{
		MenuBuilder->AddWidget(
			SNew(SImage),
			LOCTEXT("Image_description", "just an image")
		);
		MenuBuilder->AddEditableText(
			LOCTEXT("label", "Value"),
			LOCTEXT("tip_text", "tips"),
			FSlateIcon(),
			LOCTEXT("default_text", "10000")
		);
	}
	MenuBuilder->EndSection();
}

#undef LOCTEXT_NAMESPACE