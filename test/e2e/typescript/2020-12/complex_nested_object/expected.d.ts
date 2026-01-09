export type Record_Properties_Region = string;

export type Record_Properties_ReferenceCode = string;

export type Record_Properties_RecordId = string;

export type Record_Properties_OrganizationName = string;

export type Record_Properties_Notes = string;

export type Record_Properties_Meta_Properties_OriginId = string;

export type Record_Properties_Meta_Properties_Origin = string;

export type Record_Properties_Meta_AdditionalProperties = never;

export type Record_Properties_Meta = {
  "originId"?: Record_Properties_Meta_Properties_OriginId;
  "origin"?: Record_Properties_Meta_Properties_Origin
} & {
  [K in string as K extends
    "originId" |
    "origin"
  ? never : K]: Record_Properties_Meta_AdditionalProperties;
};

export type Record_Properties_LocationInfo_Properties_StateCode = string;

export type Record_Properties_LocationInfo_Properties_AreaCode = string;

export type Record_Properties_LocationInfo_AdditionalProperties = never;

export type Record_Properties_LocationInfo = {
  "areaCode"?: Record_Properties_LocationInfo_Properties_AreaCode;
  "stateCode"?: Record_Properties_LocationInfo_Properties_StateCode
} & {
  [K in string as K extends
    "areaCode" |
    "stateCode"
  ? never : K]: Record_Properties_LocationInfo_AdditionalProperties;
};

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

export type Record_Properties_Items_Items_Properties_Meta = {
  "originId"?: Record_Properties_Items_Items_Properties_Meta_Properties_OriginId;
  "origin"?: Record_Properties_Items_Items_Properties_Meta_Properties_Origin
} & {
  [K in string as K extends
    "originId" |
    "origin"
  ? never : K]: Record_Properties_Items_Items_Properties_Meta_AdditionalProperties;
};

export type Record_Properties_Items_Items_Properties_ItemId = string;

export type Record_Properties_Items_Items_Properties_Description = string;

export type Record_Properties_Items_Items_Properties_Code_AnyOf_ZIndex1 = null;

export type Record_Properties_Items_Items_Properties_Code_AnyOf_ZIndex0 = string;

export type Record_Properties_Items_Items_Properties_Code =
  Record_Properties_Items_Items_Properties_Code_AnyOf_ZIndex0 |
  Record_Properties_Items_Items_Properties_Code_AnyOf_ZIndex1;

export type Record_Properties_Items_Items_Properties_Category = string;

export type Record_Properties_Items_Items_AdditionalProperties = never;

export type Record_Properties_Items_Items = {
  "subCategory"?: Record_Properties_Items_Items_Properties_SubCategory;
  "remarks"?: Record_Properties_Items_Items_Properties_Remarks;
  "category"?: Record_Properties_Items_Items_Properties_Category;
  "occurredAt": Record_Properties_Items_Items_Properties_OccurredAt;
  "outcome"?: Record_Properties_Items_Items_Properties_Outcome;
  "resolvedAt"?: Record_Properties_Items_Items_Properties_ResolvedAt;
  "meta"?: Record_Properties_Items_Items_Properties_Meta;
  "code"?: Record_Properties_Items_Items_Properties_Code;
  "severity": Record_Properties_Items_Items_Properties_Severity;
  "description": Record_Properties_Items_Items_Properties_Description;
  "sequenceNumber": Record_Properties_Items_Items_Properties_SequenceNumber;
  "resolution"?: Record_Properties_Items_Items_Properties_Resolution;
  "itemId": Record_Properties_Items_Items_Properties_ItemId
} & {
  [K in string as K extends
    "subCategory" |
    "remarks" |
    "category" |
    "occurredAt" |
    "outcome" |
    "resolvedAt" |
    "meta" |
    "code" |
    "severity" |
    "description" |
    "sequenceNumber" |
    "resolution" |
    "itemId"
  ? never : K]: Record_Properties_Items_Items_AdditionalProperties;
};

export type Record_Properties_Items = Record_Properties_Items_Items[];

export type Record_Properties_Entity_Properties_Locations_Items = Record_X24Defs_ULocation;

export type Record_Properties_Entity_Properties_Locations = Record_Properties_Entity_Properties_Locations_Items[];

export type Record_Properties_Entity_Properties_FullName = Record_X24Defs_UFullName;

export type Record_Properties_Entity_Properties_Classification = string;

export type Record_Properties_Entity_Properties_Category = string;

