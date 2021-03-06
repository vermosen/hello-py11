# -*- coding: utf-8 -*-
import unittest

import numpy as np
import habu as m

from datetime import datetime

class test_numpy(unittest.TestCase):

    def test_date_to_int(self):

      dt = np.datetime64('2021-10-10')
      ctr = m.date_to_int(dt)
      self.assertEqual(type(ctr), int)
      self.assertEqual(ctr, 18910)
      
    def test_int_to_date(self):

      ctr = 12000      
      dt = m.int_to_date(ctr)
      self.assertEqual(type(dt), np.datetime64)
      self.assertEquals(dt, np.datetime64('2002-11-09'))

    def test_dates_to_ints(self):

      inn = np.array([np.datetime64('2021-10-10'), np.datetime64('2021-10-11')])
      ctrs = m.dates_to_ints(inn)
      self.assertEqual(type(ctrs), list)
      self.assertEqual(len(ctrs), 2)
      self.assertEquals(ctrs[0], 18910)
      self.assertEquals(ctrs[1], 18911)

    def test_ints_to_dates(self):

      inn = [18910, 18911]
      ctrs = m.ints_to_dates(inn)
      self.assertEqual(type(ctrs), np.ndarray)
      tt = ctrs.dtype
      self.assertEqual(ctrs.dtype, '<M8[D]')
      self.assertEqual(len(ctrs), 2)
      self.assertEquals(ctrs[0], np.datetime64('2021-10-10'))
      self.assertEquals(ctrs[1], np.datetime64('2021-10-11'))
     
    def test_refcount_ints_to_dates(self):

      import sys

      obj = m.ints_to_dates([18910])
      count = sys.getrefcount(obj) - 1
      self.assertEqual(count, 1)

    def test_overload_func(self):

      t1 = m.int_to_date_uni(10012)
      t2 = m.int_to_date_uni([10012])

      self.assertEqual(type(t1), np.datetime64)
      self.assertEqual(type(t2), np.ndarray)
      self.assertEqual(len(t2), 1)
      

if __name__ == '__main__':
    unittest.main()