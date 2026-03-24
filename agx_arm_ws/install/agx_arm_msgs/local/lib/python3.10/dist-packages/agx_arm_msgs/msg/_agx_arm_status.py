# generated from rosidl_generator_py/resource/_idl.py.em
# with input from agx_arm_msgs:msg/AgxArmStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AgxArmStatus(type):
    """Metaclass of message 'AgxArmStatus'."""

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
                'agx_arm_msgs.msg.AgxArmStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__agx_arm_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__agx_arm_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__agx_arm_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__agx_arm_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__agx_arm_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AgxArmStatus(metaclass=Metaclass_AgxArmStatus):
    """Message class 'AgxArmStatus'."""

    __slots__ = [
        '_ctrl_mode',
        '_arm_status',
        '_mode_feedback',
        '_teach_status',
        '_motion_status',
        '_trajectory_num',
        '_err_status',
        '_joint_angle_limit',
        '_communication_status_joint',
    ]

    _fields_and_field_types = {
        'ctrl_mode': 'uint8',
        'arm_status': 'uint8',
        'mode_feedback': 'uint8',
        'teach_status': 'uint8',
        'motion_status': 'uint8',
        'trajectory_num': 'uint8',
        'err_status': 'int64',
        'joint_angle_limit': 'sequence<boolean>',
        'communication_status_joint': 'sequence<boolean>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('boolean')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('boolean')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.ctrl_mode = kwargs.get('ctrl_mode', int())
        self.arm_status = kwargs.get('arm_status', int())
        self.mode_feedback = kwargs.get('mode_feedback', int())
        self.teach_status = kwargs.get('teach_status', int())
        self.motion_status = kwargs.get('motion_status', int())
        self.trajectory_num = kwargs.get('trajectory_num', int())
        self.err_status = kwargs.get('err_status', int())
        self.joint_angle_limit = kwargs.get('joint_angle_limit', [])
        self.communication_status_joint = kwargs.get('communication_status_joint', [])

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
        if self.ctrl_mode != other.ctrl_mode:
            return False
        if self.arm_status != other.arm_status:
            return False
        if self.mode_feedback != other.mode_feedback:
            return False
        if self.teach_status != other.teach_status:
            return False
        if self.motion_status != other.motion_status:
            return False
        if self.trajectory_num != other.trajectory_num:
            return False
        if self.err_status != other.err_status:
            return False
        if self.joint_angle_limit != other.joint_angle_limit:
            return False
        if self.communication_status_joint != other.communication_status_joint:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def ctrl_mode(self):
        """Message field 'ctrl_mode'."""
        return self._ctrl_mode

    @ctrl_mode.setter
    def ctrl_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ctrl_mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'ctrl_mode' field must be an unsigned integer in [0, 255]"
        self._ctrl_mode = value

    @builtins.property
    def arm_status(self):
        """Message field 'arm_status'."""
        return self._arm_status

    @arm_status.setter
    def arm_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'arm_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'arm_status' field must be an unsigned integer in [0, 255]"
        self._arm_status = value

    @builtins.property
    def mode_feedback(self):
        """Message field 'mode_feedback'."""
        return self._mode_feedback

    @mode_feedback.setter
    def mode_feedback(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode_feedback' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode_feedback' field must be an unsigned integer in [0, 255]"
        self._mode_feedback = value

    @builtins.property
    def teach_status(self):
        """Message field 'teach_status'."""
        return self._teach_status

    @teach_status.setter
    def teach_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'teach_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'teach_status' field must be an unsigned integer in [0, 255]"
        self._teach_status = value

    @builtins.property
    def motion_status(self):
        """Message field 'motion_status'."""
        return self._motion_status

    @motion_status.setter
    def motion_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'motion_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'motion_status' field must be an unsigned integer in [0, 255]"
        self._motion_status = value

    @builtins.property
    def trajectory_num(self):
        """Message field 'trajectory_num'."""
        return self._trajectory_num

    @trajectory_num.setter
    def trajectory_num(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'trajectory_num' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'trajectory_num' field must be an unsigned integer in [0, 255]"
        self._trajectory_num = value

    @builtins.property
    def err_status(self):
        """Message field 'err_status'."""
        return self._err_status

    @err_status.setter
    def err_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'err_status' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'err_status' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._err_status = value

    @builtins.property
    def joint_angle_limit(self):
        """Message field 'joint_angle_limit'."""
        return self._joint_angle_limit

    @joint_angle_limit.setter
    def joint_angle_limit(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, bool) for v in value) and
                 True), \
                "The 'joint_angle_limit' field must be a set or sequence and each value of type 'bool'"
        self._joint_angle_limit = value

    @builtins.property
    def communication_status_joint(self):
        """Message field 'communication_status_joint'."""
        return self._communication_status_joint

    @communication_status_joint.setter
    def communication_status_joint(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, bool) for v in value) and
                 True), \
                "The 'communication_status_joint' field must be a set or sequence and each value of type 'bool'"
        self._communication_status_joint = value
