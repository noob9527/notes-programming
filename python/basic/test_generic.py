import unittest
from typing import Generic, TypeVar
from typing import get_args, get_origin

T = TypeVar('T')


class BaseModel:
    pass


class MyClass(BaseModel, Generic[T]):  # Multiple inheritance
    pass


class IntClass(MyClass[int]):  # Specializing T with int
    pass


class GenericTestCase(unittest.TestCase):
    def test_orig_bases(self):
        # Get the first base class (MyClass[int])
        generic_base = IntClass.__orig_bases__[0]

        # Extract the original class without generics (MyClass)
        origin = get_origin(generic_base)  # Equivalent to MyClass

        # Extract the actual type arguments (int)
        args = get_args(generic_base)  # Equivalent to (int,)

        print(f"Original Base: {origin}")  # MyClass
        print(f"Generic Arguments: {args}")  # (int,)
        print(f"Resolved Generic Type: {args[0]}")  # int
