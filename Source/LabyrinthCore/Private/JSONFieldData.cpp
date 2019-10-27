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

#include "JSONFieldData.h"
#include "Engine/Engine.h"

UJSONFieldData* UJSONFieldData::Create() {
	// Construct the object and return it
	return NewObject<UJSONFieldData>();
}

bool UJSONFieldData::HasField(const FString& key) {
	return Data->HasField(key);
}

TArray<FString> UJSONFieldData::GetObjectKeys() {
	TArray<FString> stringArray;
	for (TMap<FString, TSharedPtr<FJsonValue>>::TConstIterator currJsonValue = Data->Values.CreateConstIterator(); currJsonValue; ++currJsonValue) {
		stringArray.Add((*currJsonValue).Key);
	}

	return stringArray;
}

bool UJSONFieldData::FromString(const FString& dataString) {
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(dataString);

	// Deserialize the JSON data
	bool isDeserialized = FJsonSerializer::Deserialize(JsonReader, Data);

	if (!isDeserialized || !Data.IsValid()) {
		//UE_LOG(JSONQueryLog, Error, TEXT("JSON data is invalid! Input:\n'%s'!"), *dataString);
		return false;
	}

	return true;
}

FString UJSONFieldData::ToString() {
	FString outStr;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&outStr);

	// Start writing the response
	WriteObject(JsonWriter, "", new FJsonValueObject(Data));
	JsonWriter->Close();

	return outStr;
}

//** FROM/POST FILE **//

bool UJSONFieldData::FromFile(const FString& FilePath) {
	FString Result;
	FString FullJsonPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / FilePath);
	if (!FFileHelper::LoadFileToString(Result, *FullJsonPath)) {
		//UE_LOG(JSONQueryLog, Error, TEXT("Can't load JSON data from '%s'!"), *FilePath);
	}

	return FromString(Result);
}

UJSONFieldData* UJSONFieldData::GetObject(const FString& key, bool& success) {
	UJSONFieldData* fieldObj = NULL;
	const TSharedPtr<FJsonObject> *outPtr;
	if (!Data->TryGetObjectField(*key, outPtr)) {
		//UE_LOG(JSONQueryLog, Error, TEXT("Entry '%s' not found in the field data!"), *key);
		success = false;
		return NULL;
	}

	fieldObj = UJSONFieldData::Create();
	fieldObj->Data = *outPtr;
	success = true;
	return fieldObj;
}

UJSONFieldData* UJSONFieldData::SetObject(const FString& key, const UJSONFieldData* objectData) {
	Data->SetObjectField(*key, objectData->Data);
	return this;
}

TArray<UJSONFieldData*> UJSONFieldData::GetObjectArray(const FString& key, bool& success) {
	TArray<UJSONFieldData*> objectArray;
	const TArray<TSharedPtr<FJsonValue>>* valueArray;
	success = Data->TryGetArrayField(*key, valueArray);
	if (success) {
		for (int32 i = 0; i < valueArray->Num(); i++) {
			UJSONFieldData* pageData = Create();
			pageData->Data = (*valueArray)[i]->AsObject();
			objectArray.Add(pageData);
		}
	}

	return objectArray;
}

UJSONFieldData* UJSONFieldData::SetObjectArray(const FString& key, const TArray<UJSONFieldData*> objectData) {
	TArray<TSharedPtr<FJsonValue>> *dataArray = new TArray<TSharedPtr<FJsonValue>>();
	for (int32 i = 0; i < objectData.Num(); i++) {
		dataArray->Add(MakeShareable(new FJsonValueObject(objectData[i]->Data)));
	}

	Data->SetArrayField(*key, *dataArray);
	return this;
}

//** FSTRING **//
FString UJSONFieldData::GetString(const FString& key, bool& success) const {
	FString outString = "";
	success = Data->TryGetStringField(*key, outString);
	if (!success) {
		//UE_LOG(JSONQueryLog, Error, TEXT("String entry '%s' not found in the field data!"), *key);
	}

	return outString;
}

UJSONFieldData* UJSONFieldData::SetString(const FString& key, const FString& value) {
	Data->SetStringField(*key, *value);
	return this;
}

