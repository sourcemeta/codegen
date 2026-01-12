export type StrictPerson_Properties_Name = string;

export type StrictPerson_Properties_Age = number;

export type StrictPerson_AdditionalProperties = never;

export interface StrictPerson {
  "name": StrictPerson_Properties_Name;
  "age"?: StrictPerson_Properties_Age;
}
