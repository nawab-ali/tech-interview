
class Container:
    """
    A container of integers that should support
    addition, removal, and search for the median integer
    """
    def __init__(self):
        self.data = []

    def add(self, value: int) -> None:
        """
        Adds the specified value to the container

        :param value: int
        """
        self.data.append(value)

    def delete(self, value: int) -> bool:
        """
        Attempts to delete one item of the specified value from the container

        :param value: int
        :return: True, if the value has been deleted, or
                 False, otherwise.
        """
        if value in self.data:
            self.data.remove(value)
            return True
        else:
            return False

    def get_median(self) -> int:
        """
        Finds the container's median integer value, which is
        the middle integer when the all integers are sorted in order.
        If the sorted array has an even length,
        the leftmost integer between the two middle 
        integers should be considered as the median.

        :return: The median if the array is not empty, or
        :raise:  a runtime exception, otherwise.
        """
        if self.data:
            size = len(self.data)
            self.data.sort()
            
            if not size % 2:
                # Array has an even length
                idx = (size // 2) - 1
            else:
                # Array has an odd length
                idx = size // 2
            
            return self.data[idx]
        else:
            raise ValueError('Array is empty')
    