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

#include <string.h>
#include <stdlib.h>

#include "rosidl_generator_c/cdr.h"
#include "rosidl_generator_c/string.h"
#include "rosidl_generator_c/string_functions.h"

int64_t size(Cdr *cdr)
{
    return cdr->currentPosition;
}

size_t alignment(Cdr *cdr, size_t dataSize)
{
    return dataSize > cdr->lastDataSize
            ? (dataSize - (cdr->currentPosition % dataSize)) & (dataSize-1)
            : 0;
}

void move(Cdr *cdr, size_t num_bytes)
{
    cdr->currentPosition += num_bytes;
    cdr->_p += num_bytes;
}

bool resize(Cdr *cdr, size_t size)
{
    cdr->buffer_size += size;

    if (cdr->buffer == NULL)
    {
        cdr->buffer = malloc(cdr->buffer_size);
    } else
    {
        cdr->buffer = realloc(cdr->buffer, cdr->buffer_size + 1);
    }

    cdr->_p = cdr->buffer;
    cdr->_p += cdr->currentPosition;

    return true;
}

void align(Cdr *cdr, size_t align)
{
    if (align > 0)
    {
        move(cdr, align);
    }
}

#define serialize(cdr, type, value) ({\
    size_t align = cdr->alignment(cdr, sizeof(type)); \
    size_t sizeAligned = sizeof(value) + align; \
    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned \
        || cdr->resize(cdr, sizeAligned)) \
    { \
        cdr->lastDataSize = sizeof(type); \
        cdr->align(cdr, align); \
        *((type *)cdr->_p) = value; \
        move(cdr, sizeof(type)); \
    }\
})

void serialize_char(Cdr *cdr, const char char_t)
{
    if((cdr->buffer_size - cdr->currentPosition) >= sizeof(char_t)
            || cdr->resize(cdr, sizeof(char_t)))
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(char_t);

        *((char *)cdr->_p) = char_t;
        move(cdr, sizeof(char));
    }
}

void serialize_int16(Cdr *cdr, const int16_t short_t)
{
    size_t align = cdr->alignment(cdr, sizeof(int16_t));
    size_t sizeAligned = sizeof(short_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned
            || cdr->resize(cdr, sizeAligned))
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(int16_t);

        // Align.
        cdr->align(cdr, align);

        *((int16_t *)cdr->_p) = short_t;
        move(cdr, sizeof(int16_t));
    }
}

//void serialize(Cdr *cdr, const int16_t short_t, Endianness endianness);

void serialize_int32(Cdr *cdr, const void* long_t)
{
//    size_t align = cdr->alignment(cdr, sizeof(int32_t));
//    size_t sizeAligned = sizeof(long_t) + align;
//
//    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned
//            || cdr->resize(cdr, sizeAligned))
//    {
//        // Save last datasize.
//        cdr->lastDataSize = sizeof(int32_t);
//
//        // Align.
//        cdr->align(cdr, align);
//
//        *((int64_t *)cdr->_p) = long_t;
//        move(cdr, sizeof(int32_t));
//    }
    serialize(cdr, int32_t, long_t);
}

//void serialize(Cdr *cdr, const int32_t long_t, Endianness endianness);

void serialize_int64(Cdr *cdr, const int64_t longlong_t)
{
    size_t align = cdr->alignment(cdr, sizeof(int64_t));
    size_t sizeAligned = sizeof(longlong_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned
            || cdr->resize(cdr, sizeAligned))
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(int64_t);

        // Align.
        cdr->align(cdr, align);

        *((int64_t *)cdr->_p) = longlong_t;
        move(cdr, sizeof(int64_t));
    }
}

//void serialize(Cdr *cdr, const int64_t longlong_t, Endianness endianness);

void serialize_float(Cdr *cdr, const float float_t)
{
    size_t align = cdr->alignment(cdr, sizeof(float));
    size_t sizeAligned = sizeof(float_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned
            || cdr->resize(cdr, sizeAligned))
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(float);

        // Align.
        cdr->align(cdr, align);

        *((float *)cdr->_p) = float_t;
        move(cdr, sizeof(float));
    }
}

//void serialize(Cdr *cdr, const float float_t, Endianness endianness);

