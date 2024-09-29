""" Implement the SuffixTrie data structure. """

from Trie import Trie

class SuffixTrie(Trie):
    def __init__(self, alphabet_length=26):
        """
        Initialize SuffixTrie object.

        Arguments:
        self
        alphabet_length -- number of characters in the alphabet

        Returns:
        None
        """

        super(SuffixTrie, self).__init__(alphabet_length)

    def is_prefix_of_suffix(self, key):
        """
        Is key a prefix of some suffix of text in the suffix trie?

        Arguments:
        self
        key -- string to be searched

        Returns:
        True if key is a prefix of some suffix of text in the suffix trie, else
        False
        """

        current_node = self.root

        for character in key:
            child = self._search_character_in_node_children(current_node,
                                                            character)
            if child is not None:
                current_node = child
            else:
                return False

        return True
