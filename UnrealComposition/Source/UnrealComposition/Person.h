// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCOMPOSITION_API UPerson : public UObject
{
	GENERATED_BODY()
public:
	UPerson();

	//FORCEINLINE: 가능한 인라인 함수가 되도록 함. 100%는 아님
	FORCEINLINE FString& GetName() { return Name; }
	FORCEINLINE void SetName(const FString InName) { Name = InName; }

protected:
	UPROPERTY()
	FString Name;
	
};
