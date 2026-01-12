import { Person } from "./expected";

const person: Person = {
  name: "John Doe"
};

const invalidPerson: Person = {
  // @ts-expect-error
  name: 123
};
