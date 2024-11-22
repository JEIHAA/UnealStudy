// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSERIALIZATION_API UStudent : public UObject
{
	GENERATED_BODY()
	
public:
	UStudent();

	int32 GetOrder() const { return Order; }
	void SetOrder(int32 InOrder) { Order = InOrder; }

	const FString& GetName() const { return Name; }
	void SetName(const FString& InName) { Name = InName; }

	// 언리얼 오브젝트는 안에 직렬화 함수가 
	// 이미 구현되어 있어 오버라이드해서 쓰면 됨
	virtual void Serialize(FArchive& Ar) override;

private:
	UPROPERTY()
	int32 Order;

	UPROPERTY()
	FString Name;
	
};
