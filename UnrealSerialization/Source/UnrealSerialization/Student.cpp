// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
    Order = -1;
    Name = TEXT("홍길동");
}

void UStudent::Serialize(FArchive& Ar)
{
    // 언리얼 오브젝트가 가져야하는 기본정인 정보는 알아서 처리해줌
    Super::Serialize(Ar);

    // 프로퍼티의 순번만 지정해주면 됨
    Ar << Order;
    Ar << Name;
}
