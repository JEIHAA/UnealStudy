// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentManager.h"
#include "Student.h"

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
    if (SafeStudent->IsValidLowLevel())
    {
        // 인자로 들어온 콜렉터에 AddReferencedObject를 사용해
        // 관리할 언리얼 오브젝트를 등록해주면 됨
        Collector.AddReferencedObject(SafeStudent);
    }
}
