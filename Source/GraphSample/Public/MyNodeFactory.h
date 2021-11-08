#pragma once 
#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class FMyNodeFactory : public FGraphPanelNodeFactory
{
public:
	FMyNodeFactory();

	virtual TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* Node) const;

};