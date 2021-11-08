#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "MyDrawingPolicy.h"
#include "MySchema.generated.h"

USTRUCT()
struct FMySchemaAction : public FEdGraphSchemaAction
{
	GENERATED_BODY();
public:
	FMySchemaAction()
	{

	}

	FMySchemaAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, FText InKeywords = FText(), int32 InSectionID = 0)
		: FEdGraphSchemaAction(InNodeCategory,InMenuDesc,InToolTip,InGrouping,InKeywords,InSectionID)
	{

	}

	/** Execute this action, given the graph and schema, and possibly a pin that we were dragged from. Returns a node that was created by this action (if any). */
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true);

	class UMyNode* NodeHelloWorld;
};

UCLASS(MinimalAPI)
class UMySchema :public UEdGraphSchema
{
	GENERATED_BODY()
public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT("Not implemented by this schema"));
	}
	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override
	{ 
		return new FMyDrawingPolicy(InBackLayerID,InFrontLayerID,InZoomFactor,InClippingRect, InDrawElements,InGraphObj);
	}


};