export type AllTypes_Properties_StringField = string;

export type AllTypes_Properties_ObjectField_Properties_Nested = string;

export type AllTypes_Properties_ObjectField_AdditionalProperties = never;

export interface AllTypes_Properties_ObjectField {
  "nested"?: AllTypes_Properties_ObjectField_Properties_Nested;
}

export type AllTypes_Properties_NumberField = number;

export type AllTypes_Properties_NullField = null;

export type AllTypes_Properties_NestedTypes_Properties_DeepNull = null;

export type AllTypes_Properties_NestedTypes_Properties_DeepInteger = number;

export type AllTypes_Properties_NestedTypes_Properties_DeepBoolean = boolean;

export type AllTypes_Properties_NestedTypes_AdditionalProperties = never;

export interface AllTypes_Properties_NestedTypes {
  "deepBoolean"?: AllTypes_Properties_NestedTypes_Properties_DeepBoolean;
  "deepNull"?: AllTypes_Properties_NestedTypes_Properties_DeepNull;
  "deepInteger"?: AllTypes_Properties_NestedTypes_Properties_DeepInteger;
}

export type AllTypes_Properties_MultiType_AnyOf_ZIndex2 = null;

export type AllTypes_Properties_MultiType_AnyOf_ZIndex1 = number;

export type AllTypes_Properties_MultiType_AnyOf_ZIndex0 = string;

export type AllTypes_Properties_MultiType =
  AllTypes_Properties_MultiType_AnyOf_ZIndex0 |
  AllTypes_Properties_MultiType_AnyOf_ZIndex1 |
  AllTypes_Properties_MultiType_AnyOf_ZIndex2;

export type AllTypes_Properties_IntegerField = number;

export type AllTypes_Properties_BooleanField = boolean;

export type AllTypes_Properties_ArrayField_Items = string;

export type AllTypes_Properties_ArrayField = AllTypes_Properties_ArrayField_Items[];

export type AllTypes_AdditionalProperties = never;

export interface AllTypes {
  "stringField": AllTypes_Properties_StringField;
  "numberField": AllTypes_Properties_NumberField;
  "integerField": AllTypes_Properties_IntegerField;
  "booleanField": AllTypes_Properties_BooleanField;
  "nullField": AllTypes_Properties_NullField;
  "arrayField": AllTypes_Properties_ArrayField;
  "objectField": AllTypes_Properties_ObjectField;
  "multiType"?: AllTypes_Properties_MultiType;
  "nestedTypes"?: AllTypes_Properties_NestedTypes;
}
