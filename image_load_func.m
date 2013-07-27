function [ data ] = image_load_func(src)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
rgbI = imread(src);

%convert to lab
labTransformation = makecform('srgb2lab');
labI = applycform(rgbI,labTransformation);

%seperate l,a,b
l = labI(:,:,1);
a = labI(:,:,2);
b = labI(:,:,3);
x=a(:);
y=b(:);
data=[x,y];
file= fopen('Matlab output22.txt','w');
fprintf(file,'%d %d\n',data);
fclose(file);
figure, imshow(l) , title('l');
figure, imshow(a) , title('a');
figure, imshow(b) , title('b');

end

