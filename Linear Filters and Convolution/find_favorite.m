% Finds the location of the template in the image.
function [x_index, y_index] = find_favorite(t, Img)

    % calculate the cross-correlation
    c = xcorr2(t, Img);
    
    % Find the peak in cross-correlation.
    % For this the max values indices are found
    % in the correlation matrix 'c'.
    [y_peak, x_peak] = find(c == max(c(:)));
    
    % consider the template's paddings
    x_index = x_peak - size(t, 2) + 1;
    y_index = y_peak - size(t, 1) + 1;
end