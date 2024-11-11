// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"
#include "Card.h"

//부모클래스의 생성자가 호출된 이후에 호출되기 때문에 CreateDefaultSubobject를 할 필요는 없다
//하위 클래스에서 다시하면 중복됨
UTeacher::UTeacher()
{
    Name = TEXT("이선생");
    Card->SetCardType(ECardType::Teacher);
}

void UTeacher::DoLesson()
{
    ILessonInterface::DoLesson();
    UE_LOG(LogTemp, Log, TEXT("%s님은 가르칩니다."), *Name);
}
