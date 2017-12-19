// generated from rosidl_generator_c/resource/msg__functions.h.em
// generated code does not contain a copyright notice

@#######################################################################
@# EmPy template for generating <msg>__functions.h files
@#
@# Context:
@#  - spec (rosidl_parser.MessageSpecification)
@#    Parsed specification of the .msg file
@#  - subfolder (string)
@#    The subfolder / subnamespace of the message
@#    Either 'msg' or 'srv'
@#  - get_header_filename_from_msg_name (function)
@#######################################################################
@
@{
from rosidl_generator_c import get_typename_of_base_type
from rosidl_generator_c import value_to_c

header_guard_parts = [
    spec.base_type.pkg_name, subfolder,
    get_header_filename_from_msg_name(spec.base_type.type) + '__serialization_h']
header_guard_variable = '__'.join([x.upper() for x in header_guard_parts]) + '_'

msg_typename = '%s__%s__%s' % (spec.base_type.pkg_name, subfolder, spec.base_type.type)
array_typename = '%s__Array' % msg_typename
}@
#ifndef @(header_guard_variable)
#define @(header_guard_variable)

#if __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "freertps/rtps/type/type.h"
#include "freertps/freertps.h"

#include "rosidl_generator_c/cdr.h"
#include "rosidl_generator_c/visibility_control.h"
#include "@(spec.base_type.pkg_name)/msg/rosidl_generator_c__visibility_control.h"

#include "@(spec.base_type.pkg_name)/@(subfolder)/@(get_header_filename_from_msg_name(spec.base_type.type))__struct.h"

@#######################################################################
@# message functions
@#######################################################################
/// Initialize @(spec.base_type.pkg_name)/@(spec.base_type.type) message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(@(msg_typename))) before
 * or use @(msg_typename)__create() to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_@(spec.base_type.pkg_name)
bool
@(msg_typename)__serialize(void *_msg, Cdr *cdr);

/// Initialize @(spec.base_type.pkg_name)/@(spec.base_type.type) message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(@(msg_typename))) before
 * or use @(msg_typename)__create() to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_@(spec.base_type.pkg_name)
bool
@(msg_typename)__deserialize(void *_msg, Cdr *cdr);

extern struct freertps_type @(msg_typename)__type;

#if __cplusplus
}
#endif

#endif  // @(header_guard_variable)
