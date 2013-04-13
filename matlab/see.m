% ------------------------------------------------------------------------ % The Gabor.R and Gabor.I are stored as floating number.You can % use Xsee to view them.Xsee is implemented by one of the former % students in the image processing lab(IPL) at UCSB, and it is publicly % available.You may want to contact IPL
%for this software
%if you % need it. % % You can also use matlab to view it.The following is the codes
%for % showing the images in matlab. % ------------------------------------------------------------------------ % The same parameters in the file xgabor.c
side = 60;
scale = 3;
orientation = 8; % Procedure to read the Gabor filters
wid = (2 * side + 1) * (orientation);
hei = (2 * side + 1) * (scale);
% fid = fopen('Gabor.R', 'r');
% A = fread(fid, [wid hei], 'float')';
% fclose(fid);

% Procedure to read the outputs
imghei = 900; % height of input image
imgwid = 335; % width of input image
wid = imgwid*(orientation);
hei = imghei*(scale);
fid=fopen('Output.R','r');
A=fread(fid,[wid hei],'float')'; 
fclose(fid);
% fid=fopen('Output.I','r');
% A2=fread(fid,[wid hei],'float')'; 
% fclose(fid);
% A=sqrt(A1.^2+A2.^2);
% the floating number to[0, 255]
A_max = max(max(A));
A_min = min(min(A));
imagedata = fix(255 * (A - (A_min * ones(size(A)))) / (A_max - A_min));
colormap(gray(256));
image(imagedata);
axis equal;