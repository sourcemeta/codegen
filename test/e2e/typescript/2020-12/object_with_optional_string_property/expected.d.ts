export type MyObject_Properties_Foo = string;

export interface MyObject {
  "foo"?: MyObject_Properties_Foo;
  [key: string]: unknown | undefined;
}
