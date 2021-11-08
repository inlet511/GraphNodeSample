#include "MyGraphPanelNodeFactory.h"
#include "MySchema.h"
#include "MyNode.h"
#include "SMyPin.h"
#include "MyDrawingPolicy.h"
#include "SMyGraphNode.h"

FMyGraphPanelNodeFactory::FMyGraphPanelNodeFactory()
{

}

TSharedPtr<SGraphNode> FMyGraphPanelNodeFactory::CreateNode(class UEdGraphNode* Node) const
{
	if (UMyNode* MarkerNode = Cast<UMyNode>(Node))
	{
		return SNew(SMyGraphNode, MarkerNode);
	}

	return nullptr;
}


TSharedPtr<SGraphPin> FMyGraphPanelPinFactory::CreatePin(class UEdGraphPin* Pin) const
{
	
	//if(const UMySchema* MarkerSchema = Cast<UMySchema>(Pin->GetSchema())) // 改变整个蓝图的所有pin
	if (UMyNode* MarkerNode = Cast<UMyNode>(Pin->GetOuter()))
	{
		return SNew(SMyPin, Pin);
	}
	return nullptr;
}

class FConnectionDrawingPolicy* FMyGraphPanelConnectionFactory::CreateConnectionPolicy(const class UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const class FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
	if(Schema->IsA(UMySchema::StaticClass()))
	{
		return new FMyDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj);

	}
	return nullptr;
}

