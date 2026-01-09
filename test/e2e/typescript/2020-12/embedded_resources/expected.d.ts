export type DocumentSystem_Properties_Item = DocumentSystem_X24Defs_UItem;

export type DocumentSystem_AdditionalProperties = never;

export type DocumentSystem_X24Defs_UItem_Properties_Name = string;

export type DocumentSystem_X24Defs_UItem_AdditionalProperties = never;

export type DocumentSystem_X24Defs_UItem = {
  "name": DocumentSystem_X24Defs_UItem_Properties_Name;
} & {
  [K in string as K extends
    "name"
  ? never : K]: DocumentSystem_X24Defs_UItem_AdditionalProperties;
};

export type DocumentSystem = {
  "item": DocumentSystem_Properties_Item;
} & {
  [K in string as K extends
    "item"
  ? never : K]: DocumentSystem_AdditionalProperties;
};
