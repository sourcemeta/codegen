import { DocumentSystem, DocumentSystem_X24Defs_UItem } from "./expected";


// Valid: minimal
const valid: DocumentSystem = {
  item: { name: "test item" }
};

// Invalid: missing required item
// @ts-expect-error
const missingItem: DocumentSystem = {};

// Invalid: item missing required name
const missingName: DocumentSystem = {
  // @ts-expect-error
  item: {}
};

// Invalid: item name must be string
const invalidName: DocumentSystem = {
  item: {
    // @ts-expect-error
    name: 123
  }
};

// Invalid: extra property on item (additionalProperties: false)
const invalidItemExtra: DocumentSystem = {
  item: {
    name: "test",
    // @ts-expect-error
    description: "not allowed"
  }
};

// Invalid: extra property on root (additionalProperties: false)
const invalidRootExtra: DocumentSystem = {
  item: { name: "test" },
  // @ts-expect-error
  extra: "not allowed"
};

// Test standalone Item type
const validItem: DocumentSystem_X24Defs_UItem = { name: "standalone" };
// @ts-expect-error
const invalidItem: DocumentSystem_X24Defs_UItem = { name: 123 };
