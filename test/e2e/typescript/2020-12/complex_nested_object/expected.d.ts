export type Record_Properties_Region = string;

export type Record_Properties_ReferenceCode = string;

export type Record_Properties_RecordId = string;

export type Record_Properties_OrganizationName = string;

export type Record_Properties_Notes = string;

export type Record_Properties_Meta_Properties_OriginId = string;

export type Record_Properties_Meta_Properties_Origin = string;

export type Record_Properties_Meta_AdditionalProperties = never;

export interface Record_Properties_Meta {
  "origin"?: Record_Properties_Meta_Properties_Origin;
  "originId"?: Record_Properties_Meta_Properties_OriginId;
}

export type Record_Properties_LocationInfo_Properties_StateCode = string;

export type Record_Properties_LocationInfo_Properties_AreaCode = string;

export type Record_Properties_LocationInfo_AdditionalProperties = never;

export interface Record_Properties_LocationInfo {
  "stateCode"?: Record_Properties_LocationInfo_Properties_StateCode;
  "areaCode"?: Record_Properties_LocationInfo_Properties_AreaCode;
}

export type Record_Properties_Items_Items_Properties_SubCategory = string;

export type Record_Properties_Items_Items_Properties_Severity = string;

export type Record_Properties_Items_Items_Properties_SequenceNumber = string;

export type Record_Properties_Items_Items_Properties_ResolvedAt_AnyOf_ZIndex1 = null;

export type Record_Properties_Items_Items_Properties_ResolvedAt_AnyOf_ZIndex0 = Record_X24Defs_UTimestamp;

export type Record_Properties_Items_Items_Properties_ResolvedAt =
  Record_Properties_Items_Items_Properties_ResolvedAt_AnyOf_ZIndex0 |
  Record_Properties_Items_Items_Properties_ResolvedAt_AnyOf_ZIndex1;

export type Record_Properties_Items_Items_Properties_Resolution_AnyOf_ZIndex1 = null;

export type Record_Properties_Items_Items_Properties_Resolution_AnyOf_ZIndex0 = string;

export type Record_Properties_Items_Items_Properties_Resolution =
  Record_Properties_Items_Items_Properties_Resolution_AnyOf_ZIndex0 |
  Record_Properties_Items_Items_Properties_Resolution_AnyOf_ZIndex1;

export type Record_Properties_Items_Items_Properties_Remarks_AnyOf_ZIndex1 = null;

export type Record_Properties_Items_Items_Properties_Remarks_AnyOf_ZIndex0 = string;

export type Record_Properties_Items_Items_Properties_Remarks =
  Record_Properties_Items_Items_Properties_Remarks_AnyOf_ZIndex0 |
  Record_Properties_Items_Items_Properties_Remarks_AnyOf_ZIndex1;

export type Record_Properties_Items_Items_Properties_Outcome = string;

export type Record_Properties_Items_Items_Properties_OccurredAt = Record_X24Defs_UTimestamp;

export type Record_Properties_Items_Items_Properties_Meta_Properties_OriginId = string;

export type Record_Properties_Items_Items_Properties_Meta_Properties_Origin = string;

export type Record_Properties_Items_Items_Properties_Meta_AdditionalProperties = never;

export interface Record_Properties_Items_Items_Properties_Meta {
  "origin"?: Record_Properties_Items_Items_Properties_Meta_Properties_Origin;
  "originId"?: Record_Properties_Items_Items_Properties_Meta_Properties_OriginId;
}

export type Record_Properties_Items_Items_Properties_ItemId = string;

export type Record_Properties_Items_Items_Properties_Description = string;

export type Record_Properties_Items_Items_Properties_Code_AnyOf_ZIndex1 = null;

export type Record_Properties_Items_Items_Properties_Code_AnyOf_ZIndex0 = string;

