export type Person_Properties_Name = string;

export type Person_Properties_Age = number;

export type Person_AdditionalProperties = string;

export type Person = {
  "age"?: Person_Properties_Age;
  "name": Person_Properties_Name
} & {
  [K in string as K extends
    "age" |
    "name"
  ? never : K]: Person_AdditionalProperties;
};
