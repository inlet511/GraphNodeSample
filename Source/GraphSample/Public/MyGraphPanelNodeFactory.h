#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class FMyGraphPanelNodeFactory :public FGraphPanelNodeFactory
{
public:
	FMyGraphPanelNodeFactory();
	virtual TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* Node) const;
};

class FMyGraphPanelPinFactory : public FGraphPanelPinFactory
{
public: 
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const;
};