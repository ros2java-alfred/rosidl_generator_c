// generated from rosidl_generator_c/resource/msg__functions.c.em
// generated code does not contain a copyright notice

@#######################################################################
@# EmPy template for generating <msg>__functions.c files
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
from rosidl_generator_c import primitive_value_to_c
from rosidl_generator_c import value_to_c

msg_typename = '%s__%s__%s' % (spec.base_type.pkg_name, subfolder, spec.base_type.type)
array_typename = '%s__Array' % msg_typename
}@
#include "@(spec.base_type.pkg_name)/@(subfolder)/@(get_header_filename_from_msg_name(spec.base_type.type))__serialization.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "freertps/rtps/type/type.h"

@#######################################################################
@# include message dependencies
@#######################################################################
@{
from collections import OrderedDict
includes = OrderedDict()
for field in spec.fields:
    if field.type.is_primitive_type():
        if field.type.type == 'string':
            field_names = includes.setdefault('rosidl_generator_c/string_functions.h', [])
            field_names.append(field.name)
        else:
            if field.type.is_dynamic_array():
                field_names = includes.setdefault('rosidl_generator_c/primitives_array_functions.h', [])
                field_names.append(field.name)
    else:
        field_names = includes.setdefault(
            '%s/msg/%s__functions.h' %
            (field.type.pkg_name, get_header_filename_from_msg_name(field.type.type)),
            [])
        field_names.append(field.name)
}@
@[if includes]@
// include message dependencies
@[  for header_file, field_names in includes.items()]@
@[    for field_name in field_names]@
// @(field_name)
@[    end for]@
#include "@(header_file)"
@[  end for]@

@[end if]@

