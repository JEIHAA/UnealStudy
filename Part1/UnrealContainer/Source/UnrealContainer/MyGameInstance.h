// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// 별도의 헤더 파일을 추가하지 않고 바로 구조체 추가
// 따로 헤더 파일을 추가해 구조체를 만들 수도 있음

USTRUCT()
struct FStudentData 
{
	GENERATED_BODY() //	public으로 적용됨
	
	FStudentData() // 생성자
	{
		Name = TEXT("홍길동");
		Order = -1;
	}

	FStudentData(FString InName, int32 InOrder) : Name(InName), Order(InOrder) {}
	// New API를 사용해 생성될 일이 없기 때문에 언리얼 오브젝트와 달리
	// 인자를 가진 생성자를 만들어 자유롭게 사용하면 됨

	// 커스텀 구조체(FStudentData)에 대한 GetTypeHash 함수가 지정되어 있지 않아서 에러 발생
	// == 연산자 지정
	bool operator==(const FStudentData& InOther) const
	{
		// Order가 같으면 같은 것으로 간주
		return Order == InOther.Order;
	}

	// GetTypeHash 지정
	// 전역 함수로 선언할 수도 있고
	// friend 함수를 사용해 안쪽에 선언하면 더 깔끔
	// 해시 값은 uint32로 반환
	// 인자로 레퍼런스
	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		// 가지고 있는 integer Order 값을 해시로 지정해 리턴
		return GetTypeHash(InStudentData.Order);
	}


	// UPROPERTY를 넣을 때는 
	// 리플렉션을 사용하거나 블루프린트와 호환시키는 등
	// 명확한 이유가 있어야함.
	// 다만 언리얼 오브젝트 포인터를 멤버 변수로 가질때는
	// UPROPERTY를 반드시 넣어줘야함.	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;

};

/**
 * 
 */
UCLASS()
class UNREALCONTAINER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void  Init() override;

private:
	// 값타입. 메모리 관리 필요없음. 굳이 UPROPERTY 쓸 필요 X
	TArray<FStudentData> StudentsData; 
	
	// 언리얼 오브젝트 헤더에서 
	// 언리얼 오브젝트 포인터를 선언할 때는 TObjectPtr 사용
	// 전방 선언으로 의존성 최소화
	// TArray에 내부적으로 포인터를 사용하게 될 때는 
	// 자동으로 메모리를 관리할 수 있도록 UPROPERTY 필수
	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	// Key나 Value에 언리얼 오브젝트 포인터가 들어가게 되면 반드시 UPROPERTY를 선언
	TMap<int32, FString> StudentsMap;
};