void serialize_double(Cdr *cdr, const double double_t)
{
    size_t align = cdr->alignment(cdr, sizeof(double));
    size_t sizeAligned = sizeof(double_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned
            || cdr->resize(cdr, sizeAligned))
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(double);

        // Align.
        cdr->align(cdr, align);

        *((double *)cdr->_p) = double_t;
        move(cdr, sizeof(double));
    }
}

//void serialize(Cdr *cdr, const double double_t, Endianness endianness);

void serialize_bool(Cdr *cdr, const bool bool_t)
{
    uint8_t value = 0;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeof(uint8_t)
            || cdr->resize(cdr, sizeof(uint8_t)))
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(uint8_t);

        if(bool_t)
            value = 1;

        *((bool *)cdr->_p) = value;
        move(cdr, sizeof(bool));
    }
}

void serialize_string(Cdr *cdr, const char *string_t)
{
    uint32_t length = 0;

    if(string_t != NULL)
        length = (uint32_t)strlen(string_t) + 1;

    cdr->serialize_int32(cdr, length);

    if(length > 0)
    {
        if((cdr->buffer_size - cdr->currentPosition) >= length
                || cdr->resize(cdr, length))
        {
            // Save last datasize.
            cdr->lastDataSize = sizeof(uint8_t);

            memcpy(cdr->_p, string_t, length);

            move(cdr, length);
        }
    }
}

//void serialize(Cdr *cdr, const char *string_t, Endianness endianness);

void serializeArray_bool(Cdr *cdr, const bool *bool_t, size_t numElements)
{

}

void serializeArray_char(Cdr *cdr, const char *char_t, size_t numElements)
{

}

void serializeArray_int16(Cdr *cdr, const int16_t *short_t, size_t numElements)
{

}

//void serializeArray(Cdr *cdr, const int16_t *short_t, size_t numElements, Endianness endianness);

void serializeArray_int32(Cdr *cdr, const int32_t *long_t, size_t numElements)
{

}

//void serializeArray(Cdr *cdr, const int32_t *long_t, size_t numElements, Endianness endianness);

void serializeArray_string(Cdr *cdr, const wchar_t *wchar, size_t numElements)
{

}

//void serializeArray(Cdr *cdr, const wchar_t *wchar, size_t numElements, Endianness endianness);

void serializeArray_int64(Cdr *cdr, const int64_t *longlong_t, size_t numElements)
{

}

//void serializeArray(Cdr *cdr, const int64_t *longlong_t, size_t numElements, Endianness endianness);

void serializeArray_float(Cdr *cdr, const float *float_t, size_t numElements)
{

}

//void serializeArray(Cdr *cdr, const float *float_t, size_t numElements, Endianness endianness);

void serializeArray_double(Cdr *cdr, const double *double_t, size_t numElements)
{

}

//void serializeArray(Cdr *cdr, const double *double_t, size_t numElements, Endianness endianness);

void deserialize_char(Cdr *cdr, char *char_t)
{
    if((cdr->buffer_size - cdr->currentPosition) >= sizeof(char_t))
    {
        // Save last datasize.
        cdr-> lastDataSize = sizeof(char);

        *char_t = *((char *)*cdr->_p);
        *cdr->_p += sizeof(char);
        cdr->currentPosition += sizeof(char);
    }
}

void deserialize_int16(Cdr *cdr, int16_t *short_t)
{
    size_t align = cdr->alignment(cdr, sizeof(int16_t));
    size_t sizeAligned = sizeof(short_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned)
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(int16_t);

        // Align
        cdr->align(cdr, align);

        *short_t = (int16_t)*cdr->_p;
        move(cdr , sizeof(int16_t));
    }
}

////void deserialize(Cdr *cdr, int16_t &short_t, Endianness endianness);

void deserialize_int32(Cdr *cdr, int32_t *long_t)
{
    size_t align = cdr->alignment(cdr, sizeof(int32_t));
    size_t sizeAligned = sizeof(long_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned)
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(int32_t);

        // Align
        cdr->align(cdr, align);

        *long_t = (int32_t)*cdr->_p;
        move(cdr , sizeof(int32_t));
    }
}

////void deserialize(Cdr *cdr, int32_t &long_t, Endianness endianness);

void deserialize_int64(Cdr *cdr, int64_t *longlong_t)
{
    size_t align = cdr->alignment(cdr, sizeof(int64_t));
    size_t sizeAligned = sizeof(longlong_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned)
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(int64_t);

        // Align.
        cdr->align(cdr, align);

        *longlong_t = (int64_t)*cdr->_p;
        move(cdr , sizeof(int64_t));
    }
}

