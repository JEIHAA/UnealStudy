// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LessonInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULessonInterface : public UInterface
{
	GENERATED_BODY()
};	

/**
 * 
 */
class UNREALCOMPOSITION_API ILessonInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//가상 함수로 만들어야 상속받는 클래스들이 구현
	//abstract 가상함수로 선언하면 해당 인터페이스를 상속받는 클래스들은 반드시 구현해야함
	virtual void DoLesson() 
	{
		UE_LOG(LogTemp, Log, TEXT("수업에 입장합니다."));
	};
	//abstract 상태로 두는 것이 좋지만 인터페이스 내부에 구현할 수 있다.
	//더 이상 추상 클래스가 아니기 때문에 하위 클래스에서 구현하지 않아도 컴파일 에러가 발생하지 않음
	//언리얼 내부에서도 이런 것들을 활용한 코드가 종종 있음
};
