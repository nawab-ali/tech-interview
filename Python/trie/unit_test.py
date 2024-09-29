#!/home/ubuntu/wspace-2/anaconda2/bin/python

import string
import unittest
from Trie import TrieNode
from Trie import Trie
from SuffixTrie import SuffixTrie
from PatternMatching import *

class TestTrieNode(unittest.TestCase):
    def test_raise_exception_if_alphabet_length_less_than_zero(self):
        with self.assertRaises(ValueError):
            _ = TrieNode('a', -1)

    def test_initialize_trie_node_object(self):
        node = TrieNode('a')
        self.assertEqual(node.character, 'a')
        self.assertIsNone(node.value)
        self.assertEqual(node.alphabet_length, 26)
        self.assertEqual(node.children, [None]*26)
        self.assertFalse(node.is_end_of_word)

    def test_initialize_trie_node_object_with_alphabet_length(self):
        node = TrieNode('a', 4)
        self.assertEqual(node.character, 'a')
        self.assertIsNone(node.value)
        self.assertEqual(node.alphabet_length, 4)
        self.assertEqual(node.children, [None]*4)
        self.assertFalse(node.is_end_of_word)

class TestTrie(unittest.TestCase):
    def test_initialize_trie_object(self):
        trie = Trie()
        self.assertIsNone(trie.root.character)
        self.assertIsNone(trie.root.value)
        self.assertEqual(trie.root.children, [None]*26)
        self.assertFalse(trie.root.is_end_of_word)

    def test_initialize_trie_object_with_alphabet_length(self):
        trie = Trie(4)
        self.assertIsNone(trie.root.character)
        self.assertIsNone(trie.root.value)
        self.assertEqual(trie.root.children, [None]*4)
        self.assertFalse(trie.root.is_end_of_word)

    def test_insert_key_with_unique_characters_in_empty_trie(self):
        trie = Trie()
        trie.insert_key(string.ascii_lowercase, 1)
        self.assertEqual(trie.search_key(string.ascii_lowercase), 1)

    def test_insert_key_with_duplicate_characters_in_empty_trie(self):
        trie = Trie()
        trie.insert_key('helloo', 1)
        self.assertEqual(trie.search_key('helloo'), 1)

    def test_insert_multiple_keys_in_trie(self):
        trie = Trie()
        trie.insert_key('their', 1)
        trie.insert_key('there', 2)
        trie.insert_key('answer', 3)
        trie.insert_key('any', 4)
        trie.insert_key('bye', 5)

        self.assertEqual(trie.search_key('their'), 1)
        self.assertEqual(trie.search_key('there'), 2)
        self.assertEqual(trie.search_key('answer'), 3)
        self.assertEqual(trie.search_key('any'), 4)
        self.assertEqual(trie.search_key('bye'), 5)

    def test_insert_empty_key(self):
        trie = Trie()

        with self.assertRaises(ValueError):
            trie.insert_key('', 1)

    def test_search_empty_key(self):
        trie = Trie()

        with self.assertRaises(ValueError):
            trie.search_key('')

    def test_search_key_in_empty_trie(self):
        trie = Trie()
        self.assertIsNone(trie.search_key('hello'))

    def test_search_key_not_in_trie(self):
        trie = Trie()
        trie.insert_key('their', 1)
        trie.insert_key('there', 2)
        trie.insert_key('answer', 3)
        trie.insert_key('any', 4)
        trie.insert_key('bye', 5)

        self.assertIsNone(trie.search_key('hello'))

class TestSuffixTrie(unittest.TestCase):
    def test_raise_exception_if_alphabet_length_less_than_zero(self):
        with self.assertRaises(ValueError):
            suffix_trie = SuffixTrie(-1)

    def test_is_prefix_of_suffix_in_empty_suffix_trie(self):
        suffix_trie = SuffixTrie()
        self.assertFalse(suffix_trie.is_prefix_of_suffix('hello'))

    def test_is_prefix_of_suffix_empty_key(self):
        suffix_trie = SuffixTrie()
        self.assertTrue(suffix_trie.is_prefix_of_suffix(''))

    def test_search_for_prefix_in_suffix_trie(self):
        suffix_trie = SuffixTrie()
        suffix_trie.insert_key('baaba', 1)
        suffix_trie.insert_key('aaba', 2)
        suffix_trie.insert_key('aba', 3)
        suffix_trie.insert_key('ba', 4)
        suffix_trie.insert_key('a', 5)

        self.assertTrue(suffix_trie.is_prefix_of_suffix('baa'))