////void deserialize(Cdr *cdr, int64_t &longlong_t, Endianness endianness);

void deserialize_float(Cdr *cdr, float *float_t)
{
    size_t align = cdr->alignment(cdr, sizeof(float));
    size_t sizeAligned = sizeof(float_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned)
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(float);

        // Align.
        cdr->align(cdr, align);

        *float_t = (float)*cdr->_p;
        move(cdr , sizeof(float));
    }
}

////void deserialize(Cdr *cdr, float &float_t, Endianness endianness);

void deserialize_double(Cdr *cdr, double *double_t)
{
    size_t align = cdr->alignment(cdr, sizeof(double));
    size_t sizeAligned = sizeof(double_t) + align;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeAligned)
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(double);

        // Align.
        cdr->align(cdr, align);

        *double_t = (double)*cdr->_p;
        move(cdr , sizeof(double));
    }
}

////void deserialize(Cdr *cdr, double &double_t, Endianness endianness);

void deserialize_bool(Cdr *cdr, bool *bool_t)
{
    uint8_t value = 0;

    if((cdr->buffer_size - cdr->currentPosition) >= sizeof(uint8_t))
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(uint8_t);

        value = (uint8_t) *cdr->_p;
        move(cdr , sizeof(uint8_t));

        if(value == 1)
        {
            *bool_t = true;
        }
        else if(value == 0)
        {
            *bool_t = false;
        }
    }
}

void deserialize_string(Cdr *cdr, rosidl_generator_c__String *string_t)
{
    int32_t length = 0;

    cdr->deserialize_int32(cdr, &length);

    if((cdr->buffer_size - cdr->currentPosition) >= length)
    {
        // Save last datasize.
        cdr->lastDataSize = sizeof(uint8_t);

        rosidl_generator_c__String__assignn(string_t, cdr->_p, length);

        move(cdr , length);
    }
}

////void deserialize(Cdr *cdr, char *&string_t, Endianness endianness);
//const char* readString(uint32_t &length);

void deserializeArray_bool(Cdr *cdr, bool *bool_t, size_t numElements)
{

}

void deserializeArray_char(Cdr *cdr, char *char_t, size_t numElements)
{

}

void deserializeArray_int16(Cdr *cdr, int16_t *short_t, size_t numElements)
{

}

////void deserializeArray(Cdr *cdr, int16_t *short_t, size_t numElements, Endianness endianness);

void deserializeArray_int32(Cdr *cdr, int32_t *long_t, size_t numElements)
{

}

////void deserializeArray(Cdr *cdr, int32_t *long_t, size_t numElements, Endianness endianness);
//void deserializeArray(Cdr *cdr, wchar_t *wchar, size_t numElements);
////void deserializeArray(wchar_t *wchar, size_t numElements, Endianness endianness);

void deserializeArray_int64(Cdr *cdr, int64_t *longlong_t, size_t numElements)
{

}

////void deserializeArray(Cdr *cdr, int64_t *longlong_t, size_t numElements, Endianness endianness);

void deserializeArray_float(Cdr *cdr, float *float_t, size_t numElements)
{

}

////void deserializeArray(Cdr *cdr, float *float_t, size_t numElements, Endianness endianness);

void deserializeArray_double(Cdr *cdr, double *double_t, size_t numElements)
{

}

////void deserializeArray(Cdr *cdr, double *double_t, size_t numElements, Endianness endianness);
//void serializeBoolSequence(const std::vector<bool> &vector_t);
//void deserializeBoolSequence(std::vector<bool> &vector_t);
//void deserializeStringSequence(std::string *&sequence_t, size_t &numElements);

