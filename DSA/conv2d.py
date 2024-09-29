# 2D convolution

import numpy as np

def im2col(activation: np.array, kernel: np.array) -> np.array:
    # Dimensions for output given no padding and stride of 1
    output_shape = activation.shape[0] - kernel.shape[0] + 1
    matrix = []
    
    for row in range(output_shape):
        for col in range(output_shape):
            window = activation[row:row+kernel.shape[0], col:col+kernel.shape[1]]
            matrix.append(list(window.flatten()))
    
    return np.transpose(np.array(matrix))

def conv2d(activation: np.array, kernel: np.array, bias: np.array) -> np.array:
    # Dimensions for output given no padding and stride of 1
    output_shape = activation.shape[0] - kernel.shape[0] + 1
    
    activation_matrix = im2col(activation, kernel)
    kernel_flat = kernel.flatten()
    assert kernel_flat.shape[0] == activation_matrix.shape[0]

    output = np.dot(kernel_flat, activation_matrix)
    return output.reshape(output_shape, output_shape) + bias
    
def naive_conv2d(activation: np.array, kernel: np.array, bias: np.array) -> np.array:
    # Dimensions for output given no padding and stride of 1
    output_shape = activation.shape[0] - kernel.shape[0] + 1
    output = np.zeros((output_shape, output_shape))
    
    # Convolve in x and y dimensions
    for row in range(output_shape):
        for col in range(output_shape):
            window = activation[row:row+kernel.shape[0], col:col+kernel.shape[1]]
            # Element-wise multiplication and sum
            output[row, col] = np.sum(window * kernel)

    return output + bias # Add bias (broadcasts automatically)

def main():
    image = np.array([[3., 9., 0.],
                      [2., 8., 1.],
                      [1., 4., 8.]], dtype=np.float32)
    kernel = np.array([[8., 9.],
                       [4., 4.]], dtype=np.float32)
    bias = np.array([0.06], dtype=np.float32)

    print(naive_conv2d(image, kernel, bias))
    print(conv2d(image, kernel, bias))
    print(im2col(image, kernel))

if __name__ == "__main__":
    main()
