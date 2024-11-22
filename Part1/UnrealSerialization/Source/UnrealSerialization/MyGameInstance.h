// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
// 비동기 로딩
#include "MyGameInstance.generated.h"

struct FStudentData
{
	FStudentData() {}
	FStudentData(int32 InOrder, const FString& InName) : Order(InOrder), Name (InName) {}

	friend FArchive& operator <<(FArchive& Ar, FStudentData& InStudentData)
	{
		Ar << InStudentData.Order;
		Ar << InStudentData.Name;
		return Ar;
	}

	int32 Order = -1;
	FString Name = TEXT("홍길동");
};

/**
 * 
 */
UCLASS()
class UNREALSERIALIZATION_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

	// 패키지 저장함수
	void SaveStudentPackage() const;
	// 패키지 로드함수
	void LoadStudentPackage() const;

	// 패키지를 로드하지 않고 경로를 사용해 애셋 로딩 함수
	void LoadStudentObject() const;

private:
	UPROPERTY()
	// 데이터를 저장할 소스 오브젝트
	TObjectPtr<class UStudent> StudentSrc;

	// 패키지를 사용하기 위해서는
	// 패키지와 패키지가 담고 있는 대표 에셋을 설정해주어야함
	// 패키지와 패키지가 담고 있는 대표 에셋의 이름 지정
	static const FString PackageName;
	static const FString AssetName;

	// FStreamableManager는 포인터가 아니고 그냥 선언해주는 것이라 헤더 추가해야함
	FStreamableManager StreamableManager;
	// 스트리밍된 애셋을 관리할 핸들
	TSharedPtr<FStreamableHandle> Handle;
};