Cdr* create_cdr() {
    Cdr *cdr = malloc(sizeof(Cdr));

    cdr->buffer = NULL;
    cdr->buffer_size = 0;
    cdr->_p = cdr->buffer;

    cdr->lastDataSize = 0;
    cdr->currentPosition = 0;

    cdr->alignment = alignment;
    cdr->resize = resize;
    cdr->align = align;

    cdr->size = size;

    cdr->serialize_char = serialize_char;
    cdr->serialize_int16 = serialize_int16;
    cdr->serialize_int32 = serialize_int32;
    cdr->serialize_int64 = serialize_int64;
    cdr->serialize_float = serialize_float;
    cdr->serialize_double = serialize_double;
    cdr->serialize_bool = serialize_bool;
    cdr->serialize_string = serialize_string;
    cdr->serializeArray_bool = serializeArray_bool;
    cdr->serializeArray_char = serializeArray_char;
    cdr->serializeArray_int16 = serializeArray_int16;
    cdr->serializeArray_int32 = serializeArray_int32;
    cdr->serializeArray_string = serializeArray_string;
    cdr->serializeArray_int64 = serializeArray_int64;
    cdr->serializeArray_float = serializeArray_float;
    //cdr->serializeArray)(Cdr *cdr, const float *float_t, size_t numElements, Endianness endianness);
    cdr->serializeArray_double = serializeArray_double;
    //cdr->serializeArray)(Cdr *cdr, const double *double_t, size_t numElements, Endianness endianness);

    cdr->deserialize_char = deserialize_char;
    cdr->deserialize_int16 = deserialize_int16;
    //cdr->deserialize)(Cdr *cdr, int16_t &short_t, Endianness endianness);
    cdr->deserialize_int32 = deserialize_int32;
    ////cdr->deserialize)(Cdr *cdr, int32_t &long_t, Endianness endianness);
    cdr->deserialize_int64 = deserialize_int64;
    ////cdr->deserialize)(Cdr *cdr, int64_t &longlong_t, Endianness endianness);
    cdr->deserialize_float = deserialize_float;
    ////cdr->deserialize)(Cdr *cdr, float &float_t, Endianness endianness);
    cdr->deserialize_double = deserialize_double;
    ////cdr->deserialize)(Cdr *cdr, double &double_t, Endianness endianness);
    cdr->deserialize_bool = deserialize_bool;
    cdr->deserialize_string = deserialize_string;
    ////cdr->deserialize)(Cdr *cdr, char *&string_t, Endianness endianness);
    //const char* (*readString)(Cdr *cdr, uint32_t &length);
    cdr->deserializeArray_bool = deserializeArray_bool;
    cdr->deserializeArray_char = deserializeArray_char;
    cdr->deserializeArray_int16 = deserializeArray_int16;
    ////cdr->deserializeArray)(Cdr *cdr, int16_t *short_t, size_t numElements, Endianness endianness);
    cdr->deserializeArray_int32 = deserializeArray_int32;
    ////cdr->deserializeArray)(Cdr *cdr, int32_t *long_t, size_t numElements, Endianness endianness);
    //cdr->deserializeArray)(Cdr *cdr, wchar_t *wchar, size_t numElements);
    ////cdr->deserializeArray)(Cdr *cdr, wchar_t *wchar, size_t numElements, Endianness endianness);
    cdr->deserializeArray_int64 = deserializeArray_int64;
    ////cdr->deserializeArray)(Cdr *cdr, int64_t *longlong_t, size_t numElements, Endianness endianness);
    cdr->deserializeArray_float = deserializeArray_float;
    ////cdr->deserializeArray)(Cdr *cdr, float *float_t, size_t numElements, Endianness endianness);
    cdr->deserializeArray_double = deserializeArray_double;
    ////cdr->deserializeArray)(Cdr *cdr, double *double_t, size_t numElements, Endianness endianness);
    //cdr->serializeBoolSequence)(Cdr *cdr, const std::vector<bool> &vector_t);
    //cdr->deserializeBoolSequence)(Cdr *cdr, std::vector<bool> &vector_t);
    //cdr->deserializeStringSequence)(Cdr *cdr, std::string *&sequence_t, size_t &numElements);

    return cdr;
}

Cdr* create_cdr_with_buffer(uint8_t *buffer, uint32_t buffer_size)
{
    Cdr *cdr = create_cdr();

    cdr->_p = buffer;
    cdr->buffer_size = buffer_size;

    return cdr;
}

void destroy_cdr(Cdr *cdr)
{
    if (cdr != NULL) {
        if (cdr->buffer != NULL) {
            free(cdr->buffer);
        }

        cdr->buffer = NULL;
        cdr->buffer_size = 0;
        cdr->_p = NULL;
        cdr->lastDataSize = 0;
        cdr->currentPosition = 0;

        free(cdr);
    }
}
