#include "SMyGraphNode.h"
#include "SBoxPanel.h"
#include "SBox.h"
#include "GraphSampleStyle.h"
#include "SMyPin.h"
#include "SGraphPinBool.h"
#include "SGraphPinColor.h"
#include "Private/KismetPins/SGraphPinEnum.h"
#include "SGraphPinExec.h"
#include "SGraphPinNameList.h"
#include "SGraphPinObject.h"
#include "SGraphPinString.h"
#include "SGraphPinVector2D.h"
#include "SGraphPinVector4.h"
#include "SGraphPinInteger.h"
#include "MyGraphPanelNodeFactory.h"

void SMyGraphNode::Construct(const FArguments& InArgs, UMyNode* MarkerNode)
{
	GraphNode = MarkerNode;
	this->SetCursor(EMouseCursor::GrabHand);
	this->UpdateGraphNode();
}

void SMyGraphNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	const FSlateBrush* MyNodeIcon = FEditorStyle::GetBrush(TEXT("Graph.StateNode.Icon"));

	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(PinBox,SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderBackgroundColor_Lambda([&]()
				{
						FSlateColor SlateColor(FLinearColor(1.0f, 1.0f, 1.0f));
						return SlateColor;
				})
				.BorderBackgroundColor(FLinearColor(1.0f,0.0f,0.0f))
				//.BorderImage_Lambda([&]()
				//{
				//		const FVector2D IconSize(64.f, 64.f);
				//		return FGraphSampleStyle::GetImageBrush(TEXT("ButtonIcon_40x"), IconSize);
				//})
					[
						SNew(SHorizontalBox)

						+SHorizontalBox::Slot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.AutoWidth()
						[
							SAssignNew(LeftNodeBox, SVerticalBox)
						]

						+ SHorizontalBox::Slot()
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Fill)
						.FillWidth(1.0f)
						[
							SAssignNew(RightNodeBox, SVerticalBox)
						]

					]
			]
		];

	PinBox->SetWidthOverride(500.0f);
	PinBox->SetHeightOverride(400.0f);

	CreatePinWidgets();
}

#define RESET_PIN(SMyGraphPinType,GraphPinObject,...) \
	NewPin = SNew(SMyGraphPinType, GraphPinObject, __VA_ARGS__); \
	NewPin->SetIsEditable(IsEditable); \
	this->AddPin(NewPin.ToSharedRef());

#define VERSION_SET 1
void SMyGraphNode::CreatePinWidgets()
{
	UMyNode* myNode = CastChecked<UMyNode>(GraphNode);

	if (myNode)
	{
#if VERSION_SET

		for (UEdGraphPin* CurrentPin : myNode->Pins)
		{
			TSharedPtr<SGraphPin> NewPin = FMyGraphPanelPinFactory::CreatePin(CurrentPin);
			NewPin->SetIsEditable(IsEditable);

			this->AddPin(NewPin.ToSharedRef());
		}
#else
		static TArray<TSharedPtr<FName>> InNameList;
		InNameList.Add(MakeShareable(new FName(TEXT("Monster"))));
		InNameList.Add(MakeShareable(new FName(TEXT("Hello"))));
		InNameList.Add(MakeShareable(new FName(TEXT("Wood"))));
		InNameList.Add(MakeShareable(new FName(TEXT("Forest"))));

		TSharedPtr<SGraphPin> NewPin = nullptr;
		
		RESET_PIN(SGraphPinBool, myNode->Pins[0]);
		RESET_PIN(SGraphPinColor, myNode->Pins[1]);
		RESET_PIN(SGraphPinEnum, myNode->Pins[2]);
		RESET_PIN(SGraphPinExec, myNode->Pins[3]);
		RESET_PIN(SGraphPinNameList, myNode->Pins[4], InNameList);
		RESET_PIN(SGraphPinObject, myNode->Pins[5]);
		RESET_PIN(SGraphPinString, myNode->Pins[6]);
		RESET_PIN(SGraphPinVector2D, myNode->Pins[7]);
		RESET_PIN(SGraphPinVector4, myNode->Pins[8]);
		RESET_PIN(SGraphPinInteger, myNode->Pins[9]);

		RESET_PIN(SMyPin, myNode->Pins[10]);
		RESET_PIN(SMyPin, myNode->Pins[11]);
		RESET_PIN(SMyPin, myNode->Pins[12]);
		RESET_PIN(SMyPin, myNode->Pins[13]);
		RESET_PIN(SMyPin, myNode->Pins[14]);

#endif

	}
}

void SMyGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = (PinObj != nullptr) && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility(TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced));
	}

#if VERSION_SET
	PinToAdd->SetDesiredSizeScale(FVector2D(16.f, 16.f));
#endif

	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		LeftNodeBox->AddSlot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Fill)
			.Padding(20.0f,0.0f)
			[
				PinToAdd
			];
		InputPins.Add(PinToAdd);
	} else // Direction == EEdGraphPinDirection::EGPD_Output
	{
		RightNodeBox->AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			.Padding(20.0f,0.0f)
			[
				PinToAdd
			];
		OutputPins.Add(PinToAdd);
	}
}

