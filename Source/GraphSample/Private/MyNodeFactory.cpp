#include "MyNodeFactory.h"
#include "MyNode.h"
#include "SMyGraphNode.h"

FMyNodeFactory::FMyNodeFactory()
{

}

TSharedPtr<class SGraphNode> FMyNodeFactory::CreateNode(class UEdGraphNode* Node) const
{
	if (UMyNode* MarkerNode = Cast<UMyNode>(Node))
	{
		return SNew(SMyGraphNode, MarkerNode);
	}

	return nullptr;
}

