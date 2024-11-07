// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance() //생성자
{
	SchoolName = TEXT("기본학교"); //CDO 기본값 설정
}

void UMyGameInstance::Init()
{
	Super::Init(); //원래 로직 실행

	UE_LOG(LogTemp, Log, TEXT("========================="));
	UClass* ClassRuntime = GetClass();
	UClass* ClassCompile = UMyGameInstance::StaticClass();
	check(ClassRuntime == ClassCompile);


	//한글 인코딩 UTF-8 설정
	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 : %s"), *ClassRuntime->GetName());
	
	SchoolName = TEXT("청강문화산업대학교"); //개별적으로 생성된 것
	//객체의 값을 변경해도 기본 값은 없어지지 않음
	//ClassDefaultObject 템플릿 객체에 저장되어 있음

	UE_LOG(LogTemp, Log, TEXT("학교 이름 : %s"), *SchoolName); //청강문화산업대학교
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);
	//클래스 정보에서 바로 형변환이 되어 디폴트 오브젝트를 가져올 수 있음
	UE_LOG(LogTemp, Log, TEXT("========================="));
}