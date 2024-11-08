// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
//현재 구현하고자 하는 언리얼 오브젝트의 헤더가 반드시 가장 위에 있어야함
#include "Student.h"
#include "Teacher.h"


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

	UStudent* Student = NewObject<UStudent>(); //언리얼 오브젝트이기 때문에 new가 아니라 NewObject로 생성
	UTeacher* Teacher = NewObject<UTeacher>();

	//구현해둔 getter, setter를 이용해 값을 가져오는 방법
	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 %s"), *Student->GetName());

	//리플렉션을 활용해 값을 가져오는 방법
	FString CurrentTeacherName;
	FString NewTeacherName(TEXT("이득우"));
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name")); //클래스의 속성
	if (NameProp) //값이 있다면. 없다면 null로 진입하지 않음
	{
		//GetValue_InContainer를 사용해 이 속성에 대해서 지정한 인스턴스의 값을 빼올 수 있음
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName); //Teacher가 가지고 있는 객체의 속성 중 이름 속성값을 가져와야함.
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름 %s"), *CurrentTeacherName);

		//SetValue_InContainer를 사용해 이 속성에 대해서 지정한 인스턴스의 값을 변경할 수 있음
		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름 %s"), *Teacher->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("========================="));

	//함수실행
	Student->DoLesson();

	//리플렉션을 활용해 함수 실행
	UFUNCTION()
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		//함수를 찾았다면 ProcessEvent를 사용해 함수포인터를 넘겨주고 인자가 없기 때문에 null을 넣어준다
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}
}