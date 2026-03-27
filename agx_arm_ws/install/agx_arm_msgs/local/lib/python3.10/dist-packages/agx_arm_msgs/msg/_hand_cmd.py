# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agx_arm_msgs:msg/HandCmd.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_HandCmd(type):
    """Metaclass of message 'HandCmd'."""

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
                'agx_arm_msgs.msg.HandCmd')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__hand_cmd
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__hand_cmd
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__hand_cmd
            cls._TYPE_SUPPORT = module.type_support_msg__msg__hand_cmd
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__hand_cmd

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class HandCmd(metaclass=Metaclass_HandCmd):
    """Message class 'HandCmd'."""

    __slots__ = [
        '_mode',
        '_thumb_tip',
        '_thumb_base',
        '_index_finger',
        '_middle_finger',
        '_ring_finger',
        '_pinky_finger',
    ]

    _fields_and_field_types = {
        'mode': 'string',
        'thumb_tip': 'int8',
        'thumb_base': 'int8',
        'index_finger': 'int8',
        'middle_finger': 'int8',
        'ring_finger': 'int8',
        'pinky_finger': 'int8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.mode = kwargs.get('mode', str())
        self.thumb_tip = kwargs.get('thumb_tip', int())
        self.thumb_base = kwargs.get('thumb_base', int())
        self.index_finger = kwargs.get('index_finger', int())
        self.middle_finger = kwargs.get('middle_finger', int())
        self.ring_finger = kwargs.get('ring_finger', int())
        self.pinky_finger = kwargs.get('pinky_finger', int())

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
        if self.mode != other.mode:
            return False
        if self.thumb_tip != other.thumb_tip:
            return False
        if self.thumb_base != other.thumb_base:
            return False
        if self.index_finger != other.index_finger:
            return False
        if self.middle_finger != other.middle_finger:
            return False
        if self.ring_finger != other.ring_finger:
            return False
        if self.pinky_finger != other.pinky_finger:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'mode' field must be of type 'str'"
        self._mode = value

    @builtins.property
    def thumb_tip(self):
        """Message field 'thumb_tip'."""
        return self._thumb_tip

    @thumb_tip.setter
    def thumb_tip(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'thumb_tip' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'thumb_tip' field must be an integer in [-128, 127]"
        self._thumb_tip = value

    @builtins.property
    def thumb_base(self):
        """Message field 'thumb_base'."""
        return self._thumb_base

    @thumb_base.setter
    def thumb_base(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'thumb_base' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'thumb_base' field must be an integer in [-128, 127]"
        self._thumb_base = value

    @builtins.property
    def index_finger(self):
        """Message field 'index_finger'."""
        return self._index_finger

    @index_finger.setter
    def index_finger(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'index_finger' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'index_finger' field must be an integer in [-128, 127]"
        self._index_finger = value

    @builtins.property
    def middle_finger(self):
        """Message field 'middle_finger'."""
        return self._middle_finger

    @middle_finger.setter
    def middle_finger(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'middle_finger' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'middle_finger' field must be an integer in [-128, 127]"
        self._middle_finger = value

    @builtins.property
    def ring_finger(self):
        """Message field 'ring_finger'."""
        return self._ring_finger

    @ring_finger.setter
    def ring_finger(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ring_finger' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'ring_finger' field must be an integer in [-128, 127]"
        self._ring_finger = value

    @builtins.property
    def pinky_finger(self):
        """Message field 'pinky_finger'."""
        return self._pinky_finger

    @pinky_finger.setter
    def pinky_finger(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'pinky_finger' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'pinky_finger' field must be an integer in [-128, 127]"
        self._pinky_finger = value
