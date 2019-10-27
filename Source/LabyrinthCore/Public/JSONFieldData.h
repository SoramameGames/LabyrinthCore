/*	JSON Query Plugin
	Copyright(C) 2015-2018 Stefan 'Stefander' Wijnker
	Special thanks: RVillani, Zakkar, Kheka, conneich, Patrik2991, Quantum & johnbo (Unreal forums)
	This program is free software : you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "Json.h"
#include "JSONFieldData.generated.h"

/**
 * 
 */
//UCLASS()
UCLASS(BlueprintType, Blueprintable, Category = "JSON")
class LABYRINTHCORE_API UJSONFieldData : public UObject
{
	GENERATED_BODY()

public:
	TSharedPtr<FJsonObject> Data;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Create JSON", Keywords = "new"), Category = "JSON")
	static UJSONFieldData* Create();


	UFUNCTION(BlueprintPure, meta = (DisplayName = "Check If Field Exists"), Category = "JSON")
	bool HasField(const FString& key);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Keys"), Category = "JSON")
	TArray<FString> GetObjectKeys();


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "From String"), Category = "JSON")
	bool FromString(const FString& dataString);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "JSON To String", CompactNodeTitle = "->", Keywords = "cast text convert serialize"), Category = "JSON")
	FString ToString();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "From File"), Category = "JSON")
	bool FromFile(const FString& FilePath);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Field"), Category = "JSON")
	UJSONFieldData* GetObject(const FString& key, bool& success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object Field"), Category = "JSON")
	UJSONFieldData* SetObject(const FString& key, const UJSONFieldData* objectData);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Array Field"), Category = "JSON")
	TArray<UJSONFieldData*> GetObjectArray(const FString& key, bool& success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object Array Field"), Category = "JSON")
	UJSONFieldData* SetObjectArray(const FString& key, const TArray<UJSONFieldData*> arrayData);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Field"), Category = "JSON")
	FString GetString(const FString& key, bool& success) const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add String Field"), Category = "JSON")
	UJSONFieldData* SetString(const FString& key, const FString& value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Array Field"), Category = "JSON")
	TArray<FString> GetStringArray(const FString& key, bool& success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add String Array Field"), Category = "JSON")
	UJSONFieldData* SetStringArray(const FString& key, const TArray<FString> data);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Boolean Field"), Category = "JSON")
	bool GetBool(const FString& key, bool& success) const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Boolean Field"), Category = "JSON")
	UJSONFieldData* SetBoolean(const FString& key, const bool value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Boolean Array Field"), Category = "JSON")
	TArray<bool> GetBoolArray(const FString& key, bool& success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Boolean Array Field"), Category = "JSON")
	UJSONFieldData* SetBoolArray(const FString& key, const TArray<bool> data);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Float Field"), Category = "JSON")
	float GetFloat(const FString& key, bool& success) const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Float Field"), Category = "JSON")
	UJSONFieldData* SetFloat(const FString& key, const float value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Float Array Field"), Category = "JSON")
	TArray<float> GetFloatArray(const FString& key, bool& success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Float Array Field"), Category = "JSON")
	UJSONFieldData* SetFloatArray(const FString& key, const TArray<float> data);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Integer Field"), Category = "JSON")
	int32 GetInt(const FString& key, bool& success) const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Integer Field"), Category = "JSON")
	UJSONFieldData* SetInt(const FString& key, const int32 value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Integer Array Field"), Category = "JSON")
	TArray<int32> GetIntArray(const FString& key, bool& success);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Integer Array Field"), Category = "JSON")
	UJSONFieldData* SetIntArray(const FString& key, const TArray<int32> data);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Field Is Null"), Category = "JSON")
	bool GetIsNull(const FString& key, bool& fieldExists) const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Null Field"), Category = "JSON")
	UJSONFieldData* SetNull(const FString& key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Null Array Field"), Category = "JSON")
	UJSONFieldData* SetNullArray(const FString& key, const int32& length);

private:
	void Reset();

	void WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value);
};
