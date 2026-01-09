# JSON Schema Codegen

> Generate type definitions from JSON Schema for multiple programming languages

Existing tools in this space typically support limited subsets of JSON Schema
with varying compliance levels. This project, maintained by a member of the
[JSON Schema Technical Steering Committee](https://github.com/jviotti),
prioritizes specification compliance and comprehensive keyword coverage.

## Keyword Support

Not every JSON Schema keyword maps directly to type system constructs. This
implementation aims to provide complete structural typing, and you are expected
to use a JSON Schema validator at runtime to enforce remaining constraints.

| Vocabulary | Keyword | TypeScript |
|------------|---------|------------|
| Core (2020-12) | `$schema` | Yes |
| Core (2020-12) | `$id` | Yes |
| Core (2020-12) | `$ref` | Yes |
| Core (2020-12) | `$defs` | Yes |
| Core (2020-12) | `$anchor` | Yes |
| Core (2020-12) | `$dynamicAnchor` | Pending |
| Core (2020-12) | `$dynamicRef` | Pending |
| Core (2020-12) | `$vocabulary` | Ignored |
| Core (2020-12) | `$comment` | Ignored |
| Applicator (2020-12) | `properties` | Yes |
| Applicator (2020-12) | `additionalProperties` | Yes |
| Applicator (2020-12) | `items` | Yes |
| Applicator (2020-12) | `prefixItems` | Yes |
| Applicator (2020-12) | `anyOf` | Yes |
| Applicator (2020-12) | `patternProperties` | **CANNOT SUPPORT** |
| Applicator (2020-12) | `propertyNames` | Ignored |
| Applicator (2020-12) | `dependentSchemas` | Pending |
| Applicator (2020-12) | `contains` | Ignored |
| Applicator (2020-12) | `allOf` | Pending |
| Applicator (2020-12) | `oneOf` | **CANNOT SUPPORT** |
| Applicator (2020-12) | `not` | **CANNOT SUPPORT** |
| Applicator (2020-12) | `if` | Pending |
| Applicator (2020-12) | `then` | Pending |
| Applicator (2020-12) | `else` | Pending |
| Validation (2020-12) | `type` | Yes |
| Validation (2020-12) | `enum` | Yes |
| Validation (2020-12) | `required` | Yes |
| Validation (2020-12) | `const` | Yes |
| Validation (2020-12) | `minLength` | Ignored |
| Validation (2020-12) | `maxLength` | Ignored |
| Validation (2020-12) | `pattern` | Ignored |
| Validation (2020-12) | `minimum` | Ignored |
| Validation (2020-12) | `maximum` | Ignored |
| Validation (2020-12) | `exclusiveMinimum` | Ignored |
| Validation (2020-12) | `exclusiveMaximum` | Ignored |
| Validation (2020-12) | `multipleOf` | Ignored |
| Validation (2020-12) | `minProperties` | Ignored |
| Validation (2020-12) | `maxProperties` | Ignored |
| Validation (2020-12) | `dependentRequired` | Pending |
| Validation (2020-12) | `minItems` | Ignored |
| Validation (2020-12) | `maxItems` | Ignored |
| Validation (2020-12) | `minContains` | Ignored |
| Validation (2020-12) | `maxContains` | Ignored |
| Validation (2020-12) | `uniqueItems` | Ignored |
| Unevaluated (2020-12) | `unevaluatedItems` | Pending |
| Unevaluated (2020-12) | `unevaluatedProperties` | Pending |
| Meta-Data (2020-12) | `title` | Ignored |
| Meta-Data (2020-12) | `description` | Ignored |
| Meta-Data (2020-12) | `default` | Ignored |
| Meta-Data (2020-12) | `deprecated` | Ignored |
| Meta-Data (2020-12) | `examples` | Ignored |
| Meta-Data (2020-12) | `readOnly` | Ignored |
| Meta-Data (2020-12) | `writeOnly` | Ignored |
| Format Annotation (2020-12) | `format` | Ignored |
| Format Assertion (2020-12) | `format` | Ignored |
| Content (2020-12) | `contentEncoding` | Ignored |
| Content (2020-12) | `contentMediaType` | Ignored |
| Content (2020-12) | `contentSchema` | Ignored |

Support for other JSON Schema dialects coming soon.
