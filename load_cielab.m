function [ data ] = load_cielab(src)
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
file= fopen('5.txt','w');
fprintf(file,'%d %d\n',data);
fclose(file);
end