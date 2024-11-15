// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"
// 언리얼 오브젝트를 Json 오브젝트로 편리하게 변환해주는 헬퍼 라이브러리들이 들어있음

// 출력함수
void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] 이름 %s 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
    Super::Init();

    FStudentData RawDataSrc(16, TEXT("이득우"));


    // 구조체 데이터를 파일로 저장하기 위한 경로 지정
    // 플랫폼 관련한 함수 중에 프로젝트 디렉토리를 얻어오는 함수가 있음
    // Saved 폴더를 묶어주면(Combine) 해당 폴더의 경로를 얻을 수 있음
    // 프로젝트 폴더 내의 Saved폴더.
    const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
    UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더 : %s"), *SavedDir);

    // Saved 폴더 안에 저장할 파일 이름 지정
    {
        const FString RawDataFileName(TEXT("RawData.bin"));
        // 파일에 대한 절대경로 얻기
        FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFileName);
        // 로그 찍어보면 폴더가 깔끔하지 않고 알아보기 힘들게 나옴
        UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로 : %s"), *RawDataAbsolutePath);
        // MakeStandardFilename을 사용하면 파일 이름을 보기 좋게 바꿔줌
        FPaths::MakeStandardFilename(RawDataAbsolutePath);
        UE_LOG(LogTemp, Log, TEXT("변경할 파일 전체 경로 : %s"), *RawDataAbsolutePath);

        // 이 파일을 직접 생성하고 구조체 내의 데이터를 여기에 쓰고 다시 읽어오기
        // 파일에 쓸 수 있는 아카이브 클래스 생성해주면 됨
        // FileManager라는 인터페이스의 CreateFileWriter라는 함수에서 아카이브를 얻어올 수 있음
        // 이때 경로를 RawDataAbsolutePath로 지정해주면
        // Saved 안의 RawData.bin 파일을 쓸 수 있는 아카이브 클래스를 생성하게 됨
        FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);

        if (nullptr != RawFileWriterAr)
        {
            // 파일에 데이터 집어넣기
            // *RawFileWriterAr << RawDataSrc.Order;
            // *RawFileWriterAr << RawDataSrc.Name;
            // 이렇게 하면 되지만 매번 멤버 변수를 사용해서 집어넣기는 번거로우니
            // 헤더 파일에서 직렬화 연산자인 Shift연산자(<<)를 직접 타입에 대해서 지정해주면 됨
            *RawFileWriterAr << RawDataSrc;
            RawFileWriterAr->Close();
            // 전송 완료되면 파일 닫기
            delete RawFileWriterAr;
            RawFileWriterAr = nullptr;
        }

        // 구조체에 파일에 저장한 값을 불러들여 덮어쓰기
        FStudentData RawDataDest;
        // Reader 아카이브
        FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
            if (nullptr != RawFileReaderAr)
            {
                // 읽기와 쓰기 모두 << 연산자 사용
                // 읽거나 불러들이기가 자동으로 진행됨
                *RawFileReaderAr << RawDataDest;
                RawFileReaderAr->Close();
                delete RawFileReaderAr;
                RawFileReaderAr = nullptr;
                
                UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 %s 순번 %d"), *RawDataDest.Name, RawDataDest.Order);
            }
    }

    StudentSrc = NewObject<UStudent>();
    StudentSrc->SetName(TEXT("이득우"));
    StudentSrc->SetOrder(59);

    // 언리얼 오브젝트 저장하기
    {
        const FString ObjectDataFileName(TEXT("ObjectData.bin"));
        FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, *ObjectDataFileName);
        FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

        // 언리얼 오브젝트의 내용을 메모리에 저장하기
        // 바이트 스트림은 TArray<uint8>로 지정해주면 됨
        // 직렬화를 위한 버퍼.
        TArray<uint8> BufferArray;
        // 버퍼와 연동되는 메모리 Writer
        FMemoryWriter MemoryWriterAr(BufferArray);
        // Serialize함수에 메모리에 쓸 아카이브를 지정
        StudentSrc->Serialize(MemoryWriterAr);

        // 메모리의 BufferArray에 Student 언리얼 오브젝트에 대한 내용이 적혀있음
        // 이것을 파일로 다시 저장
        
        // delete, null 작업이 번거로우니
        // 스마트 포인터 라이브러리를 사용해 한번에 처리
        // TUniquePtr을 사용해 함수 내에서 바로 쓰고 지울 용도로 편리하게 사용 가능
        if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)))
        {
            // 유니크 포인터를 선언한 로직을 벗어나면 알아서 메모리가 해제됨
            // Close만 신경쓰면 됨
            *FileWriterAr << BufferArray;
            FileWriterAr->Close();
        }

        // 파일로부터 버퍼 읽어오기
        TArray<uint8> BufferArrayFromFile;
        if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)))
        {
            *FileReaderAr << BufferArrayFromFile;
            FileReaderAr->Close();
        }

        // 버퍼에 있는 데이터를 메모리에 전송하기
        FMemoryReader MemoryReaderAr(BufferArrayFromFile);
        UStudent* StudentDest = NewObject<UStudent>();
        StudentDest->Serialize(MemoryReaderAr);
        PrintStudentInfo(StudentDest, TEXT("ObjectData"));
    }

    // Json으로 읽고 쓰기
    {
        const FString JsonDataFileName(TEXT("StudentJsonData.txt"));
        FString JsonDataAbsolutePath = FPaths::Combine(*SavedDir, *JsonDataFileName);
        FPaths::MakeStandardFilename(JsonDataAbsolutePath);
        
        // Json은 FJson이라는 특별한 객체를 생성해줘야함
        // 언리얼 오브젝트를 Json오브젝트로 바꿔줘야함
        // 레퍼런스로 편하게 사용할 수 있게 공유 레퍼런스 설정
        // Null 이 아님을 보장해주기 때문에 객체 생성해서 공유 레퍼런스에 지정
        TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();
        // UStructToJsonObject: 언리얼 오브젝트도 결국 UStruct에서 상속받음.
        // 프로퍼티를 Json으로 변환할 것이기 때문에 UStruct 정보를 넘긴다.
        // 클래스 정보와 오브젝트 포인터, Json 오브젝트에 대한 공유 레퍼런스를 넘겨주면
        // 자동으로 변환해준다.
        FJsonObjectConverter::UStructToJsonObject(StudentSrc->GetClass(), StudentSrc, JsonObjectSrc);
        // 헤더로는 선언이 되어있는데 구현부가 없어 빌드 시 에러 발생
        // Json 라이브러리들은 별도의 라이브러리를 연동시켜서 구현부를 제공해야함
        // UnrealSerialization.Build.cs 파일을 통해 현재 만들고 있는
        // UnrealSerialization 프로젝트의 모듈에 Json에 관련된 라이브러리를 연동시켜줘야함
        
        // 변환된 내용을 파일에 쓰기
        // Json오브젝트를 문자열로 변환
        FString JsonOutString;
        // TJsonWriterFactory에 의해 Json으로 써주는 아카이브 만들어짐
        TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
        // FJsonSerializer을 활용해 직렬화
        // 첫번째 인자로 JsonObject, 두번째 인자로 JsonString으로 연동시킨 아카이브
        if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
        {
            // FFileHelper::SaveStringToFile 인코딩을 신경쓰지 않아도 운영체제에 맞게 알아서 저장해줌
            FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsolutePath);
        }

        // 불러들이기
        FString JsonInString;
        // FFileHelper을 사용해 문자열 불러들이기
        FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);

        // 불러들인 String을 사용해서 Reader 아카이브 생성
        // TJsonReaderFactory에 Reader값을 인풋으로 넣어줌
        TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

        // Reader로부터 실제로 변환할 Json 오브젝트가 없을수도 (이상한 값이나 null)
        // null일 수도 있기 때문에 Ptr사용
        TSharedPtr<FJsonObject> JsonObjectDest;

        // Reader로부터 실제로 변환할 Json 오브젝트가 있다면
        if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
        {
            UStudent* JsonStudentDest = NewObject<UStudent>();
            // 첫번째 인자로 공유 레퍼런스
            // if문 안에 들어왔다면 공유포인터는 반드시 무언가 할당되어 있기 때문에
            // 공유포인터를 .ToSharedRef()로 공유 레퍼런스로 변환
            // 두번째 인자로 JsonStudentDest의 클래스 정보(스키마), 세번째 인자로 객체 정보
            if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
            {
                //언리얼 오브젝트로 변환이 성공했다면 출력
                PrintStudentInfo(JsonStudentDest, TEXT("JsonData"));
            }

        }
    }

}

