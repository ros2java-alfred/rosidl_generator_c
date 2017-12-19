// Copyright 2017 Mickael Gaillard <mick.gaillard@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROSIDL_GENERATOR_C__CDR_H
#define ROSIDL_GENERATOR_C__CDR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "rosidl_generator_c/string.h"
#include "rosidl_generator_c/string_functions.h"

typedef struct Cdr Cdr;

struct Cdr {
    size_t lastDataSize;
    size_t currentPosition;

    uint8_t *buffer;
    uint32_t buffer_size;
    uint8_t *_p;

    size_t (*alignment)(Cdr *cdr, size_t dataSize);
    bool (*resize)(Cdr *cdr, size_t size);
    void (*align)(Cdr *cdr, size_t align);

    int64_t (*size)(Cdr *cdr);

    void (*serialize_char)(Cdr *cdr, const char char_t);
    void (*serialize_int16)(Cdr *cdr, const int16_t short_t);
    void (*serialize_int32)(Cdr *cdr, const int32_t long_t);
    void (*serialize_int64)(Cdr *cdr, const int64_t longlong_t);
    void (*serialize_float)(Cdr *cdr, const float float_t);
    void (*serialize_double)(Cdr *cdr, const double double_t);
    void (*serialize_bool)(Cdr *cdr, const bool bool_t);
    void (*serialize_string)(Cdr *cdr, const char* string_t);
    void (*serializeArray_bool)(Cdr *cdr, const bool *bool_t, size_t numElements);
    void (*serializeArray_char)(Cdr *cdr, const char *char_t, size_t numElements);
    void (*serializeArray_int16)(Cdr *cdr, const int16_t *short_t, size_t numElements);
    void (*serializeArray_int32)(Cdr *cdr, const int32_t *long_t, size_t numElements);
    void (*serializeArray_string)(Cdr *cdr, const wchar_t *wchar, size_t numElements);
    void (*serializeArray_int64)(Cdr *cdr, const int64_t *longlong_t, size_t numElements);
    void (*serializeArray_float)(Cdr *cdr, const float *float_t, size_t numElements);
    //void (*serializeArray)(Cdr *cdr, const float *float_t, size_t numElements, Endianness endianness);
    void (*serializeArray_double)(Cdr *cdr, const double *double_t, size_t numElements);
    //void (*serializeArray)(Cdr *cdr, const double *double_t, size_t numElements, Endianness endianness);

    void (*deserialize_char)(Cdr *cdr, char *char_t);
    void (*deserialize_int16)(Cdr *cdr, int16_t *short_t);
    //void (*deserialize)(Cdr *cdr, int16_t &short_t, Endianness endianness);
    void (*deserialize_int32)(Cdr *cdr, int32_t *long_t);
    ////void (*deserialize)(Cdr *cdr, int32_t &long_t, Endianness endianness);
    void (*deserialize_int64)(Cdr *cdr, int64_t *longlong_t);
    ////void (*deserialize)(Cdr *cdr, int64_t &longlong_t, Endianness endianness);
    void (*deserialize_float)(Cdr *cdr, float *float_t);
    ////void (*deserialize)(Cdr *cdr, float &float_t, Endianness endianness);
    void (*deserialize_double)(Cdr *cdr, double *double_t);
    ////void (*deserialize)(Cdr *cdr, double &double_t, Endianness endianness);
    void (*deserialize_bool)(Cdr *cdr, bool *bool_t);
    void (*deserialize_string)(Cdr *cdr, rosidl_generator_c__String *string_t);
    ////void (*deserialize)(Cdr *cdr, char *&string_t, Endianness endianness);
    //const char* (*readString)(Cdr *cdr, uint32_t &length);
    void (*deserializeArray_bool)(Cdr *cdr, bool *bool_t, size_t numElements);
    void (*deserializeArray_char)(Cdr *cdr, char *char_t, size_t numElements);
    void (*deserializeArray_int16)(Cdr *cdr, int16_t *short_t, size_t numElements);
    ////void (*deserializeArray)(Cdr *cdr, int16_t *short_t, size_t numElements, Endianness endianness);
    void (*deserializeArray_int32)(Cdr *cdr, int32_t *long_t, size_t numElements);
    ////void (*deserializeArray)(Cdr *cdr, int32_t *long_t, size_t numElements, Endianness endianness);
    //void (*deserializeArray)(Cdr *cdr, wchar_t *wchar, size_t numElements);
    ////void (*deserializeArray)(Cdr *cdr, wchar_t *wchar, size_t numElements, Endianness endianness);
    void (*deserializeArray_int64)(Cdr *cdr, int64_t *longlong_t, size_t numElements);
    ////void (*deserializeArray)(Cdr *cdr, int64_t *longlong_t, size_t numElements, Endianness endianness);
    void (*deserializeArray_float)(Cdr *cdr, float *float_t, size_t numElements);
    ////void (*deserializeArray)(Cdr *cdr, float *float_t, size_t numElements, Endianness endianness);
    void (*deserializeArray_double)(Cdr *cdr, double *double_t, size_t numElements);
    ////void (*deserializeArray)(Cdr *cdr, double *double_t, size_t numElements, Endianness endianness);
    //void (*serializeBoolSequence)(Cdr *cdr, const std::vector<bool> &vector_t);
    //void (*deserializeBoolSequence)(Cdr *cdr, std::vector<bool> &vector_t);
    //void (*deserializeStringSequence)(Cdr *cdr, std::string *&sequence_t, size_t &numElements);
};

Cdr* create_cdr();
Cdr* create_cdr_with_buffer(uint8_t *buffer, uint32_t buffer_size);
void destroy_cdr(Cdr *cdr);

#endif
