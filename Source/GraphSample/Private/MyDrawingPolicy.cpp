#include "MyDrawingPolicy.h"
#include "DrawElements.h"

static const FLinearColor DefaultWiringColor(1.0f, 0.0f, 0.0f);

FMyDrawingPolicy::FMyDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj)
	:FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor,InClippingRect,InDrawElements),
	EdGraphObj(InGraphObj)
{

}

void FMyDrawingPolicy::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, /*inout*/ FConnectionParams& Params)
{
	Params.WireThickness = 5.5f;
	Params.WireColor = DefaultWiringColor;

	if (HoveredPins.Num() > 0)
	{
		ApplyHoverDeemphasis(OutputPin, InputPin, Params.WireThickness, Params.WireColor);
	}

}

void FMyDrawingPolicy::DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params)
{
	const FVector2D Delta = End - Start;
	const FVector2D Delta_Normal = Delta.GetSafeNormal();

	FSlateDrawElement::MakeDrawSpaceSpline(
		DrawElementsList,
		LayerId,
		Start,Delta_Normal,
		End, Delta_Normal,
		Params.WireThickness
	);
}

