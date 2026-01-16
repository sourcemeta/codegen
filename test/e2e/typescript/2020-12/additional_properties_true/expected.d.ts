export type FlexibleRecordName = string;

export type FlexibleRecordCount = number;

export type FlexibleRecordAdditionalProperties_5 = number;

export type FlexibleRecordAdditionalProperties_4 = string;

export type FlexibleRecordAdditionalProperties_3 = unknown[];

export type FlexibleRecordAdditionalProperties_2 = Record<string, unknown>;

export type FlexibleRecordAdditionalProperties_1 = boolean;

export type FlexibleRecordAdditionalProperties_0 = null;

export type FlexibleRecordAdditionalProperties =
  FlexibleRecordAdditionalProperties_0 |
  FlexibleRecordAdditionalProperties_1 |
  FlexibleRecordAdditionalProperties_2 |
  FlexibleRecordAdditionalProperties_3 |
  FlexibleRecordAdditionalProperties_4 |
  FlexibleRecordAdditionalProperties_5;

export interface FlexibleRecord {
  "name": FlexibleRecordName;
  "count"?: FlexibleRecordCount;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    FlexibleRecordName |
    FlexibleRecordCount |
    FlexibleRecordAdditionalProperties |
    undefined;
}
