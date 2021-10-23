# -*- coding: utf-8 -*-
import unittest

import habu as m

class basic_test(unittest.TestCase):

    def test_version(self):
        self.assertEqual(m.__version__, "0.0.1")

    def test_add(self):
        self.assertEqual(m.add(1, 2), 3)

    def test_sub(self):
        self.assertEqual(m.subtract(1, 2), -1)

if __name__ == '__main__':
    unittest.main()