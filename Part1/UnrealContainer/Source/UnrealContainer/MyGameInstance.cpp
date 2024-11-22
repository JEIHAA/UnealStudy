// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"
// 언리얼은 여러 알고리즘 라이브러리를 언리얼 엔진 컨테이너에 맞게 제공하고 있음
// 대표적인 합을 구하는 알고리즘을 위한 헤더 Algo/Accumulate.h

FString MakeRandomName()
{
    TCHAR FirstChar[] = TEXT("김이박최");
    TCHAR MiddleChar[] = TEXT("상혜지성");
    TCHAR LastChar[] = TEXT("수은원연");

    TArray<TCHAR> RandArray;
    RandArray.SetNum(3); // 공간 3개 확보
    RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
    RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
    RandArray[2] = LastChar[FMath::RandRange(0, 3)];

    return RandArray.GetData();
    // TArray는 TCHAR배열을 포함한 컨테이너.
    // 포인터 값을 넘겨주면 반환값을 FString으로 지정했기 때문에
    // 자동으로 FString이 만들어짐.
}


void UMyGameInstance::Init()
{
    Super::Init();

    const int32 ArrayNum = 10;
    TArray<int32> Int32Array; //메모리를 차지하지 않는 빈 상태

    for (int32 ix = 1; ix <= ArrayNum; ++ix)
    {
        // Primitive Type(기본 타입)의 경우 Emplace나 Add나 큰 차이는 없음
        // 가독성을 위해 Add가 낫긴 하지만 성능에 정말 신경쓰고 싶다면 Emplace 사용해도 무방
        Int32Array.Add(ix);
    }

    // 조건에 해당하는 구문을 람다식으로 적는 것이 일반적
    Int32Array.RemoveAll(
        [](int32 Val)
        {
            return Val % 2 == 0; // 짝수 제거
        }
    );

    Int32Array += { 2, 4, 6, 8, 10};
    // 짝수를 제거하고 다시 넣었기 때문에 {1,2,3,4,5,2,4,...,10}으로 채워짐

    // C스타일 low한 접근
    TArray<int32> Int32ArrayCompare;
    int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
    
    // CArray를 TArray에 넣어야함
    Int32ArrayCompare.AddUninitialized(ArrayNum);
    // 초기화되지 않는 데이터 빠르게 넣기
    FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);
    // Int32ArrayCompare의 포인터를 가져와 CArray의 값을 sizeof(int32) * ArrayNum만큼 복제해서 넣기
    
    ensure(Int32Array == Int32ArrayCompare);
    // 같음, 에러 발생하지 않음


    // 배열 요소의 합을 구하는 방법
    // for반복
    int32 Sum = 0;
    for(const int32& Int32Elem : Int32Array)
    {
        Sum += Int32Elem;
    }
    ensure(Sum == 55);

    // Accumulate사용
    int32 SumByAlgo = Algo::Accumulate(Int32Array, 0); //Accumulate(배열, 시작값)
    ensure(Sum == SumByAlgo); //같음

    TSet<int32> Int32Set; //비어있는 상태
    for (int32 ix = 1; ix <= ArrayNum; ++ix)
    {
        Int32Set.Add(ix);
    }


    Int32Set.Remove(2); //RemoveAll 같은건 없음
    Int32Set.Remove(4);
    Int32Set.Remove(6);
    Int32Set.Remove(8);
    Int32Set.Remove(10);
    Int32Set.Add(2);
    Int32Set.Add(4);
    Int32Set.Add(6);
    Int32Set.Add(8);
    Int32Set.Add(10);
    
    const int32 StudentNum = 300;
    for (int32 ix = 1; ix <= StudentNum; ++ix)
    {
        // 구조체이기 때문에 복사 비용 발생, Add보단 Emplace
        StudentsData.Emplace(FStudentData(MakeRandomName(), ix)); 
    }

    TArray<FString> AllStudentsNames;

    // Algo::Transform 데이터 옮겨담기 함수
    // (inputData, outData, 람다식) 
    // TArray에 옮겨담기
    Algo::Transform(StudentsData, AllStudentsNames,
        // 첫번째 인자 : TArray에서 선언한 데이터 타입의 값
        // TArray<FStudentData> StudentsData;
        [](const FStudentData& Val) 
        {
            return Val.Name; // 리턴값 : 옮길 데이터 타입에 대한 FString 값
        }
    );
    // StudentsData의 TArray값을 String TArray로 함수 한번에 옮기기 가능
    UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수: %d"), AllStudentsNames.Num());

    // TSet에 옮겨담기
    TSet<FString> AllUniqueNames; // 중복을 허용하지 않음
    Algo::Transform(StudentsData, AllUniqueNames,
        [](const FStudentData& Val)
        {
            return Val.Name;
        }
    );
    UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수: %d"), AllUniqueNames.Num());

    // 순번을 Key로 만든 학생 Map
    Algo::Transform(StudentsData, StudentsMap,
        [](const FStudentData& Val)
        {
            // TPair로 반환해줘야 TMap에 들어감
            return TPair<int32, FString>(Val.Order, Val.Name);
        }
    );

    UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수: %d"), StudentsMap.Num());


    // 이름을 Key로
    TMap<FString, int32> StudentsMapByUniqueName; // TMap은 중복을 허용하지 않음
    Algo::Transform(StudentsData, StudentsMapByUniqueName,
        [](const FStudentData& Val)
        {
            return TPair<FString, int32>(Val.Name, Val.Order);
        }
    );
    UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 수: %d"), StudentsMapByUniqueName.Num());

    TMultiMap<FString, int32> StudentsMapByName;
    Algo::Transform(StudentsData, StudentsMapByName,
        [](const FStudentData& Val) 
        {
            return TPair<FString, int32>(Val.Name, Val.Order);
        }
    );
    UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 멀티맵의 레코드 수: %d"), StudentsMapByName.Num());

    // 특정 이름을 가진 학생이 몇명 있는지에 대한 정보 뽑기
    const FString TargetName(TEXT("이혜은"));
    TArray<int32> AllOrders;
    StudentsMapByName.MultiFind(TargetName, AllOrders);

    UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생 수: %d"), *TargetName, AllOrders.Num());

    TSet<FStudentData> StudentsSet;
    for (int32 ix = 1; ix <= StudentNum; ++ix)
    {
        // 구조체이기 때문에 복사 비용 발생, Add보단 Emplace
        StudentsSet.Emplace(FStudentData(MakeRandomName(), ix));
    }
    
}
