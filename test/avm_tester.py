#!/usr/bin/python3
#!/

import os
import unittest
from contextlib import contextmanager

from ShellOutput import ShellOutput

EXECUTABLE = "../bin/avm"

def print_header(str):
	print("----------------------------------------------------------------------")
	print("     Testing " + str)
	print("----------------------------------------------------------------------")

def get_output(file):
	with ShellOutput() as out:
		os.system(EXECUTABLE + " files/" + file)
	return out.capturedtext

class Test_01_Push(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		print_header("Push")

	def test_push_basic(self):
		return self.assertEqual(get_output("test_push_basic"), "42.420000\n42.419998\n42424242\n500\n5\n")
	
	def test_push_empty(self):
		return self.assertEqual(get_output("test_push_empty"), "\x1b[91mError:\x1b[0m Invalid syntax on line 1\n")

	def test_push_error_syntax_01(self):
		return self.assertEqual(get_output("test_push_error_syntax_01"), "\x1b[91mError:\x1b[0m Invalid syntax on line 1\n")

	def test_push_error_syntax_02(self):
		return self.assertEqual(get_output("test_push_error_syntax_02"), "\x1b[91mError:\x1b[0m Invalid syntax on line 1\n")
	
	def test_push_error_syntax_03(self):
		return self.assertEqual(get_output("test_push_error_syntax_03"), "\x1b[91mError:\x1b[0m Invalid syntax on line 1\n")

	@classmethod
	def tearDownClass(cls):
		print("")

class Test_02_Pop(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		print_header("Pop")

	def test_pop_basic(self):
		return self.assertEqual(get_output("test_pop_basic"), "42\n")
	
	def test_pop_empty(self):
		return self.assertEqual(get_output("test_pop_empty"), "\x1b[91mError:\x1b[0m Stack is empty\n")

	@classmethod
	def tearDownClass(cls):
		print("")

class Test_03_Dump(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		print_header("Dump")

	def test_dump_basic(self):
		return self.assertEqual(get_output("test_dump_basic"), "5\n42\n5\n42\n5\n")
	
	def test_dump_empty(self):
		return self.assertEqual(get_output("test_dump_empty"), "")

	@classmethod
	def tearDownClass(cls):
		print("")

class Test_04_Assert(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		print_header("Assert")

	def test_assert_basic(self):
		return self.assertEqual(get_output("test_assert_basic"), "32\n42.420000\n32\n")

	def test_assert_empty(self):
		return self.assertEqual(get_output("test_assert_empty"), "\x1b[91mError:\x1b[0m Stack is empty\n")
	
	def test_assert_error_01(self):
		return self.assertEqual(get_output("test_assert_error_01"), "\x1b[91mError:\x1b[0m Invalid syntax on line 2\n")

	def test_assert_error_02(self):
		return self.assertEqual(get_output("test_assert_error_02"), "\x1b[91mError:\x1b[0m Invalid syntax on line 2\n")

	def test_assert_error_03(self):
		return self.assertEqual(get_output("test_assert_error_03"), "\x1b[91mError:\x1b[0m Operand type does not match\n")

	def test_assert_error_04(self):
		return self.assertEqual(get_output("test_assert_error_04"), "\x1b[91mError:\x1b[0m Operand value does not match\n")

	@classmethod
	def tearDownClass(cls):
		print("")

class Test_05_Add(unittest.TestCase):
	
	@classmethod
	def setUpClass(cls):
		print_header("Add")
	
	def test_add_basic(self):
		return self.assertEqual(get_output("test_add_basic"), "84\n100\n")

	def test_add_empty(self):
		return self.assertEqual(get_output("test_add_empty"), "\x1b[91mError:\x1b[0m Stack does not have sufficient operands\n")

	def test_add_error_01(self):
		return self.assertEqual(get_output("test_add_error_01"), "\x1b[91mError:\x1b[0m Stack does not have sufficient operands\n")

	def test_add_overflow_01(self):
		return self.assertEqual(get_output("test_add_overflow_01"), "\x1b[91mError:\x1b[0m Addition Overflow\n")

	def test_add_overflow_02(self):
		return self.assertEqual(get_output("test_add_overflow_02"), "32772\n32772\n32772\n")

	def test_add_types(self):
		return self.assertEqual(get_output("test_add_types"), "75.900000\n")

	def test_add_underflow_01(self):
		return self.assertEqual(get_output("test_add_underflow_01"), "\x1b[91mError:\x1b[0m Addition Underflow\n")

	def test_add_underflow_02(self):
		return self.assertEqual(get_output("test_add_underflow_02"), "-133\n-10000132\n")

	@classmethod
	def tearDownClass(cls):
		print("")

class Test_06_Subtract(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		print_header("Subtract")

	def test_subtract_basic(self):
		return self.assertEqual(get_output("test_subtract_basic"), "-28.700000\n")
	
	def test_subtract_empty(self):
		return self.assertEqual(get_output("test_subtract_empty"), "\x1b[91mError:\x1b[0m Stack does not have sufficient operands\n")
	
	def test_subtract_error_01(self):
		return self.assertEqual(get_output("test_subtract_error_01"), "\x1b[91mError:\x1b[0m Stack does not have sufficient operands\n")

	def test_subtract_overflow_01(self):
		return self.assertEqual(get_output("test_subtract_overflow_01"), "\x1b[91mError:\x1b[0m Subtraction Overflow\n")

	def test_subtract_overflow_02(self):
		return self.assertEqual(get_output("test_subtract_overflow_02"), "32772\n32772\n32772\n")
	
	def test_subtract_types(self):
		return self.assertEqual(get_output("test_subtract_types"), "-22.500000\n-27.900000\n")

	def test_subtract_underflow_01(self):
		return self.assertEqual(get_output("test_subtract_underflow_01"), "\x1b[91mError:\x1b[0m Subtraction Underflow\n")

	def test_subtract_underflow_02(self):
		return self.assertEqual(get_output("test_subtract_underflow_02"), "-133\n-10000132\n")

	@classmethod
	def tearDownClass(cls):
		print("")

class Test_07_Multiply(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		print_header("Multiply")

	def test_multiply_basic(self):
		return self.assertEqual(get_output("test_multiply_basic"), "1764\n")

	def test_multiply_empty(self):
		return self.assertEqual(get_output("test_multiply_empty"), "\x1b[91mError:\x1b[0m Stack does not have sufficient operands\n")

	def test_multiply_error_01(self):
		return self.assertEqual(get_output("test_multiply_error_01"), "\x1b[91mError:\x1b[0m Stack does not have sufficient operands\n")

	def test_multiply_overflow_01(self):
		return self.assertEqual(get_output("test_multiply_overflow_01"), "\x1b[91mError:\x1b[0m Multiplication Overflow\n")
	
	def test_multiply_overflow_02(self):
		return self.assertEqual(get_output("test_multiply_overflow_02"), "500\n-2500\n500\n")

	def test_multiply_types(self):
		return self.assertEqual(get_output("test_multiply_types"), "4242000.000000\n")

	def test_multiply_underflow_01(self):
		return self.assertEqual(get_output("test_multiply_underflow_01"), "\x1b[91mError:\x1b[0m Multiplication Underflow\n")

	@classmethod
	def tearDownClass(cls):
		print("")

if __name__ == '__main__':
	print("----------------------------------------------------------------------\n")
	print("     Initializing Abstract VM Unit Test ...\n")
	print("----------------------------------------------------------------------\n")
	unittest.main(verbosity=2)