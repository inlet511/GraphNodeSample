#pragma once
#include "SGraphPin.h"


class SMyPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SMyPin){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

	TSharedPtr<SGraphNode> GetGraphNode() { return OwnerNodePtr.Pin(); }
protected:
};