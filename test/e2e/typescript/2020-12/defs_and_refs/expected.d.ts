export type SocialPlatform_Properties_X75ser = SocialPlatform_X24Defs_X55ser;

export type SocialPlatform_Properties_Settings = SocialPlatform_X24Defs_USettings;

export type SocialPlatform_Properties_Posts_Items = SocialPlatform_X24Defs_UPost;

export type SocialPlatform_Properties_Posts = SocialPlatform_Properties_Posts_Items[];

export type SocialPlatform_Properties_PinnedPost_AnyOf_ZIndex1 = null;

export type SocialPlatform_Properties_PinnedPost_AnyOf_ZIndex0 = SocialPlatform_X24Defs_UPost;

export type SocialPlatform_Properties_PinnedPost =
  SocialPlatform_Properties_PinnedPost_AnyOf_ZIndex0 |
  SocialPlatform_Properties_PinnedPost_AnyOf_ZIndex1;

export type SocialPlatform_Properties_Followers_Items = SocialPlatform_X24Defs_X55ser;

export type SocialPlatform_Properties_Followers = SocialPlatform_Properties_Followers_Items[];

export type SocialPlatform_AdditionalProperties = never;

export type SocialPlatform_X24Defs_X55ser_Properties_X75sername = string;

export type SocialPlatform_X24Defs_X55ser_Properties_Profile = SocialPlatform_X24Defs_UProfile;

export type SocialPlatform_X24Defs_X55ser_Properties_Id = SocialPlatform_X24Defs_X55X55ID;

export type SocialPlatform_X24Defs_X55ser_Properties_Email = SocialPlatform_X24Defs_UEmail;

export type SocialPlatform_X24Defs_X55ser_AdditionalProperties = never;

export interface SocialPlatform_X24Defs_X55ser {
  "id": SocialPlatform_X24Defs_X55ser_Properties_Id;
  "username": SocialPlatform_X24Defs_X55ser_Properties_X75sername;
  "email": SocialPlatform_X24Defs_X55ser_Properties_Email;
  "profile"?: SocialPlatform_X24Defs_X55ser_Properties_Profile;
}

export type SocialPlatform_X24Defs_X55X55ID = string;

export type SocialPlatform_X24Defs_X55RL = string;

export type SocialPlatform_X24Defs_UTheme = "light" | "dark" | "system";

export type SocialPlatform_X24Defs_UTag_Properties_Slug = string;

export type SocialPlatform_X24Defs_UTag_Properties_Name = string;

export type SocialPlatform_X24Defs_UTag_AdditionalProperties = never;

export interface SocialPlatform_X24Defs_UTag {
  "name": SocialPlatform_X24Defs_UTag_Properties_Name;
  "slug"?: SocialPlatform_X24Defs_UTag_Properties_Slug;
}

export type SocialPlatform_X24Defs_USettings_Properties_Theme = SocialPlatform_X24Defs_UTheme;

export type SocialPlatform_X24Defs_USettings_Properties_Privacy = SocialPlatform_X24Defs_UPrivacySettings;

export type SocialPlatform_X24Defs_USettings_Properties_Notifications = SocialPlatform_X24Defs_UNotificationSettings;

export type SocialPlatform_X24Defs_USettings_AdditionalProperties = never;

export interface SocialPlatform_X24Defs_USettings {
  "theme"?: SocialPlatform_X24Defs_USettings_Properties_Theme;
  "notifications"?: SocialPlatform_X24Defs_USettings_Properties_Notifications;
  "privacy"?: SocialPlatform_X24Defs_USettings_Properties_Privacy;
}

export type SocialPlatform_X24Defs_UProfile_Properties_Location_AnyOf_ZIndex1 = null;

export type SocialPlatform_X24Defs_UProfile_Properties_Location_AnyOf_ZIndex0 = string;

export type SocialPlatform_X24Defs_UProfile_Properties_Location =
  SocialPlatform_X24Defs_UProfile_Properties_Location_AnyOf_ZIndex0 |
  SocialPlatform_X24Defs_UProfile_Properties_Location_AnyOf_ZIndex1;

export type SocialPlatform_X24Defs_UProfile_Properties_Bio_AnyOf_ZIndex1 = null;

