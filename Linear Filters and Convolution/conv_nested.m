% Convolves the image with kernel.
function OutputImg = conv_nested(Img, kernel)

    [kernel_rows, kernel_cols] = size(kernel);
    
    assert(mod(kernel_rows, 2) == 1 && mod(kernel_cols, 2) == 1, ...
        "Kernel size must be odd.");
    
    % determine the image's size: rows, columns
    [rows, cols, depth] = size(Img);
    
    assert(depth == 1, "Grayscale input image is required.");
    
    % kernel center coordinates
    pad_rows = fix(kernel_rows / 2);
    pad_cols = fix(kernel_cols / 2);
    
    % create the resulting image (padded with zeros on borders)
    % 'uint8' type is used (default is double)
    PaddedImg = zeros(rows + kernel_rows - 1, ...
        cols + kernel_cols - 1, 'double');
    
    PaddedImg(pad_rows + 1:rows + pad_rows, ...
        pad_cols + 1:cols + pad_cols) = Img;
    
    OutputImg = zeros(rows, cols,'uint8');
    
    for i = 1:rows
        for j = 1:cols
            for u = -pad_rows:pad_rows
                for v = -pad_cols:pad_cols
                    OutputImg(i, j) = OutputImg(i, j) ... 
                        + kernel(u + pad_rows + 1, v + pad_cols + 1) ...
                        * PaddedImg(i + pad_rows - u, j + pad_cols - v);
                end
            end
        end
    end
    
end