export type Record_Properties_Items_Items_Properties_Code =
  Record_Properties_Items_Items_Properties_Code_AnyOf_ZIndex0 |
  Record_Properties_Items_Items_Properties_Code_AnyOf_ZIndex1;

export type Record_Properties_Items_Items_Properties_Category = string;

export type Record_Properties_Items_Items_AdditionalProperties = never;

export interface Record_Properties_Items_Items {
  "itemId": Record_Properties_Items_Items_Properties_ItemId;
  "sequenceNumber": Record_Properties_Items_Items_Properties_SequenceNumber;
  "description": Record_Properties_Items_Items_Properties_Description;
  "code"?: Record_Properties_Items_Items_Properties_Code;
  "occurredAt": Record_Properties_Items_Items_Properties_OccurredAt;
  "severity": Record_Properties_Items_Items_Properties_Severity;
  "resolution"?: Record_Properties_Items_Items_Properties_Resolution;
  "resolvedAt"?: Record_Properties_Items_Items_Properties_ResolvedAt;
  "outcome"?: Record_Properties_Items_Items_Properties_Outcome;
  "remarks"?: Record_Properties_Items_Items_Properties_Remarks;
  "category"?: Record_Properties_Items_Items_Properties_Category;
  "subCategory"?: Record_Properties_Items_Items_Properties_SubCategory;
  "meta"?: Record_Properties_Items_Items_Properties_Meta;
}

export type Record_Properties_Items = Record_Properties_Items_Items[];

export type Record_Properties_Entity_Properties_Locations_Items = Record_X24Defs_ULocation;

export type Record_Properties_Entity_Properties_Locations = Record_Properties_Entity_Properties_Locations_Items[];

export type Record_Properties_Entity_Properties_FullName = Record_X24Defs_UFullName;

export type Record_Properties_Entity_Properties_Classification = string;

export type Record_Properties_Entity_Properties_Category = string;

export type Record_Properties_Entity_Properties_BirthDate = Record_X24Defs_UTimestamp;

export type Record_Properties_Entity_AdditionalProperties = never;

export interface Record_Properties_Entity {
  "fullName": Record_Properties_Entity_Properties_FullName;
  "birthDate": Record_Properties_Entity_Properties_BirthDate;
  "category"?: Record_Properties_Entity_Properties_Category;
  "classification"?: Record_Properties_Entity_Properties_Classification;
  "locations": Record_Properties_Entity_Properties_Locations;
}

export type Record_Properties_CreatedAt = Record_X24Defs_UTimestamp;

export type Record_AdditionalProperties = never;

export type Record_X24Defs_UTimestamp_Properties_Year = number;

export type Record_X24Defs_UTimestamp_Properties_RawValue = string;

export type Record_X24Defs_UTimestamp_Properties_Month = number;

export type Record_X24Defs_UTimestamp_Properties_IsoFormat = string;

export type Record_X24Defs_UTimestamp_Properties_Day = number;

export type Record_X24Defs_UTimestamp_AdditionalProperties = never;

export interface Record_X24Defs_UTimestamp {
  "rawValue": Record_X24Defs_UTimestamp_Properties_RawValue;
  "year": Record_X24Defs_UTimestamp_Properties_Year;
  "month": Record_X24Defs_UTimestamp_Properties_Month;
  "day": Record_X24Defs_UTimestamp_Properties_Day;
  "isoFormat"?: Record_X24Defs_UTimestamp_Properties_IsoFormat;
}

export type Record_X24Defs_ULocation_Properties_Region = string;

export type Record_X24Defs_ULocation_Properties_RawValue = string;

export type Record_X24Defs_ULocation_Properties_PostalCode = string;

export type Record_X24Defs_ULocation_Properties_Line2_AnyOf_ZIndex1 = null;

export type Record_X24Defs_ULocation_Properties_Line2_AnyOf_ZIndex0 = string;

