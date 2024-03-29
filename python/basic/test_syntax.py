import unittest


class SyntaxTestCase(unittest.TestCase):
    def testForLoop(self):
        arr1 = [1,2,3]
        arr2 = [ele * 2 for ele in arr1]
        print(arr2)

    def testForLoopWithIndex(self):
        arr1 = ['a', 'b', 'c']
        arr2 = [(index, ele) for index, ele in enumerate(arr1)]
        print(arr2)

    def testElseInLoop(self):
        # for/while循环可以使用else子句，它仅在没有使用break时调用
        for i in range(10):
            foo = 'bar'
        else:
            foo = 'foo'
        for i in range(10):
            bar = 'bar'
            break
        else:
            bar = 'foo'
        self.assertEqual(foo, 'foo')
        self.assertEqual(bar, 'bar')

    # https://docs.python.org/3/reference/compound_stmts.html#with
    # https://docs.python.org/3/reference/datamodel.html#context-managers
    # https://docs.python.org/3/library/stdtypes.html#typecontextmanager
    # http://effbot.org/zone/python-with-statement.htm
    def testWith(self):
        class context_manager:
            def __enter__(self):
                return 'foo'

            def __exit__(self, exc_type, exc_val, exc_tb):
                return None

        with context_manager() as foo:
            self.assertEqual(foo, 'foo')