export type SocialPlatform_X24Defs_UProfile_Properties_Bio_AnyOf_ZIndex0 = string;

export type SocialPlatform_X24Defs_UProfile_Properties_Bio =
  SocialPlatform_X24Defs_UProfile_Properties_Bio_AnyOf_ZIndex0 |
  SocialPlatform_X24Defs_UProfile_Properties_Bio_AnyOf_ZIndex1;

export type SocialPlatform_X24Defs_UProfile_Properties_Avatar = SocialPlatform_X24Defs_X55RL;

export type SocialPlatform_X24Defs_UProfile_AdditionalProperties = never;

export interface SocialPlatform_X24Defs_UProfile {
  "bio"?: SocialPlatform_X24Defs_UProfile_Properties_Bio;
  "avatar"?: SocialPlatform_X24Defs_UProfile_Properties_Avatar;
  "location"?: SocialPlatform_X24Defs_UProfile_Properties_Location;
}

export type SocialPlatform_X24Defs_UPrivacySettings_Properties_ShowEmail = boolean;

export type SocialPlatform_X24Defs_UPrivacySettings_Properties_ProfileVisible = boolean;

export type SocialPlatform_X24Defs_UPrivacySettings_AdditionalProperties = never;

export interface SocialPlatform_X24Defs_UPrivacySettings {
  "profileVisible"?: SocialPlatform_X24Defs_UPrivacySettings_Properties_ProfileVisible;
  "showEmail"?: SocialPlatform_X24Defs_UPrivacySettings_Properties_ShowEmail;
}

export type SocialPlatform_X24Defs_UPostStatus = "draft" | "published" | "archived";

export type SocialPlatform_X24Defs_UPost_Properties_Title = string;

export type SocialPlatform_X24Defs_UPost_Properties_Tags_Items = SocialPlatform_X24Defs_UTag;

export type SocialPlatform_X24Defs_UPost_Properties_Tags = SocialPlatform_X24Defs_UPost_Properties_Tags_Items[];

export type SocialPlatform_X24Defs_UPost_Properties_Status = SocialPlatform_X24Defs_UPostStatus;

export type SocialPlatform_X24Defs_UPost_Properties_Id = SocialPlatform_X24Defs_X55X55ID;

export type SocialPlatform_X24Defs_UPost_Properties_Content = string;

export type SocialPlatform_X24Defs_UPost_Properties_Author = SocialPlatform_X24Defs_X55ser;

export type SocialPlatform_X24Defs_UPost_AdditionalProperties = never;

export interface SocialPlatform_X24Defs_UPost {
  "id": SocialPlatform_X24Defs_UPost_Properties_Id;
  "title": SocialPlatform_X24Defs_UPost_Properties_Title;
  "content"?: SocialPlatform_X24Defs_UPost_Properties_Content;
  "author": SocialPlatform_X24Defs_UPost_Properties_Author;
  "tags"?: SocialPlatform_X24Defs_UPost_Properties_Tags;
  "status"?: SocialPlatform_X24Defs_UPost_Properties_Status;
}

export type SocialPlatform_X24Defs_UNotificationSettings_Properties_Sms = boolean;

export type SocialPlatform_X24Defs_UNotificationSettings_Properties_Push = boolean;

export type SocialPlatform_X24Defs_UNotificationSettings_Properties_Email = boolean;

export type SocialPlatform_X24Defs_UNotificationSettings_AdditionalProperties = never;

export interface SocialPlatform_X24Defs_UNotificationSettings {
  "email"?: SocialPlatform_X24Defs_UNotificationSettings_Properties_Email;
  "push"?: SocialPlatform_X24Defs_UNotificationSettings_Properties_Push;
  "sms"?: SocialPlatform_X24Defs_UNotificationSettings_Properties_Sms;
}

export type SocialPlatform_X24Defs_UEmail = string;

export interface SocialPlatform {
  "user": SocialPlatform_Properties_X75ser;
  "posts": SocialPlatform_Properties_Posts;
  "settings": SocialPlatform_Properties_Settings;
  "followers"?: SocialPlatform_Properties_Followers;
  "pinnedPost"?: SocialPlatform_Properties_PinnedPost;
}
