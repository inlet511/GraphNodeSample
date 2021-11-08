#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "MyNode.generated.h"


UCLASS()
class UMyNode : public UEdGraphNode
{
	GENERATED_BODY()
public:
	UMyNode();

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};