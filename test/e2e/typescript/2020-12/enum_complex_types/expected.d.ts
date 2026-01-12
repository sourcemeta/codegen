export type ComplexEnum_Properties_Status = {
  "code": 200,
  "message": "OK"
} | {
  "code": 404,
  "message": "Not Found"
} | {
  "code": 500,
  "message": "Internal Server Error"
};

export type ComplexEnum_Properties_FixedList = [ "read", "write", "execute" ];

export type ComplexEnum_Properties_FixedConfig = {
  "enabled": true,
  "maxRetries": 3
};

export type ComplexEnum_Properties_Coordinates = [ 0, 0 ] | [ 1, 1 ] | [ -1, -1 ];

export type ComplexEnum_AdditionalProperties = never;

export interface ComplexEnum {
  "status"?: ComplexEnum_Properties_Status;
  "coordinates"?: ComplexEnum_Properties_Coordinates;
  "fixedConfig"?: ComplexEnum_Properties_FixedConfig;
  "fixedList"?: ComplexEnum_Properties_FixedList;
}
