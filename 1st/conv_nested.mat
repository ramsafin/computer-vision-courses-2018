% Convolves an image I with kernel k
function J = conv_nested(I, k)

    % the kernel size (in the 1st dimension)
    kernel_size = size(k, 1);
    
    assert(mod(kernel_size, 2) == 1, "Kernel size must be odd.");
    
    % determine the image's size: rows, columns
    [rows, cols, depth] = size(I);
    
    assert(depth == 1, "Grayscale input image is required.");
    
    % init the convolved image (zeros on borders)
    % 'uint8' type is used (default is double)
    J = zeros(rows, cols, 'uint8');
    
    % find padding for the image
    padding = fix(kernel_size / 2);
    
    for i = (1 + padding):(rows - padding)
        for j = (1 + padding):(cols - padding)
            kernel_sum = 0;
            for u = -padding:padding
                for v = -padding:padding
                    % correspondant image and kernel elements product sum
                    kernel_sum = kernel_sum + k(u + padding + 1, v + padding + 1) * I(i - u, j - v);
                end
            end
            % apply the kernel to the image's pixel
            J(i, j) = kernel_sum;
        end
    end
end
