import { Root } from "./expected";

// At runtime, the dynamic ref resolves to either string or number depending
// on the evaluation path. The codegen emits a union of all possible targets.
const strings: Root = [ "hello", "world" ];

const numbers: Root = [ 1, 2, 3 ];

const mixed: Root = [ "hello", 42 ];

const empty: Root = [];

// @ts-expect-error
const notArray: Root = "hello";

// Boolean is not in the union (string | number)
// @ts-expect-error
const invalidItem: Root = [ true ];
