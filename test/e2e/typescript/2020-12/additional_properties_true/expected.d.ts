export type FlexibleRecord_Properties_Name = string;

export type FlexibleRecord_Properties_Count = number;

export type FlexibleRecord_AdditionalProperties_AnyOf_ZIndex5 = number;

export type FlexibleRecord_AdditionalProperties_AnyOf_ZIndex4 = string;

export type FlexibleRecord_AdditionalProperties_AnyOf_ZIndex3 = unknown[];

export type FlexibleRecord_AdditionalProperties_AnyOf_ZIndex2 = Record<string, unknown>;

export type FlexibleRecord_AdditionalProperties_AnyOf_ZIndex1 = boolean;

export type FlexibleRecord_AdditionalProperties_AnyOf_ZIndex0 = null;

export type FlexibleRecord_AdditionalProperties =
  FlexibleRecord_AdditionalProperties_AnyOf_ZIndex0 |
  FlexibleRecord_AdditionalProperties_AnyOf_ZIndex1 |
  FlexibleRecord_AdditionalProperties_AnyOf_ZIndex2 |
  FlexibleRecord_AdditionalProperties_AnyOf_ZIndex3 |
  FlexibleRecord_AdditionalProperties_AnyOf_ZIndex4 |
  FlexibleRecord_AdditionalProperties_AnyOf_ZIndex5;

export interface FlexibleRecord {
  "name": FlexibleRecord_Properties_Name;
  "count"?: FlexibleRecord_Properties_Count;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    FlexibleRecord_Properties_Name |
    FlexibleRecord_Properties_Count |
    FlexibleRecord_AdditionalProperties |
    undefined;
}