@{
class PrimitiveType(object):
  def __init__(self, type_name):
    self.name = type_name
  def serialize(self, name, lines):
    raise RuntimeError("serialization of {0} not implemented!".format(self.name))
  def deserialize(self, name, lines):
    #raise RuntimeError("deserialization of {0} not implemented!".format(self.name))
    lines.append("  FREERTPS_INFO(\"deserialization of {0} not implemented!\\r\\n\");".format(self.name))
    lines.append("  exit(1);")
  def create(self, field_name, lines):
    #do nothing
    return
  def destroy(self, field_name, lines):
    #do nothing
    return

class BooleanType(PrimitiveType):
  def __init__(self):
    super(BooleanType, self).__init__('bool')
  def serialize(self, field_name, lines):
    lines.append("  cdr->serialize_bool(cdr, _s->{0});".format(field_name))
  def serialize_fixed_array(self, field_name, array_size, lines):
    lines.append("  cdr->serializeArray_bool(cdr, _s->{0}, {1});".format(field_name, array_size))
  def deserialize(self, field_name, lines):
    lines.append("  cdr->deserialize_bool(cdr, &_s->{0});".format(field_name))
  def create(self, field_name, lines):
    lines.append("  _s->{0} = false;".format(field_name))
  def destroy(self, field_name, lines):
    lines.append("  _s->{0} = false;".format(field_name))

class NumericType(PrimitiveType):
  def __init__(self, c_name, field_type):
    super(NumericType, self).__init__(c_name)
    self.field_type = field_type
  def serialize(self, field_name, lines):
    lines.append("  cdr->serialize_{0}(cdr, _s->{1});".format(self.field_type, field_name))
  def serialize_fixed_array(self, field_name, array_size, lines):
    lines.append("  cdr->serializeArray_{0}(cdr, _s->{1}, {2});".format(self.field_type, field_name, array_size))
  def serialize_variable_array(self, field_name, lines):
    size_var = "_s->{0}.size".format(field_name)
    lines.append("  cdr->serializeArray_{0}(cdr, _s->{1}.data, {2});".format(self.field_type, field_name, size_var))
  def deserialize(self, field_name, lines):
    lines.append("  cdr->deserialize_{0}(cdr, &_s->{1});".format(self.field_type, field_name))
  def deserialize_fixed_array(self, field_name, array_size, lines):
    lines.append("  cdr->serializeArray_{0}(cdr, _s->{1}, {2});".format(self.field_type, field_name, array_size))
  def deserialize_variable_array(self, field_name, lines):
    lines.append("  FREERTPS_INFO(\"this is not yet complete.\\r\\n\");")
    lines.append("  return false;")
  def create(self, field_name, lines):
    lines.append("  _s->{0} = 0;".format(field_name))
  def destroy(self, field_name, lines):
    lines.append("  _s->{0} = 0;".format(field_name))

class BigNumericType(NumericType):
  def __init__(self, c_name, field_type):
    super(BigNumericType, self).__init__(c_name, field_type)
  def serialize(self, field_name, lines):
    lines.append("  cdr->serialize_{0}(cdr, _s->{1});".format(self.field_type, field_name))
  def serialize_fixed_array(self, field_name, array_size, lines):
    lines.append("  cdr->serializeArray_{0}(cdr, _s->{1}, {2});".format(self.field_type, field_name, array_size))
  def serialize_variable_array(self, field_name, lines):
    size_var = "_s->{0}.size".format(field_name)
    lines.append("  cdr->serializeArray_{0}(cdr, _s->{1}.data, {2});".format(self.field_type, field_name, size_var))
  def deserialize(self, field_name, lines):
    lines.append("  cdr->deserialize_{0}(cdr, &_s->{1});".format(self.field_type, field_name))

class StringType(PrimitiveType):
  def __init__(self):
    super(StringType, self).__init__('char *')
  def serialize(self, field_name, lines):
    lines.append("  cdr->serialize_string(cdr, _s->{0}.data);".format(field_name))
  def serialize_variable_array(self, field_name, lines):
    lines.append("  cdr->serializeArray_string(cdr, _s->{0}.data, _s->{0}.size);".format(field_name))
  def deserialize(self, field_name, lines):
    lines.append("  cdr->deserialize_string(cdr, &_s->{0});\r\n".format(field_name))
  def deserialize_variable_array(self, field_name, lines):
    lines.append("  FREERTPS_INFO(\"deserialization of variable-length string arrays not implemented!\\r\\n\");")
    lines.append("  exit(1);")
  def create(self, field_name, lines):
    lines.append("  _s->{0} = NULL;".format(field_name))
  def destroy(self, field_name, lines):
    lines.append("  if (_s->{0}) {{".format(field_name));
    lines.append("    free(_s->{0});".format(field_name));
    lines.append("    _s->{0} = NULL;".format(field_name));
    lines.append("  }");


primitive_types = { }
primitive_types['bool']    = BooleanType()
primitive_types['byte']    = NumericType('uint8_t', 'char')
primitive_types['uint8']   = NumericType('uint8_t', 'char')
primitive_types['char']    = NumericType('int8_t', 'char')
primitive_types['int8']    = NumericType('int8_t', 'char')
primitive_types['uint16']  = NumericType('uint16_t', 'int16')
primitive_types['int16']   = NumericType('int16_t', 'int16')
primitive_types['uint32']  = NumericType('uint32_t', 'int32')
primitive_types['int32']   = NumericType('int32_t', 'int32')
primitive_types['uint64']  = BigNumericType('uint64_t', 'int64')
primitive_types['int64']   = BigNumericType('int64_t', 'int64')
primitive_types['float32'] = NumericType('float', 'float')
primitive_types['float64'] = BigNumericType('double', 'double')
primitive_types['string']  = StringType()

def uncamelcase(camelcase):
  lower = ""
  upper_run_len = 0
  for idx in range(0, len(camelcase)):
    #print(camelcase[idx])
    if (camelcase[idx].isupper()):
      next_lower = idx < len(camelcase)-1 and camelcase[idx+1].islower()
      if (idx > 0 and upper_run_len == 0) or (idx > 1 and next_lower):
        lower += '_'
      lower += camelcase[idx].lower()
      upper_run_len += 1
    else:
      lower += camelcase[idx]
      upper_run_len = 0
  return lower
}@

