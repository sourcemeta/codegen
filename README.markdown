Codegen
=======

- Each input schema corresponds to a single `.d.ts` file
- 100% structurally map to TypeScript. Additional constraints might belong to
  validation

| Vocabulary | Keyword | Support |
|------------|---------|---------|
| Core | `$schema` | Yes |
| Core | `$id` | Yes |
| Core | `$ref` | Yes |
| Core | `$defs` | Yes |
| Core | `$anchor` | No |
| Core | `$dynamicAnchor` | No (TODO: Simplify in canonicalisation) |
| Core | `$dynamicRef` | No (TODO: Simplify in canonicalisation) |
| Core | `$vocabulary` | Ignored |
| Core | `$comment` | Ignored |
| Applicator | `properties` | Yes |
| Applicator | `additionalProperties` | Yes |
| Applicator | `items` | Yes |
| Applicator | `prefixItems` | Yes |
| Applicator | `anyOf` | Yes |
| Applicator | `patternProperties` | CANNOT SUPPORT IN MOST LANGUAGES |
| Applicator | `propertyNames` | Ignored |
| Applicator | `dependentSchemas` | No (TODO: Simplify in canonicalisation) |
| Applicator | `contains` | Ignored |
| Applicator | `allOf` | No (TODO: Simplify in canonicalisation) |
| Applicator | `oneOf` | CANNOT SUPPORT IN MOST LANGUAGES |
| Applicator | `not` | CANNOT SUPPORT IN MOST LANGUAGES |
| Applicator | `if` | No (TODO: Simplify in canonicalisation) |
| Applicator | `then` | No (TODO: Simplify in canonicalisation) |
| Applicator | `else` | No (TODO: Simplify in canonicalisation) |
| Validation | `type` | Yes |
| Validation | `enum` | Yes |
| Validation | `required` | Yes |
| Validation | `const` | Yes |
| Validation | `minLength` | Ignored |
| Validation | `maxLength` | Ignored |
| Validation | `pattern` | Ignored |
| Validation | `minimum` | Ignored |
| Validation | `maximum` | Ignored |
| Validation | `exclusiveMinimum` | Ignored |
| Validation | `exclusiveMaximum` | Ignored |
| Validation | `multipleOf` | Ignored |
| Validation | `minProperties` | Ignored |
| Validation | `maxProperties` | Ignored |
| Validation | `dependentRequired` | No (TODO: Simplify in canonicalisation) |
| Validation | `minItems` | Ignored |
| Validation | `maxItems` | Ignored |
| Validation | `minContains` | Ignored |
| Validation | `maxContains` | Ignored |
| Validation | `uniqueItems` | Ignored |
| Unevaluated | `unevaluatedItems` | No (TODO: Simplify in canonicalisation) |
| Unevaluated | `unevaluatedProperties` | No (TODO: Simplify in canonicalisation) |
| Meta-Data | `title` | Ignored |
| Meta-Data | `description` | Ignored |
| Meta-Data | `default` | Ignored |
| Meta-Data | `deprecated` | Ignored |
| Meta-Data | `examples` | Ignored |
| Meta-Data | `readOnly` | Ignored |
| Meta-Data | `writeOnly` | Ignored |
| Format Annotation | `format` | Ignored |
| Format Assertion | `format` | Ignored |
| Content | `contentEncoding` | Ignored |
| Content | `contentMediaType` | Ignored |
| Content | `contentSchema` | Ignored |
