#include "SMyPin.h"
#include "GraphSampleStyle.h"
#include "SGraphNode.h"
#include "SGraphPanel.h"

void SMyPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Hand);

	IsEditable = true;

	GraphPinObj = InPin;
	check(GraphPinObj != NULL);

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	SBorder::Construct(
		SBorder::FArguments()
		//.BorderImage_Lambda([&]()
		//	{
		//		const FVector2D IconSize(64.f, 64.f);
		//		return FGraphSampleStyle::GetImageBrush(TEXT("ButtonIcon_40x"), IconSize);
		//	})

		.BorderBackgroundColor_Lambda([&]()
			{
				FSlateColor SlateColor(FLinearColor(1.f, 1.f, 1.f));
				return SlateColor;
			})

		.OnMouseButtonDown_Lambda([&](const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent)
			{ 
				bIsMovingLinks = false;

				if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
				{
					if (IsEditingEnabled())
					{
						TSharedPtr<SGraphNode> OwnerNodePinned = OwnerNodePtr.Pin();
						if (!GraphPinObj->bNotConnectable)
						{
							if (MouseEvent.IsAltDown())
							{
								const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
								Schema->BreakPinLinks(*GraphPinObj, true);

								return FReply::Handled();
							}

							if (MouseEvent.IsControlDown() && (GraphPinObj->LinkedTo.Num() > 0))
							{
								TSet<TSharedRef<SWidget>> AllPins;
								OwnerNodePinned->GetOwnerPanel()->GetAllPins(AllPins);
								TMap<FGraphPinHandle, TSharedRef<SGraphPin>> PinToPinWidgetMap;

								for (const TSharedRef<SWidget>& SomePinWidget : AllPins)
								{
									const SGraphPin& PinWidget = static_cast<const SGraphPin&>(SomePinWidget.Get());
									UEdGraphPin* GraphPin = PinWidget.GetPinObj();
									if (GraphPin->LinkedTo.Num() > 0)
									{
										PinToPinWidgetMap.Add(FGraphPinHandle(GraphPin), StaticCastSharedRef<SGraphPin>(SomePinWidget));
									}
								}

								struct FLinkedToPinInfo
								{
									FString PinName;
									TWeakObjectPtr<UEdGraphNode> OwnerNodePtr;
								};

								TArray<FLinkedToPinInfo> LinkedToPinInfoArray;

								for(UEdGraphPin* Pin : GetPinObj()->LinkedTo)
								{
									if(auto PinWidget = PinToPinWidgetMap.Find(Pin))
									{
										FLinkedToPinInfo PinInfo;
										PinInfo.PinName = (*PinWidget)->GetPinObj()->PinName.ToString();
										PinInfo.OwnerNodePtr = StaticCastSharedRef<SMyPin>(*PinWidget)->GetGraphNode()->GetNodeObj();
										LinkedToPinInfoArray.Add(MoveTemp(PinInfo));
									}
								}

								TArray<TSharedRef<SGraphPin>> PinArray;
								for(FLinkedToPinInfo PinInfo : LinkedToPinInfoArray)
								{
									for(UEdGraphPin* Pin: PinInfo.OwnerNodePtr.Get()->Pins)
									{
										if(Pin->PinName.ToString() == PinInfo.PinName)
										{
											if(TSharedRef<SGraphPin>* pWidget = PinToPinWidgetMap.Find(FGraphPinHandle(Pin)))
											{
												PinArray.Add(*pWidget);
											}
										}
									}
								}

								TSharedPtr<FDragDropOperation> DragEvent;
								if(PinArray.Num()>0)
								{
									DragEvent = SpawnPinDragEvent(OwnerNodePinned->GetOwnerPanel().ToSharedRef(), PinArray);
								}

								const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
								Schema->BreakPinLinks(*GraphPinObj, true);

								if(DragEvent.IsValid())
								{
									bIsMovingLinks = true;
									return FReply::Handled().BeginDragDrop(DragEvent.ToSharedRef());
								}
								else
								{
									return FReply::Handled();
								}

							}

							if (!ensure(OwnerNodePinned.IsValid()))
							{
								return FReply::Unhandled();
							}
							else  
							{
								TArray<TSharedRef<SGraphPin>> PinArray;
								PinArray.Add(SharedThis(this));
								TSharedPtr<FDragDropOperation> DragEvent = SpawnPinDragEvent(OwnerNodePinned->GetOwnerPanel().ToSharedRef(), PinArray);
								return FReply::Handled().BeginDragDrop(DragEvent.ToSharedRef());
							}
						}
					}
				}

				return FReply::Handled();
			})
	);
}

