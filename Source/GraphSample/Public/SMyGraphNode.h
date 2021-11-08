#pragma once

#include "SGraphNode.h"
#include "MyNode.h"

class SMyGraphNode :public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SMyGraphNode)
	{

	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UMyNode* MarkerNode);

	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	
protected:
	TSharedPtr<class SBox> PinBox;
};