export type Record_X24Defs_ULocation_Properties_Line2 =
  Record_X24Defs_ULocation_Properties_Line2_AnyOf_ZIndex0 |
  Record_X24Defs_ULocation_Properties_Line2_AnyOf_ZIndex1;

export type Record_X24Defs_ULocation_Properties_Line1 = string;

export type Record_X24Defs_ULocation_Properties_District = string;

export type Record_X24Defs_ULocation_Properties_Country = string;

export type Record_X24Defs_ULocation_Properties_City = string;

export type Record_X24Defs_ULocation_AdditionalProperties = never;

export interface Record_X24Defs_ULocation {
  "rawValue": Record_X24Defs_ULocation_Properties_RawValue;
  "line1": Record_X24Defs_ULocation_Properties_Line1;
  "line2"?: Record_X24Defs_ULocation_Properties_Line2;
  "city": Record_X24Defs_ULocation_Properties_City;
  "district"?: Record_X24Defs_ULocation_Properties_District;
  "region": Record_X24Defs_ULocation_Properties_Region;
  "postalCode": Record_X24Defs_ULocation_Properties_PostalCode;
  "country": Record_X24Defs_ULocation_Properties_Country;
}

export type Record_X24Defs_UFullName_Properties_Suffix_AnyOf_ZIndex1 = null;

export type Record_X24Defs_UFullName_Properties_Suffix_AnyOf_ZIndex0 = string;

export type Record_X24Defs_UFullName_Properties_Suffix =
  Record_X24Defs_UFullName_Properties_Suffix_AnyOf_ZIndex0 |
  Record_X24Defs_UFullName_Properties_Suffix_AnyOf_ZIndex1;

export type Record_X24Defs_UFullName_Properties_RawValue = string;

export type Record_X24Defs_UFullName_Properties_Prefix_AnyOf_ZIndex1 = null;

export type Record_X24Defs_UFullName_Properties_Prefix_AnyOf_ZIndex0 = string;

export type Record_X24Defs_UFullName_Properties_Prefix =
  Record_X24Defs_UFullName_Properties_Prefix_AnyOf_ZIndex0 |
  Record_X24Defs_UFullName_Properties_Prefix_AnyOf_ZIndex1;

export type Record_X24Defs_UFullName_Properties_MiddleName_AnyOf_ZIndex1 = null;

export type Record_X24Defs_UFullName_Properties_MiddleName_AnyOf_ZIndex0 = string;

export type Record_X24Defs_UFullName_Properties_MiddleName =
  Record_X24Defs_UFullName_Properties_MiddleName_AnyOf_ZIndex0 |
  Record_X24Defs_UFullName_Properties_MiddleName_AnyOf_ZIndex1;

export type Record_X24Defs_UFullName_Properties_GivenName = string;

export type Record_X24Defs_UFullName_Properties_FamilyName = string;

export type Record_X24Defs_UFullName_AdditionalProperties = never;

export interface Record_X24Defs_UFullName {
  "rawValue"?: Record_X24Defs_UFullName_Properties_RawValue;
  "givenName": Record_X24Defs_UFullName_Properties_GivenName;
  "middleName"?: Record_X24Defs_UFullName_Properties_MiddleName;
  "familyName": Record_X24Defs_UFullName_Properties_FamilyName;
  "suffix"?: Record_X24Defs_UFullName_Properties_Suffix;
  "prefix"?: Record_X24Defs_UFullName_Properties_Prefix;
}

export interface Record {
  "recordId": Record_Properties_RecordId;
  "referenceCode"?: Record_Properties_ReferenceCode;
  "organizationName": Record_Properties_OrganizationName;
  "createdAt"?: Record_Properties_CreatedAt;
  "region": Record_Properties_Region;
  "locationInfo"?: Record_Properties_LocationInfo;
  "entity": Record_Properties_Entity;
  "notes"?: Record_Properties_Notes;
  "items": Record_Properties_Items;
  "meta"?: Record_Properties_Meta;
}
