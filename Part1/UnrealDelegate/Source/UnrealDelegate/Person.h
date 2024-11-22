// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UPerson : public UObject
{
	GENERATED_BODY()
public:
	UPerson();

	//FORCEINLINE: 가능한 인라인 함수가 되도록 함. 100%는 아님
	FORCEINLINE const FString& GetName() const { return Name; }
	//getter를 만들 때는 const를 붙여주는 것이 좋음
	//레퍼런스를 반환할 때는 받은 쪽에서는 값을 변경할 수 있기 때문에
	//const로 지시할 때 반환값에도 const를 붙여주어야 올바르게 동작함
	FORCEINLINE void SetName(const FString InName) { Name = InName; }

	FORCEINLINE class UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(class UCard* InCard) { Card = InCard; }

protected:
	UPROPERTY()
	FString Name;


	/*
	//UCard* Card; 이런 식으로 선언할 때는 Card에 대한 헤더를 선언해 포함시켜주어야함
	//컴포지션 관계에 있을 때는 전방 선언, 헤더를 포함하지 않아도 됨
	//보틍 오브젝트는 포인터로 관리하기 때문에 정확한 위치는 알 수 없지만
	//포인터 크기를 가지기 때문에 전방 선언을 통해 의존성을 최대한 줄일 수 있음
	UPROPERTY()
	class UCard* Card;
	//위의 방식은 언리얼4까지 정석이었으나 언리얼5부터는 방식이 바뀜
	*/

	//언리얼5부터는 포인터를 빼고 TObjectPrt이라는 템플릿 클래스로 감싸서 선언
	//전방 선언은 기존대로
	UPROPERTY()
	TObjectPtr<class UCard> Card;
	
};