TArray<FString> UJSONFieldData::GetStringArray(const FString& key, bool& success) {
	TArray<FString> stringArray;
	const TArray<TSharedPtr<FJsonValue>>* valueArray;
	success = Data->TryGetArrayField(key, valueArray);
	if (success) {
		for (int32 i = 0; i < valueArray->Num(); i++) {
			UJSONFieldData* pageData = Create();
			stringArray.Add((*valueArray)[i]->AsString());
		}
	}

	return stringArray;
}

UJSONFieldData* UJSONFieldData::SetStringArray(const FString& key, const TArray<FString> stringData) {
	TArray<TSharedPtr<FJsonValue>> *dataArray = new TArray<TSharedPtr<FJsonValue>>();
	for (int32 i = 0; i < stringData.Num(); i++) {
		dataArray->Add(MakeShareable(new FJsonValueString(stringData[i])));
	}

	Data->SetArrayField(*key, *dataArray);
	return this;
}

//** BOOL **//
bool UJSONFieldData::GetBool(const FString& key, bool& success) const {
	bool value = false;
	success = Data->TryGetBoolField(*key, value);
	if (!success) {
		//UE_LOG(JSONQueryLog, Error, TEXT("Boolean entry '%s' not found in the field data!"), *key);
	}

	return value;
}

UJSONFieldData* UJSONFieldData::SetBoolean(const FString& key, const bool value) {
	Data->SetBoolField(*key, value);
	return this;
}

TArray<bool> UJSONFieldData::GetBoolArray(const FString& key, bool& success) {
	TArray<bool> boolArray;
	const TArray<TSharedPtr<FJsonValue>>* valueArray;
	success = Data->TryGetArrayField(*key, valueArray);
	if (success) {
		for (int32 i = 0; i < valueArray->Num(); i++) {
			UJSONFieldData* pageData = Create();
			boolArray.Add((*valueArray)[i]->AsBool());
		}
	}

	return boolArray;
}

UJSONFieldData* UJSONFieldData::SetBoolArray(const FString& key, const TArray<bool> data) {
	TArray<TSharedPtr<FJsonValue>> *dataArray = new TArray<TSharedPtr<FJsonValue>>();
	for (int32 i = 0; i < data.Num(); i++) {
		dataArray->Add(MakeShareable(new FJsonValueBoolean(data[i])));
	}

	Data->SetArrayField(*key, *dataArray);
	return this;
}

//** FLOAT **//
float UJSONFieldData::GetFloat(const FString& key, bool& success) const {
	double value = 0.0f;
	success = Data->TryGetNumberField(*key, value);
	if (!success) {
		//UE_LOG(JSONQueryLog, Error, TEXT("Number entry '%s' not found in the field data!"), *key);
	}

	return static_cast<float>(value);
}

UJSONFieldData* UJSONFieldData::SetFloat(const FString& key, const float value) {
	Data->SetNumberField(*key, static_cast<double>(value));
	return this;
}

TArray<float> UJSONFieldData::GetFloatArray(const FString& key, bool& success) {
	TArray<float> floatArray;
	const TArray<TSharedPtr<FJsonValue>>* valueArray;
	success = Data->TryGetArrayField(*key, valueArray);
	if (success) {
		for (int32 i = 0; i < valueArray->Num(); i++) {
			UJSONFieldData* pageData = Create();
			floatArray.Add(static_cast<float>((*valueArray)[i]->AsNumber()));
		}
	}

	return floatArray;
}

UJSONFieldData* UJSONFieldData::SetFloatArray(const FString& key, const TArray<float> data) {
	TArray<TSharedPtr<FJsonValue>> *dataArray = new TArray<TSharedPtr<FJsonValue>>();
	for (int32 i = 0; i < data.Num(); i++) {
		dataArray->Add(MakeShareable(new FJsonValueNumber(static_cast<double>(data[i]))));
	}

	Data->SetArrayField(*key, *dataArray);
	return this;
}

//** INT32 **//
int32 UJSONFieldData::GetInt(const FString& key, bool& success) const {
	int32 value = 0;
	success = Data->TryGetNumberField(*key, value);
	if (!success) {
		//UE_LOG(JSONQueryLog, Error, TEXT("Number entry '%s' not found in the field data!"), *key);
	}

	return value;
}

