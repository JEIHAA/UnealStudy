// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
    Name = TEXT("이학생");
}

void UStudent::DoLesson()
{
    //상위 클래스가 ILessonInterface가 아닌 Person으로 되어 있기 때문에 Super를 사용할 수 없음
    //단일 상속만 지원
    ILessonInterface::DoLesson(); 
    UE_LOG(LogTemp, Log, TEXT("%s님은 공부합니다."), *Name);
}
