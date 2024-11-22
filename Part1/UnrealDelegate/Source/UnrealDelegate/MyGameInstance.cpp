// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	// CDO 안에서 생성할 수도 있지만
	// 외부에서 필요할 때만 생성하도록 함
	// 원래는 당연히 필요한 것이라 CDO에 선언하는 것이 맞음
	CourseInfo = NewObject<UCourseInfo>(this);
	// 생성한 객체는 클래스 멤버 변수에 들어가서 관리받음
	// C++에서 포인터로 참조되기 때문에 명시적으로 삭제하지 않는 한 메모리에 계속 있음
	// 이때 MyGameInstance는 CourseInfo를 포함해야하기 때문에
	// Outer를 MyGameInstance로 선언해주면
	// CourseInfo가 MyGameInstance의 서브 오브젝트가 되는 컴포지션 관계가 됨
	// MyGameInstance가 존재하는 동안 CourseInfo가 메모리에 안전하게 남아 있음
	// MyGameInstance가 삭제되면 CourseInfo도 삭제됨

	UE_LOG(LogTemp, Log, TEXT("======================================"));
	

	// 구문이 실행되면 자동으로 소멸되기 때문에 굳이 Outer를 설정해줄 필요 없음
	// 장기 유지X 단기적 사용
	// NewObject에서 명시적으로 Outer를 지정하지 않으면 자동으로 가비지 컬렉터에 의해 관리됨
	// Outer가 없는 객체는 명시적으로 삭제하거나 모든 참조가 해제되었을 때 자동으로 소멸
	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("학생1"));
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	// AddUObject: 클래스 인스턴스를 지정하고 멤버 함수를 직접 묶을 수 있음
	// AddUObject(인스턴스, 인스턴스가 가진 클래스 멤버 함수를 레퍼런스로 지정)
	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);
	
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("======================================"));
}
