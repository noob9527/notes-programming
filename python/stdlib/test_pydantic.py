import unittest
from typing import Generic, TypeVar, Optional, Any
from typing import get_args, get_origin

from pydantic import BaseModel

T = TypeVar('T')


class MyClass1(BaseModel, Generic[T]):  # Multiple inheritance
    value: Optional[T] = None  # Field using the generic type variable

    def __init__(self, /, **data: Any):
        super().__init__(**data)
        field_type = self.model_fields['value'].annotation

        print(f"__init__: Field 'value' Type: {field_type}")  # Should print: <class 'int'>

    def __init_subclass__(cls) -> None:
        field_type = cls.model_fields['value'].annotation

        print(f"__init_subclass__: Field 'value' Type: {field_type}")  # Should print: <class 'int'>

    def foo(self):
        field_type = self.__class__.model_fields['value'].annotation

        print(f"Field 'value' Type: {field_type}")  # Should print: <class 'int'>


class IntClass1(MyClass1[int]):  # Specializing T with int
    bar: str = 'bar'


class GenericTestCase(unittest.TestCase):
    # https://github.com/pydantic/pydantic/issues/8410
    def test_orig_bases(self):
        # Get the first base class (MyClass[int])
        generic_base = IntClass1.__orig_bases__[0]

        # Extract the original class without generics (MyClass)
        origin = get_origin(generic_base)

        # Extract the actual type arguments (int)
        args = get_args(generic_base)

        print(f"Original Base: {origin}")  # MyClass
        print(f"Generic Arguments: {args}")  # ()

    def test_field_type(self):
        # Access the type of the 'value' field
        field_type = IntClass1.model_fields['value'].annotation
        type_args = get_args(field_type)[0]
        print(f"T Type: {type_args}")

        print(f"Field 'value' Type: {field_type}")  # Should print: <class 'int'>

        # Assertion for testing purposes
        self.assertEqual(type_args, int)

    def test_instance(self):
        instance = IntClass1()
        instance.foo()
