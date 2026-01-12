export type Person_Properties_Name = string;

export type Person_Properties_Age = number;

export type Person_AdditionalProperties = string;

export interface Person {
  "name": Person_Properties_Name;
  "age"?: Person_Properties_Age;
  [key: string]:
    Person_Properties_Name |
    Person_Properties_Age |
    Person_AdditionalProperties |
    undefined;
}
