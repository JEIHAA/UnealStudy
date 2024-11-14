// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

// 일반 C++ 클래스는 접두사 F 붙여주기
// 일반 C++ 객체가 언리얼 오브젝트를 지키려면
// 가비지 컬렉터에 언리얼 오브젝트를 관리하겠다고 알려야함
// FGCObject 클래스를 상속받아야함.
class UNREALMEMORY_API FStudentManager : public FGCObject
{
public:

	// FGCObject 클래스의 추상 함수 2가지를 구현해야함
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override 
	{
		return TEXT("FStudentManager"); // 고유한 클래스 이름을 반환해주면 됨
	}


	// 생성자에서 인수로 들어온 InStudent가 SafeStudent에 들어가게 함
	FStudentManager(class UStudent* InStudent) : SafeStudent(InStudent) {}

	// getter
	const class UStudent* GetStudent() const { return SafeStudent; }

private:
	// 일반 C++ 클래스이기 때문에 class UStudent*로 선언
	// 기본 값 null
	class UStudent* SafeStudent = nullptr;
};
