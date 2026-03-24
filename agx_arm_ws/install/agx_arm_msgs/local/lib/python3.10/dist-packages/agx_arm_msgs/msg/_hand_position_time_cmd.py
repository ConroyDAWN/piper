# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agx_arm_msgs:msg/HandPositionTimeCmd.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_HandPositionTimeCmd(type):
    """Metaclass of message 'HandPositionTimeCmd'."""

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
                'agx_arm_msgs.msg.HandPositionTimeCmd')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__hand_position_time_cmd
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__hand_position_time_cmd
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__hand_position_time_cmd
            cls._TYPE_SUPPORT = module.type_support_msg__msg__hand_position_time_cmd
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__hand_position_time_cmd

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class HandPositionTimeCmd(metaclass=Metaclass_HandPositionTimeCmd):
    """Message class 'HandPositionTimeCmd'."""

    __slots__ = [
        '_thumb_tip_pos',
        '_thumb_base_pos',
        '_index_finger_pos',
        '_middle_finger_pos',
        '_ring_finger_pos',
        '_pinky_finger_pos',
        '_thumb_tip_time',
        '_thumb_base_time',
        '_index_finger_time',
        '_middle_finger_time',
        '_ring_finger_time',
        '_pinky_finger_time',
    ]

    _fields_and_field_types = {
        'thumb_tip_pos': 'int8',
        'thumb_base_pos': 'int8',
        'index_finger_pos': 'int8',
        'middle_finger_pos': 'int8',
        'ring_finger_pos': 'int8',
        'pinky_finger_pos': 'int8',
        'thumb_tip_time': 'uint8',
        'thumb_base_time': 'uint8',
        'index_finger_time': 'uint8',
        'middle_finger_time': 'uint8',
        'ring_finger_time': 'uint8',
        'pinky_finger_time': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.thumb_tip_pos = kwargs.get('thumb_tip_pos', int())
        self.thumb_base_pos = kwargs.get('thumb_base_pos', int())
        self.index_finger_pos = kwargs.get('index_finger_pos', int())
        self.middle_finger_pos = kwargs.get('middle_finger_pos', int())
        self.ring_finger_pos = kwargs.get('ring_finger_pos', int())
        self.pinky_finger_pos = kwargs.get('pinky_finger_pos', int())
        self.thumb_tip_time = kwargs.get('thumb_tip_time', int())
        self.thumb_base_time = kwargs.get('thumb_base_time', int())
        self.index_finger_time = kwargs.get('index_finger_time', int())
        self.middle_finger_time = kwargs.get('middle_finger_time', int())
        self.ring_finger_time = kwargs.get('ring_finger_time', int())
        self.pinky_finger_time = kwargs.get('pinky_finger_time', int())

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
        if self.thumb_tip_pos != other.thumb_tip_pos:
            return False
        if self.thumb_base_pos != other.thumb_base_pos:
            return False
        if self.index_finger_pos != other.index_finger_pos:
            return False
        if self.middle_finger_pos != other.middle_finger_pos:
            return False
        if self.ring_finger_pos != other.ring_finger_pos:
            return False
        if self.pinky_finger_pos != other.pinky_finger_pos:
            return False
        if self.thumb_tip_time != other.thumb_tip_time:
            return False
        if self.thumb_base_time != other.thumb_base_time:
            return False
        if self.index_finger_time != other.index_finger_time:
            return False
        if self.middle_finger_time != other.middle_finger_time:
            return False
        if self.ring_finger_time != other.ring_finger_time:
            return False
        if self.pinky_finger_time != other.pinky_finger_time:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def thumb_tip_pos(self):
        """Message field 'thumb_tip_pos'."""
        return self._thumb_tip_pos

    @thumb_tip_pos.setter
    def thumb_tip_pos(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'thumb_tip_pos' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'thumb_tip_pos' field must be an integer in [-128, 127]"
        self._thumb_tip_pos = value

    @builtins.property
    def thumb_base_pos(self):
        """Message field 'thumb_base_pos'."""
        return self._thumb_base_pos

    @thumb_base_pos.setter
    def thumb_base_pos(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'thumb_base_pos' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'thumb_base_pos' field must be an integer in [-128, 127]"
        self._thumb_base_pos = value

    @builtins.property
    def index_finger_pos(self):
        """Message field 'index_finger_pos'."""
        return self._index_finger_pos

    @index_finger_pos.setter
    def index_finger_pos(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'index_finger_pos' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'index_finger_pos' field must be an integer in [-128, 127]"
        self._index_finger_pos = value

    @builtins.property
    def middle_finger_pos(self):
        """Message field 'middle_finger_pos'."""
        return self._middle_finger_pos

    @middle_finger_pos.setter
    def middle_finger_pos(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'middle_finger_pos' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'middle_finger_pos' field must be an integer in [-128, 127]"
        self._middle_finger_pos = value

    @builtins.property
    def ring_finger_pos(self):
        """Message field 'ring_finger_pos'."""
        return self._ring_finger_pos

    @ring_finger_pos.setter
    def ring_finger_pos(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ring_finger_pos' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'ring_finger_pos' field must be an integer in [-128, 127]"
        self._ring_finger_pos = value

    @builtins.property
    def pinky_finger_pos(self):
        """Message field 'pinky_finger_pos'."""
        return self._pinky_finger_pos

    @pinky_finger_pos.setter
    def pinky_finger_pos(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'pinky_finger_pos' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'pinky_finger_pos' field must be an integer in [-128, 127]"
        self._pinky_finger_pos = value

    @builtins.property
    def thumb_tip_time(self):
        """Message field 'thumb_tip_time'."""
        return self._thumb_tip_time

    @thumb_tip_time.setter
    def thumb_tip_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'thumb_tip_time' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'thumb_tip_time' field must be an unsigned integer in [0, 255]"
        self._thumb_tip_time = value

    @builtins.property
    def thumb_base_time(self):
        """Message field 'thumb_base_time'."""
        return self._thumb_base_time

    @thumb_base_time.setter
    def thumb_base_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'thumb_base_time' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'thumb_base_time' field must be an unsigned integer in [0, 255]"
        self._thumb_base_time = value

    @builtins.property
    def index_finger_time(self):
        """Message field 'index_finger_time'."""
        return self._index_finger_time

    @index_finger_time.setter
    def index_finger_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'index_finger_time' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'index_finger_time' field must be an unsigned integer in [0, 255]"
        self._index_finger_time = value

    @builtins.property
    def middle_finger_time(self):
        """Message field 'middle_finger_time'."""
        return self._middle_finger_time

    @middle_finger_time.setter
    def middle_finger_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'middle_finger_time' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'middle_finger_time' field must be an unsigned integer in [0, 255]"
        self._middle_finger_time = value

    @builtins.property
    def ring_finger_time(self):
        """Message field 'ring_finger_time'."""
        return self._ring_finger_time

    @ring_finger_time.setter
    def ring_finger_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ring_finger_time' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'ring_finger_time' field must be an unsigned integer in [0, 255]"
        self._ring_finger_time = value

    @builtins.property
    def pinky_finger_time(self):
        """Message field 'pinky_finger_time'."""
        return self._pinky_finger_time

    @pinky_finger_time.setter
    def pinky_finger_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'pinky_finger_time' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'pinky_finger_time' field must be an unsigned integer in [0, 255]"
        self._pinky_finger_time = value
