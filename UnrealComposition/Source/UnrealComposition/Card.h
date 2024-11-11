// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

/*
//열거형 앞에는 E붙여서 구분
//열거형 기본타입은 8bit, 바이트 형태를 해주는 것이 일반적
//언리얼C++보다는 일반 C++방식
enum class ECardType : uint8
{
	Student = 1,
	Teacher,
	Staff,
	Invalid //기본값
};
*/

//언리얼 C++ 방식
UENUM() //언리얼이 관리하게 함
enum class ECardType : uint8
{
	//언리얼 C++은 UMETA 매크로로 메타 정보를 넣어놓고 코드에서 사용할 수 있음
	Student = 1 UMETA(DisplayName = "For Student"),
	Teacher UMETA(DisplayName = "For Teacher"),
	Staff UMETA(DisplayName = "For Staff"),
	Invalid
};

/**
 *
 */
UCLASS()
class UNREALCOMPOSITION_API UCard : public UObject
{
	GENERATED_BODY()

public:
	UCard();

	//getter,setter
	ECardType GetCardType() const { return CardType; }
	void SetCardType(ECardType InCardType) { CardType = InCardType; }

private:

	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	uint32 Id;

};
