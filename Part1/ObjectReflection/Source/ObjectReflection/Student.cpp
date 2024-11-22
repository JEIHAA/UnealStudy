// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
    Name = TEXT("이학생");
    Year = 1;
    Id = 1;
    //기본값을 설정했으면 CDO가 다시 생성되어야하기 때문에
    //미리 컴파일해주는 것이 좋다
}

void UStudent::DoLesson()
{
    Super::DoLesson();

    UE_LOG(LogTemp, Log, TEXT("%d학년 %d번 %s님이 수업을 듣습니다."), Year, Id, *Name); //인코딩 변경
}