@
@#######################################################################
@# message functions
@#######################################################################
bool
@(msg_typename)__serialize(void *_msg, Cdr *cdr)
{
  if (!_msg) {
    return false;
  }
  
  struct @(msg_typename) *_s = (struct @(msg_typename) *)_msg;

@{
lines = []
            
for field in spec.fields:
    lines.append('// ' + field.name)
    typename = field.type.type
    if field.type.is_primitive_type():
        if not field.type.is_array:
            primitive_types[typename].serialize(field.name, lines)
        elif field.type.array_size is None or field.type.is_upper_bound:
            primitive_types[typename].serialize_variable_array(field.name, lines)
        else:
            primitive_types[typename].serialize_fixed_array(field.name, field.type.array_size, lines)
    else:
        field_c_struct_name = "{0}__msg__{1}".format(field.type.pkg_name, field.type.type)
        if not field.type.is_array:
            lines.append("  {0}__serialize(&_s->{1}, cdr);".format(field_c_struct_name, field.name))
        elif field.type.array_size:
            lines.append("  for (uint32_t _{0}_idx = 0; _{0}_idx < {1}; _{0}_idx++)".format(field.name, field.type.array_size))
            lines.append("    {0}__serialize(&_s->{1}[_{1}_idx], cdr);".format(field_c_struct_name, field.name))
        else: # variable-length array of structs.
            # todo: i think the sequence length needs to be serialized first...
            lines.append("  for (uint32_t _{0}_idx = 0; _{0}_idx < _s->{0}.size; _{0}_idx++)".format(field.name))
            lines.append("    {0}__serialize(&_s->{1}.data[_{1}_idx], cdr);".format(field_c_struct_name, field.name))
    
for line in lines:
    print('  ' + line)
}@
  return true;
}

bool
@(msg_typename)__deserialize(void *_msg, Cdr *cdr)
{
  if (!_msg) {
    return false;
  }
  
  struct @(msg_typename) *_s = (struct @(msg_typename) *)_msg;

@{
lines = []          
            
for field in spec.fields:
    lines.append('// ' + field.name)
    typename = field.type.type
    if field.type.is_primitive_type():
        if not field.type.is_array:
            primitive_types[typename].deserialize(field.name, lines)
        elif field.type.array_size is None or field.type.is_upper_bound:
            primitive_types[typename].deserialize_variable_array(field.name, lines)
        else:
            primitive_types[typename].deserialize_fixed_array(field.name, field.type.array_size, lines)
    else:
        field_c_struct_name = "{0}__msg__{1}".format(field.type.pkg_name, field.type.type)
        if not field.type.is_array:
            lines.append("  {0}__deserialize(&_s->{1}, cdr);".format(field_c_struct_name, field.name))
        elif field.type.array_size:
            lines.append("  for (uint32_t _{0}_idx = 0; _{0}_idx < {1}; _{0}_idx++)".format(field.name, field.type.array_size))
            lines.append("    {0}__deserialize(&_s->{1}[_{1}_idx], cdr);".format(field_c_struct_name, field.name))
        else: # variable-length array of structs.
            # todo: i think the sequence length needs to be serialized first...
            lines.append("  for (uint32_t _{0}_idx = 0; _{0}_idx < _s->{0}.size; _{0}_idx++)".format(field.name))
            lines.append("    {0}__deserialize(&_s->{1}.data[_{1}_idx], cdr);".format(field_c_struct_name, field.name))

for line in lines:
    print('  ' + line)
}@
  return true;
}

struct freertps_type @(msg_typename)__type =
{
@{
rtps_typename = '%s::%s::dds_::%s_' % (spec.base_type.pkg_name, subfolder, spec.base_type.type)
}
  //idl_type = '%s::msg::dds_::%s_' % (type_.pkg_name, type_.type)
  .rtps_typename = "@(rtps_typename)"
};
