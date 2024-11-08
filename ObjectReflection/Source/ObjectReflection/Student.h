// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.h" 

#include "Student.generated.h"
//언리얼 오브젝트를 선언할 때는 반드시 .generated.h가 가장 밑에 include되어야함

/**
 * 
 */
UCLASS()
class OBJECTREFLECTION_API UStudent : public UPerson
{
	GENERATED_BODY()
public:
	UStudent();

	virtual void DoLesson() override;

private:
	UPROPERTY()
	int32 Id;
};
