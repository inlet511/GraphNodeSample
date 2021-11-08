#include "MyNode.h"


UMyNode::UMyNode()
{

}

void UMyNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "SGraphPinBool", FName(), TEXT("SGraphPinBool"));
	CreatePin(EGPD_Input, "SGraphPinColor", FName(), TEXT("SGraphPinColor"));
	CreatePin(EGPD_Input, "SGraphPinEnum", FName(), TEXT("SGraphPinEnum"));
	CreatePin(EGPD_Input, "SGraphPinExec", FName(), TEXT("SGraphPinExec"));
	CreatePin(EGPD_Input, "SGraphPinNameList", FName(), TEXT("SGraphPinNameList"));
	CreatePin(EGPD_Input, "SGraphPinObject", FName(), TEXT("SGraphPinObject"));
	CreatePin(EGPD_Input, "SGraphPinString", FName(), TEXT("SGraphPinString"));
	CreatePin(EGPD_Input, "SGraphPinVector2D", FName(), TEXT("SGraphPinVector2D"));
	CreatePin(EGPD_Input, "SGraphPinVector4", FName(), TEXT("SGraphPinVector4"));
	CreatePin(EGPD_Input, "SGraphPinInteger", FName(), TEXT("SGraphPinInteger"));

	CreatePin(EGPD_Output, "SGraphPin", FName(), TEXT("SGraphPin"));
	CreatePin(EGPD_Output, "SGraphPin1", FName(), TEXT("SGraphPin"));
	CreatePin(EGPD_Output, "SGraphPin2", FName(), TEXT("SGraphPin"));
	CreatePin(EGPD_Output, "SGraphPin3", FName(), TEXT("SGraphPin"));
	CreatePin(EGPD_Output, "SGraphPin4", FName(), TEXT("SGraphPin"));


}

FText UMyNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("HelloWorld");
}