UJSONFieldData* UJSONFieldData::SetInt(const FString& key, const int32 value) {
	Data->SetNumberField(*key, static_cast<double>(value));
	return this;
}

TArray<int32> UJSONFieldData::GetIntArray(const FString& key, bool& success) {
	TArray<int32> intArray;
	const TArray<TSharedPtr<FJsonValue>>* valueArray;
	success = Data->TryGetArrayField(*key, valueArray);
	if (success) {
		for (int32 i = 0; i < valueArray->Num(); i++) {
			UJSONFieldData* pageData = Create();
			intArray.Add(static_cast<int32>((*valueArray)[i]->AsNumber()));
		}
	}

	return intArray;
}

UJSONFieldData* UJSONFieldData::SetIntArray(const FString& key, const TArray<int32> data) {
	TArray<TSharedPtr<FJsonValue>> *dataArray = new TArray<TSharedPtr<FJsonValue>>();
	for (int32 i = 0; i < data.Num(); i++) {
		dataArray->Add(MakeShareable(new FJsonValueNumber(static_cast<double>(data[i]))));
	}

	Data->SetArrayField(*key, *dataArray);
	return this;
}

//** NULL **//
UJSONFieldData* UJSONFieldData::SetNull(const FString& key) {
	Data->SetObjectField(*key, NULL);
	return this;
}

bool UJSONFieldData::GetIsNull(const FString& key, bool& success) const {
	// If the current post data isn't valid, return an empty string
	success = Data->HasField(key);
	if (!success) {
		//UE_LOG(JSONQueryLog, Error, TEXT("Number entry '%s' not found in the field data!"), *key);
	}

	return Data->HasTypedField<EJson::Null>(key);
}

UJSONFieldData* UJSONFieldData::SetNullArray(const FString& key, const int32& length) {
	TArray<TSharedPtr<FJsonValue>> *dataArray = new TArray<TSharedPtr<FJsonValue>>();
	for (int32 i = 0; i < length; i++) {
		dataArray->Add(MakeShareable(new FJsonValueNull()));
	}

	Data->SetArrayField(*key, *dataArray);
	return this;
}


//** PRIVATE **//
void UJSONFieldData::Reset() {
	// If the post data is valid
	if (Data.IsValid()) {
		// Clear the current post data
		Data.Reset();
	}

	// Create a new JSON object
	Data = MakeShareable(new FJsonObject());
}

void UJSONFieldData::WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value) {
	bool hasKey = key.Len() > 0;
	TSharedPtr<FJsonObject> objectData;
	TArray<TSharedPtr<FJsonValue>> objectArray;

	switch (value->Type) {
	case EJson::Object:
		if (hasKey) {
			writer->WriteObjectStart(key);
		}
		else {
			writer->WriteObjectStart();
		}

		objectData = value->AsObject();
		for (TMap<FString, TSharedPtr<FJsonValue>>::TIterator objectValue = objectData->Values.CreateIterator(); objectValue; ++objectValue) {
			WriteObject(writer, objectValue.Key(), objectValue.Value().Get());
		}

		writer->WriteObjectEnd();
		break;
	case EJson::String:
		if (hasKey) {
			writer->WriteValue(key, value->AsString());
		}
		else {
			writer->WriteValue(value->AsString());
		}
		break;
	case EJson::Boolean:
		if (hasKey) {
			writer->WriteValue(key, value->AsBool());
		}
		else {
			writer->WriteValue(value->AsBool());
		}
		break;
	case EJson::Number:
		if (hasKey) {
			writer->WriteValue(key, value->AsNumber());
		}
		else {
			writer->WriteValue(value->AsNumber());
		}
		break;
	case EJson::Array:
		if (hasKey) {
			writer->WriteArrayStart(key);
		}
		else {
			writer->WriteArrayStart();
		}

		objectArray = value->AsArray();
		for (int32 i = 0; i < objectArray.Num(); i++) {
			WriteObject(writer, "", objectArray[i].Get());
		}

		writer->WriteArrayEnd();
		break;
	case EJson::Null:
		if (hasKey) {
			writer->WriteNull(key);
		}
		else {
			writer->WriteNull();
		}
		break;
	default:
		break;
	}
}
