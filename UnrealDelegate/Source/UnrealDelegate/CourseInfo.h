// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, const FString&, const FString&);
//보통 앞에 F를 붙임, 이벤트가 발생했다는 뜻으로 On, 학사 정보가 변경됐다는 뜻으로 Changed
//언리얼 소스코드를 보면 보통 델리게이트에 Signature라는 접미사를 붙임
//인자 2개

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UCourseInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UCourseInfo();

	//델리게이트 클래스 정보를 멤버 변수처럼 등록
	FCourseInfoOnChangedSignature OnChanged;

	//외부에서 학사정보를 변경할 때 사용할 함수
	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	// 메모리를 동적관리할 일은 없기 때문에
	// 추후 블루프린트나 리플렉션을 통해 참조할 일이 없다면
	// UPROPERTY를 넣지 않아도 상관없음
	FString Contents;
	
};
