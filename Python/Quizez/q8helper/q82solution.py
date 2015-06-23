from bag import Bag
import unittest   #use unittest.TestCase
import random     #use random.shuffle, random.randint


class Test_Bag(unittest.TestCase):
    def setUp(self):
        self.original = ['d', 'a', 'b', 'd', 'c', 'b', 'd']
        self.bag = Bag(['d', 'a', 'b', 'd', 'c', 'b', 'd'])
        
    def test_len(self):
        self.assertEqual(len(self.bag), 7, msg = "Length of constructed bag is not 7.")
        
        my_list = self.original.copy()
        for i in range(6, -1, -1):
            s = random.choice(my_list)
            self.bag.remove(s)
            my_list.remove(s)
            self.assertEqual(len(self.bag), i, msg = "Length of constructed bag is not " + str(i) +".")
            
        self.assertEqual(len(self.bag), 0, msg = "Final length of constructed bag is not 0.")
        
    def test_unique(self):
        comp_set = set(self.original)
        self.assertIs(self.bag.unique(), 4, msg = "Bag is not unique.")
        my_list = self.original.copy()
        while len(comp_set) != 0:
            s = random.choice(my_list)
            self.bag.remove(s)
            my_list.remove(s)
            comp_set = set(my_list)
            self.assertIs(self.bag.unique(), len(comp_set), msg = "Bag is not unique.")
        
    def test_contains(self):
        comp_set = ['a', 'b', 'c', 'd']
        while len(comp_set) != 0:
            self.assertTrue(Bag.__contains__(self.bag, comp_set[0]), "'{}' not in bag.".format(str(comp_set[0])))
            comp_set.remove(comp_set[0])
        self.assertFalse(Bag.__contains__(self.bag, 'x'), "'x' is in bag.")
        
    def test_count(self):
        self.assertEqual(self.bag.count('a'), 1, msg = "count('a') should be 1")
        self.assertEqual(self.bag.count('b'), 2, msg = "count('b') should be 2")
        self.assertEqual(self.bag.count('c'), 1, msg = "count('c') should be 1")
        self.assertEqual(self.bag.count('d'), 3, msg = "count('d') should be 3")
        self.assertEqual(self.bag.count('x'), 0, msg = "count('x') should be 0")
        
        total_count = self.bag.count('a') + self.bag.count('b') + self.bag.count('c') + self.bag.count('d')
        my_list = self.original.copy()
        while total_count != 0:
            total_count -= 1
            s = random.choice(my_list)
            self.bag.remove(s)
            my_list.remove(s)
            self.assertEqual(self.bag.count('a') + self.bag.count('b') + self.bag.count('c') + self.bag.count('d'), total_count, "Sum of counts not equal " + str(total_count))
        self.assertEqual(self.bag.count('a') + self.bag.count('b') + self.bag.count('c') + self.bag.count('d'), total_count, "Final sum of counts not equal to 0.")
        
    def test_equal(self):
        to_bag = [random.randrange(1, 11) for i in range(1000)]
        bag1 = Bag(to_bag)
        bag2 = Bag(to_bag)
        self.assertEqual(bag1, bag2, "Bags are not equal.")
        bag1.remove(to_bag[0])
        self.assertNotEqual(bag1, bag2, "Bags should not be equal.")
        
    def test_add(self):
        to_bag = [random.randrange(1, 11) for i in range(1000)]
        bag1 = Bag(to_bag)
        random.shuffle(to_bag)
        bag2 = Bag()
        for i in to_bag:
            bag2.add(i)
        self.assertEqual(bag1, bag2, "Bags are not equal.")
        
    def test_remove(self):
        to_bag = [random.randrange(1, 11) for i in range(1000)]
        bag1 = Bag(to_bag)
        self.assertRaises(ValueError, Bag.remove, bag1, 32)
        bag2 = Bag(to_bag)
        for i in to_bag:
            bag2.add(i)
        for i in to_bag:
            bag2.remove(i)
        self.assertEqual(bag1, bag2, "Bags are not equal.")
        
        