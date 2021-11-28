# -*- coding: utf-8 -*-
import unittest

import numpy as np
import habu as m

class test_numpy(unittest.TestCase):

    def test_date_atom(self):

      dt = np.datetime64('2021-10-10')
      m.date_atom(m)
      self.assertTrue(True)
      

if __name__ == '__main__':
    unittest.main()