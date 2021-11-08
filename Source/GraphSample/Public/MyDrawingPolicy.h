#pragma once

#include "ConnectionDrawingPolicy.h"

class FMyDrawingPolicy : public FConnectionDrawingPolicy
{
public:
	FMyDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj);
	virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, /*inout*/ FConnectionParams& Params) override;
	virtual void DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params) override;

protected:
	UEdGraph* EdGraphObj;
	TMap<UEdGraphNode*, int32> EdNodeWidgetMap;
};