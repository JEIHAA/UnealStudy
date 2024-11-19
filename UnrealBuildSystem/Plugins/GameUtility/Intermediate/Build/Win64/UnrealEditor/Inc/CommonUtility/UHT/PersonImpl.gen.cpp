// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonUtility/Private/PersonImpl.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePersonImpl() {}
// Cross Module References
	COMMONUTILITY_API UClass* Z_Construct_UClass_UPersonImpl();
	COMMONUTILITY_API UClass* Z_Construct_UClass_UPersonImpl_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_CommonUtility();
// End Cross Module References
	void UPersonImpl::StaticRegisterNativesUPersonImpl()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPersonImpl);
	UClass* Z_Construct_UClass_UPersonImpl_NoRegister()
	{
		return UPersonImpl::StaticClass();
	}
	struct Z_Construct_UClass_UPersonImpl_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPersonImpl_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CommonUtility,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPersonImpl_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "PersonImpl.h" },
		{ "ModuleRelativePath", "Private/PersonImpl.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPersonImpl_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPersonImpl>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UPersonImpl_Statics::ClassParams = {
		&UPersonImpl::StaticClass,
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
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UPersonImpl_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UPersonImpl_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPersonImpl()
	{
		if (!Z_Registration_Info_UClass_UPersonImpl.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPersonImpl.OuterSingleton, Z_Construct_UClass_UPersonImpl_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UPersonImpl.OuterSingleton;
	}
	template<> COMMONUTILITY_API UClass* StaticClass<UPersonImpl>()
	{
		return UPersonImpl::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPersonImpl);
	UPersonImpl::~UPersonImpl() {}
	struct Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Private_PersonImpl_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Private_PersonImpl_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UPersonImpl, UPersonImpl::StaticClass, TEXT("UPersonImpl"), &Z_Registration_Info_UClass_UPersonImpl, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPersonImpl), 242312738U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Private_PersonImpl_h_1954853665(TEXT("/Script/CommonUtility"),
		Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Private_PersonImpl_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_UnealStudy_UnrealBuildSystem_Plugins_GameUtility_Source_CommonUtility_Private_PersonImpl_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
