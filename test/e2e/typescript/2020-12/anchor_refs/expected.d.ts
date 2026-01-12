export type ColorScheme_Properties_Secondary = ColorScheme_X24Defs_UColor;

export type ColorScheme_Properties_Primary = ColorScheme_X24Defs_UColor;

export type ColorScheme_Properties_Background = ColorScheme_X24Defs_UColor;

export type ColorScheme_AdditionalProperties = never;

export type ColorScheme_X24Defs_UColor_Properties_R = number;

export type ColorScheme_X24Defs_UColor_Properties_G = number;

export type ColorScheme_X24Defs_UColor_Properties_B = number;

export type ColorScheme_X24Defs_UColor_Properties_Alpha = number;

export type ColorScheme_X24Defs_UColor_AdditionalProperties = never;

export interface ColorScheme_X24Defs_UColor {
  "r": ColorScheme_X24Defs_UColor_Properties_R;
  "g": ColorScheme_X24Defs_UColor_Properties_G;
  "b": ColorScheme_X24Defs_UColor_Properties_B;
  "alpha"?: ColorScheme_X24Defs_UColor_Properties_Alpha;
}

export interface ColorScheme {
  "primary": ColorScheme_Properties_Primary;
  "secondary": ColorScheme_Properties_Secondary;
  "background"?: ColorScheme_Properties_Background;
}