class TestPatternMatching(unittest.TestCase):
    def test_search_text_for_patterns_with_suffix_trie_text_is_empty(self):
        text = ''
        patterns = ['CGCA', 'CA', 'CAGTA', 'AGTA']

        matches = search_text_for_patterns_with_suffix_trie(text, patterns, 4)
        self.assertEqual([], matches)

    def test_search_text_for_patterns_with_suffix_trie_patterns_is_empty(self):
        text = 'CGCAGTAACA'
        patterns = []

        matches = search_text_for_patterns_with_suffix_trie(text, patterns, 4)
        self.assertEqual([], matches)

    def test_search_text_for_patterns_with_suffix_trie(self):
        text = 'CGCAGTAACA'
        patterns = ['CGCA', 'CA', 'CAGTA', 'AGTA']

        matches = search_text_for_patterns_with_suffix_trie(text, patterns, 4)
        self.assertEqual(patterns, matches)

    def test_search_text_for_patterns_with_suffix_trie_no_match(self):
        text = 'CGCAGTAACA'
        patterns = ['CCA', 'CAT', 'CGTA', 'ATA']

        matches = search_text_for_patterns_with_suffix_trie(text, patterns, 4)
        self.assertEqual([], matches)

    def test_search_text_for_patterns_with_trie_text_is_empty(self):
        text = ''
        patterns = ['CGCA', 'CA', 'CAGTA', 'AGTA']

        matches = search_text_for_patterns_with_trie(text, patterns, 4)
        self.assertEqual([], matches)

    def test_search_text_for_patterns_with_trie_patterns_is_empty(self):
        text = 'CGCAGTAACA'
        patterns = []

        matches = search_text_for_patterns_with_trie(text, patterns, 4)
        self.assertEqual([], matches)

    def test_search_text_for_patterns_with_trie(self):
        text = 'CGCAGTAACA'
        patterns = ['CGCA', 'CA', 'CAGTA', 'AGTA']

        matches = search_text_for_patterns_with_trie(text, patterns, 4)
        self.assertEqual(set(patterns), set(matches))

    def test_search_text_for_patterns_with_trie_no_match(self):
        text = 'CGCAGTAACA'
        patterns = ['CCA', 'CAT', 'CGTA', 'ATA']

        matches = search_text_for_patterns_with_trie(text, patterns, 4)
        self.assertEqual([], matches)

    def test_prefix_trie_matching_text_is_empty(self):
        trie = Trie(4)
        text = ''
        patterns = ['CGCA', 'CGCAGT', 'CGC', 'C']

        for pattern in patterns:
            trie.insert_key(pattern, len(pattern))

        prefix_matches = prefix_trie_matching(text, trie)
        self.assertEqual([], prefix_matches)

    def test_prefix_trie_matching_trie_is_empty(self):
        trie = Trie(4)
        text = 'CGCAGTAACA'

        prefix_matches = prefix_trie_matching(text, trie)
        self.assertEqual([], prefix_matches)

    def test_prefix_trie_matching(self):
        trie = Trie(4)
        text = 'CGCAGTAACA'
        patterns = ['CGCA', 'CGCAGT', 'CGC', 'C']

        for pattern in patterns:
            trie.insert_key(pattern, len(pattern))

        prefix_matches = prefix_trie_matching(text, trie)
        self.assertEqual(['C', 'CGC', 'CGCA', 'CGCAGT'], prefix_matches)

    def test_prefix_trie_matching_pattern_not_found(self):
        trie = Trie(4)
        text = 'CGCAGTAACA'
        patterns = ['ATC', 'CAT', 'CGTA']

        for pattern in patterns:
            trie.insert_key(pattern, len(pattern))

        prefix_matches = prefix_trie_matching(text, trie)
        self.assertEqual([], prefix_matches)

    def test_generate_text_prefixes(self):
        prefixes = generate_text_prefixes('apple')
        self.assertEqual(['a', 'ap', 'app', 'appl', 'apple'], prefixes)

    def test_generate_text_prefixes_empty_text(self):
        prefixes = generate_text_prefixes('')
        self.assertEqual([], prefixes)

    def test_generate_text_suffixes(self):
        suffixes = generate_text_suffixes('apple')
        self.assertEqual(['apple', 'pple', 'ple', 'le', 'e'], suffixes)

    def test_generate_text_suffixes_empty_text(self):
        suffixes = generate_text_suffixes('')
        self.assertEqual([], suffixes)

    def test_multiple_random_genome_sequence_generator_max_sequence_length_less_than_1(self):
        with self.assertRaises(ValueError):
            _ = generate_random_genome_sequences(0, 5)

    def test_multiple_random_genome_sequence_generator_max_sequences_less_than_zero(self):
        with self.assertRaises(ValueError):
            _ = generate_random_genome_sequences(10, -1)

    def test_multiple_random_genome_sequence_generator_max_sequences_is_zero(self):
        sequences = generate_random_genome_sequences(5, 0)
        self.assertEqual([], sequences)

    def test_multiple_random_genome_sequence_generator(self):
        random.seed(10)
        sequences = generate_random_genome_sequences(10, 5)
        self.assertEqual(['CGATTG', 'GC', 'TTA', 'GCCGCGGAT', 'TGAAATCCTC'], sequences)

    def test_random_genome_sequence_generator_raise_exception_if_sequence_length_less_than_one(self):
        with self.assertRaises(ValueError):
            _ = generate_single_random_genome_sequence(0)

    def test_random_genome_sequence_generator_default_sequence_length(self):
        random.seed(10)
        sequence = generate_single_random_genome_sequence()
        self.assertEqual('GCGATTGAGC', sequence)

    def test_random_genome_sequence_generator(self):
        random.seed(10)
        sequence = generate_single_random_genome_sequence(10)
        self.assertEqual('GCGATTGAGC', sequence)

if __name__ == '__main__':
    unittest.main()
