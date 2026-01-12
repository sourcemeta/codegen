import {
  AllTypes,
  AllTypes_Properties_ObjectField,
  AllTypes_Properties_NestedTypes,
  AllTypes_Properties_MultiType,
  AllTypes_Properties_ArrayField
} from "./expected";

const minimal: AllTypes = {
  stringField: "hello",
  numberField: 3.14,
  integerField: 42,
  booleanField: true,
  nullField: null,
  arrayField: [ "a", "b", "c" ],
  objectField: {}
};

const complete: AllTypes = {
  stringField: "hello",
  numberField: -123.456,
  integerField: 0,
  booleanField: false,
  nullField: null,
  arrayField: [],
  objectField: { nested: "value" },
  multiType: "string value",
  nestedTypes: {
    deepBoolean: true,
    deepNull: null,
    deepInteger: 100
  }
};

const multiTypeString: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  multiType: "hello world"
};

const multiTypeNumber: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  multiType: 42.5
};

const multiTypeNull: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  multiType: null
};

const invalidStringField: AllTypes = {
  // @ts-expect-error
  stringField: 123,
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {}
};

const invalidNumberField: AllTypes = {
  stringField: "test",
  // @ts-expect-error
  numberField: "3.14",
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {}
};

const invalidIntegerField: AllTypes = {
  stringField: "test",
  numberField: 1,
  // @ts-expect-error
  integerField: "42",
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {}
};

const invalidBooleanField: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  // @ts-expect-error
  booleanField: "true",
  nullField: null,
  arrayField: [],
  objectField: {}
};

const invalidNullFieldString: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  // @ts-expect-error
  nullField: "not null",
  arrayField: [],
  objectField: {}
};

const invalidNullFieldUndefined: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  // @ts-expect-error
  nullField: undefined,
  arrayField: [],
  objectField: {}
};

const invalidArrayItems: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  // @ts-expect-error
  arrayField: [ 1, 2, 3 ],
  objectField: {}
};

// @ts-expect-error
const missingRequired: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: []
};

const invalidMultiType: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  // @ts-expect-error
  multiType: true
};

const invalidMultiTypeArray: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  // @ts-expect-error
  multiType: [ 1, 2, 3 ]
};

const invalidObjectFieldExtra: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {
    nested: "ok",
    // @ts-expect-error
    extra: "not allowed"
  }
};

const invalidObjectFieldType: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {
    // @ts-expect-error
    nested: 123
  }
};

const invalidNestedTypesExtra: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  nestedTypes: {
    deepBoolean: true,
    // @ts-expect-error
    extra: "not allowed"
  }
};

const invalidNestedTypesBoolean: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  nestedTypes: {
    // @ts-expect-error
    deepBoolean: "yes"
  }
};

const invalidNestedTypesNull: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  nestedTypes: {
    // @ts-expect-error
    deepNull: "null"
  }
};

const invalidNestedTypesInteger: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  nestedTypes: {
    // @ts-expect-error
    deepInteger: "100"
  }
};

const invalidRootExtra: AllTypes = {
  stringField: "test",
  numberField: 1,
  integerField: 1,
  booleanField: true,
  nullField: null,
  arrayField: [],
  objectField: {},
  // @ts-expect-error
  unknownField: "not allowed"
};

const arrayField: AllTypes_Properties_ArrayField = [ "a", "b" ];
// @ts-expect-error
const invalidArrayFieldType: AllTypes_Properties_ArrayField = [ 1, 2 ];

const multiType1: AllTypes_Properties_MultiType = "string";
const multiType2: AllTypes_Properties_MultiType = 42;
const multiType3: AllTypes_Properties_MultiType = null;
// @ts-expect-error
const invalidMultiTypeStandalone: AllTypes_Properties_MultiType = true;

const objectField: AllTypes_Properties_ObjectField = {};
const objectField2: AllTypes_Properties_ObjectField = { nested: "value" };
// @ts-expect-error
const invalidObjectFieldStandalone: AllTypes_Properties_ObjectField = { nested: 123 };

const nestedTypes: AllTypes_Properties_NestedTypes = {};
const nestedTypes2: AllTypes_Properties_NestedTypes = { deepBoolean: false, deepNull: null, deepInteger: 50 };
// @ts-expect-error
const invalidNestedTypesStandalone: AllTypes_Properties_NestedTypes = { deepBoolean: "yes" };
