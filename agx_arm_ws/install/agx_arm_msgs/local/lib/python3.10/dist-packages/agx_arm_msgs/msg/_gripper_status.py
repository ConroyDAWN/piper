# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agx_arm_msgs:msg/GripperStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GripperStatus(type):
    """Metaclass of message 'GripperStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('agx_arm_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'agx_arm_msgs.msg.GripperStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__gripper_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__gripper_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__gripper_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__gripper_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__gripper_status

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GripperStatus(metaclass=Metaclass_GripperStatus):
    """Message class 'GripperStatus'."""

    __slots__ = [
        '_header',
        '_width',
        '_force',
        '_voltage_too_low',
        '_motor_overheating',
        '_driver_overcurrent',
        '_driver_overheating',
        '_sensor_status',
        '_driver_error_status',
        '_driver_enable_status',
        '_homing_status',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'width': 'double',
        'force': 'double',
        'voltage_too_low': 'boolean',
        'motor_overheating': 'boolean',
        'driver_overcurrent': 'boolean',
        'driver_overheating': 'boolean',
        'sensor_status': 'boolean',
        'driver_error_status': 'boolean',
        'driver_enable_status': 'boolean',
        'homing_status': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.width = kwargs.get('width', float())
        self.force = kwargs.get('force', float())
        self.voltage_too_low = kwargs.get('voltage_too_low', bool())
        self.motor_overheating = kwargs.get('motor_overheating', bool())
        self.driver_overcurrent = kwargs.get('driver_overcurrent', bool())
        self.driver_overheating = kwargs.get('driver_overheating', bool())
        self.sensor_status = kwargs.get('sensor_status', bool())
        self.driver_error_status = kwargs.get('driver_error_status', bool())
        self.driver_enable_status = kwargs.get('driver_enable_status', bool())
        self.homing_status = kwargs.get('homing_status', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.width != other.width:
            return False
        if self.force != other.force:
            return False
        if self.voltage_too_low != other.voltage_too_low:
            return False
        if self.motor_overheating != other.motor_overheating:
            return False
        if self.driver_overcurrent != other.driver_overcurrent:
            return False
        if self.driver_overheating != other.driver_overheating:
            return False
        if self.sensor_status != other.sensor_status:
            return False
        if self.driver_error_status != other.driver_error_status:
            return False
        if self.driver_enable_status != other.driver_enable_status:
            return False
        if self.homing_status != other.homing_status:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def width(self):
        """Message field 'width'."""
        return self._width

    @width.setter
    def width(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'width' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'width' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._width = value

    @builtins.property
    def force(self):
        """Message field 'force'."""
        return self._force

    @force.setter
    def force(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'force' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'force' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._force = value

    @builtins.property
    def voltage_too_low(self):
        """Message field 'voltage_too_low'."""
        return self._voltage_too_low

    @voltage_too_low.setter
    def voltage_too_low(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'voltage_too_low' field must be of type 'bool'"
        self._voltage_too_low = value

    @builtins.property
    def motor_overheating(self):
        """Message field 'motor_overheating'."""
        return self._motor_overheating

    @motor_overheating.setter
    def motor_overheating(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'motor_overheating' field must be of type 'bool'"
        self._motor_overheating = value

    @builtins.property
    def driver_overcurrent(self):
        """Message field 'driver_overcurrent'."""
        return self._driver_overcurrent

    @driver_overcurrent.setter
    def driver_overcurrent(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'driver_overcurrent' field must be of type 'bool'"
        self._driver_overcurrent = value

    @builtins.property
    def driver_overheating(self):
        """Message field 'driver_overheating'."""
        return self._driver_overheating

    @driver_overheating.setter
    def driver_overheating(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'driver_overheating' field must be of type 'bool'"
        self._driver_overheating = value

    @builtins.property
    def sensor_status(self):
        """Message field 'sensor_status'."""
        return self._sensor_status

    @sensor_status.setter
    def sensor_status(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'sensor_status' field must be of type 'bool'"
        self._sensor_status = value

    @builtins.property
    def driver_error_status(self):
        """Message field 'driver_error_status'."""
        return self._driver_error_status

    @driver_error_status.setter
    def driver_error_status(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'driver_error_status' field must be of type 'bool'"
        self._driver_error_status = value

    @builtins.property
    def driver_enable_status(self):
        """Message field 'driver_enable_status'."""
        return self._driver_enable_status

    @driver_enable_status.setter
    def driver_enable_status(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'driver_enable_status' field must be of type 'bool'"
        self._driver_enable_status = value

    @builtins.property
    def homing_status(self):
        """Message field 'homing_status'."""
        return self._homing_status

    @homing_status.setter
    def homing_status(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'homing_status' field must be of type 'bool'"
        self._homing_status = value
