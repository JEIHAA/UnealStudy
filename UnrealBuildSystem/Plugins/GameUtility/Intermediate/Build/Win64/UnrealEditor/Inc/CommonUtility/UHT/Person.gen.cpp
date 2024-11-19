// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonUtility/Public/Person.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePerson() {}
// Cross Module References
	COMMONUTILITY_API UClass* Z_Construct_UClass_UPerson();
	COMMONUTILITY_API UClass* Z_Construct_UClass_UPerson_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_CommonUtility();
// End Cross Module References
	void UPerson::StaticRegisterNativesUPerson()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPerson);
	UClass* Z_Construct_UClass_UPerson_NoRegister()
	{
		return UPerson::StaticClass();
	}
	struct Z_Construct_UClass_UPerson_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPerson_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CommonUtility,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPerson_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Person.h" },
		{ "ModuleRelativePath", "Public/Person.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPerson_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPerson>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UPerson_Statics::ClassParams = {
		&UPerson::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UPerson_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPerson()
	{
		if (!Z_Registration_Info_UClass_UPerson.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPerson.OuterSingleton, Z_Construct_UClass_UPerson_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UPerson.OuterSingleton;
	}
	template<> COMMONUTILITY_API UClass* StaticClass<UPerson>()
	{
		return UPerson::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPerson);
	UPerson::~UPerson() {}
	struct Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Public_Person_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Public_Person_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UPerson, UPerson::StaticClass, TEXT("UPerson"), &Z_Registration_Info_UClass_UPerson, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPerson), 239601421U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Public_Person_h_4273998258(TEXT("/Script/CommonUtility"),
		Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Public_Person_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Public_Person_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