export type Record_Properties_Entity_Properties_BirthDate = Record_X24Defs_UTimestamp;

export type Record_Properties_Entity_AdditionalProperties = never;

export type Record_Properties_Entity = {
  "category"?: Record_Properties_Entity_Properties_Category;
  "classification"?: Record_Properties_Entity_Properties_Classification;
  "birthDate": Record_Properties_Entity_Properties_BirthDate;
  "locations": Record_Properties_Entity_Properties_Locations;
  "fullName": Record_Properties_Entity_Properties_FullName
} & {
  [K in string as K extends
    "category" |
    "classification" |
    "birthDate" |
    "locations" |
    "fullName"
  ? never : K]: Record_Properties_Entity_AdditionalProperties;
};

export type Record_Properties_CreatedAt = Record_X24Defs_UTimestamp;

export type Record_AdditionalProperties = never;

export type Record_X24Defs_UTimestamp_Properties_Year = number;

export type Record_X24Defs_UTimestamp_Properties_RawValue = string;

export type Record_X24Defs_UTimestamp_Properties_Month = number;

export type Record_X24Defs_UTimestamp_Properties_IsoFormat = string;

export type Record_X24Defs_UTimestamp_Properties_Day = number;

export type Record_X24Defs_UTimestamp_AdditionalProperties = never;

export type Record_X24Defs_UTimestamp = {
  "day": Record_X24Defs_UTimestamp_Properties_Day;
  "month": Record_X24Defs_UTimestamp_Properties_Month;
  "isoFormat"?: Record_X24Defs_UTimestamp_Properties_IsoFormat;
  "year": Record_X24Defs_UTimestamp_Properties_Year;
  "rawValue": Record_X24Defs_UTimestamp_Properties_RawValue
} & {
  [K in string as K extends
    "day" |
    "month" |
    "isoFormat" |
    "year" |
    "rawValue"
  ? never : K]: Record_X24Defs_UTimestamp_AdditionalProperties;
};

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

export type Record_X24Defs_ULocation = {
  "country": Record_X24Defs_ULocation_Properties_Country;
  "city": Record_X24Defs_ULocation_Properties_City;
  "district"?: Record_X24Defs_ULocation_Properties_District;
  "line2"?: Record_X24Defs_ULocation_Properties_Line2;
  "region": Record_X24Defs_ULocation_Properties_Region;
  "line1": Record_X24Defs_ULocation_Properties_Line1;
  "postalCode": Record_X24Defs_ULocation_Properties_PostalCode;
  "rawValue": Record_X24Defs_ULocation_Properties_RawValue
} & {
  [K in string as K extends
    "country" |
    "city" |
    "district" |
    "line2" |
    "region" |
    "line1" |
    "postalCode" |
    "rawValue"
  ? never : K]: Record_X24Defs_ULocation_AdditionalProperties;
};

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

export type Record_X24Defs_UFullName = {
  "middleName"?: Record_X24Defs_UFullName_Properties_MiddleName;
  "suffix"?: Record_X24Defs_UFullName_Properties_Suffix;
  "familyName": Record_X24Defs_UFullName_Properties_FamilyName;
  "prefix"?: Record_X24Defs_UFullName_Properties_Prefix;
  "givenName": Record_X24Defs_UFullName_Properties_GivenName;
  "rawValue"?: Record_X24Defs_UFullName_Properties_RawValue
} & {
  [K in string as K extends
    "middleName" |
    "suffix" |
    "familyName" |
    "prefix" |
    "givenName" |
    "rawValue"
  ? never : K]: Record_X24Defs_UFullName_AdditionalProperties;
};

export type Record = {
  "items": Record_Properties_Items;
  "entity": Record_Properties_Entity;
  "region": Record_Properties_Region;
  "createdAt"?: Record_Properties_CreatedAt;
  "organizationName": Record_Properties_OrganizationName;
  "meta"?: Record_Properties_Meta;
  "locationInfo"?: Record_Properties_LocationInfo;
  "referenceCode"?: Record_Properties_ReferenceCode;
  "notes"?: Record_Properties_Notes;
  "recordId": Record_Properties_RecordId
} & {
  [K in string as K extends
    "items" |
    "entity" |
    "region" |
    "createdAt" |
    "organizationName" |
    "meta" |
    "locationInfo" |
    "referenceCode" |
    "notes" |
    "recordId"
  ? never : K]: Record_AdditionalProperties;
};
