// Fill out your copyright notice in the Description page of Project Settings.


#include "Teachar.h"

UTeachar::UTeachar()
{
    Name = TEXT("이선생");
    Year = 3;
    Id = 1;
}

void UTeachar::DoLesson()
{
    Super::DoLesson();
    //상위 클래스가 반영되지 않아 검색이 되지 않을 때
    //헤더 파일을 다시 컴파일해주면 올바른 상위 클래스 정보를 얻어올 수 있다.

    UE_LOG(LogTemp, Log, TEXT("%d년차 선생님 %s님이 수업을 강의합니다."), Year, *Name); //인코딩 변경
}
