// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

UMyGameInstance::UMyGameInstance() //생성자
{
	SchoolName = TEXT("기본학교"); //CDO 기본값 설정
}

void UMyGameInstance::Init()
{
	Super::Init(); //원래 로직 실행

	UE_LOG(LogTemp, Log, TEXT("======================================"));
	//UPerson 부모 객체 포인터의 배열
	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };
	for (const auto Person : Persons) //포인터니까 그냥 auto로
	{
		UE_LOG(LogTemp, Log, TEXT("구성원 이름: %s"), *Person->GetName());
	}
	UE_LOG(LogTemp, Log, TEXT("======================================"));


	//구성원이 가지고 있는 모든 DoLesson 함수를 호출할 것
	//그 중 LessonInterface를 상속받은 클래스만 찾아야함
	//casting을 유용하게 사용할 수 있다
	for (const auto Person : Persons)
	{
		//언리얼은 형변환을 안전하게 할 수 있음
		//형변환에 실패하면 null을 반환해 구현했는지 안했는지 알 수 있음
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다."), *Person->GetName());
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다."), *Person->GetName());
		}
	}
	UE_LOG(LogTemp, Log, TEXT("======================================"));
}