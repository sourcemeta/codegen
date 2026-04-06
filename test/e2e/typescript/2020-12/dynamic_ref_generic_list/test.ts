import { StringList } from "./expected";

// The generic list has an unconstrained default anchor (accepts anything)
// plus a string anchor. The union includes all types, so anything goes.
const strings: StringList = [ "hello", "world" ];

const numbers: StringList = [ 1, 2, 3 ];

const mixed: StringList = [ "hello", 42, true, null ];

const empty: StringList = [];

// @ts-expect-error
const notArray: StringList = "hello";
