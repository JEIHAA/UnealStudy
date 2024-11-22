// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "StudentManager.h"

// 오브젝트가 유효한지 확인하는 함수
void CheckUObjectIsValid(const UObject* InObject, const FString& InTag)
{
    // 일반적으로 ::InValid 함수를 사용해 오브젝트에 대한 유효성 검사를 함
    // 이번 예제에서는 더 딥하게 들어가서 더 정교하게 체크할 수 있는 함수를 사용

    // IsValidLowLevel: null 포인터도 함께 체크됨
    if (InObject->IsValidLowLevel())
    {
        UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 않은 언리얼 오브젝트"), *InTag);
    }
}


// null값인지 체크하는 함수
void CheckUObjectIsNull(const UObject* InObject, const FString& InTag)
{
    if (nullptr == InObject)
    {
        UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터 언리얼 오브젝트"), *InTag);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터가 아닌 언리얼 오브젝트"), *InTag);
    }
}

void UMyGameInstance::Init()
{
    Super::Init();

    NonPropStudent = NewObject<UStudent>();
    PropStudent = NewObject<UStudent>();

    NonPropStudents.Add(NewObject<UStudent>());
    PropStudents.Add(NewObject<UStudent>());

    // 일반 오브젝트이기 때문에 new
    StudentManager = new FStudentManager(NewObject<UStudent>());
}

void UMyGameInstance::Shutdown()
{
    Super::Shutdown();

    const UStudent* StudentInManager = StudentManager->GetStudent();

    // StudentManager 소멸
    delete StudentManager;
    StudentManager = nullptr;


    // StudentManager가 지워졌을 때 StudentManager의 인자로 들어왔던 Student가 유효한지 확인
    CheckUObjectIsNull(StudentInManager, TEXT("StudentInManager"));
    CheckUObjectIsValid(StudentInManager, TEXT("StudentInManager"));


    // 언리얼 오브젝트가 유효한지 확인
    CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
    CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

    CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
    CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));


    // 자료구조 컨테이너 안의 언리얼 오브젝트도 안전하게 관리하는 방법
    CheckUObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
    CheckUObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));

    CheckUObjectIsNull(PropStudents[0], TEXT("PropStudents"));
    CheckUObjectIsValid(PropStudents[0], TEXT("PropStudents"));
}
