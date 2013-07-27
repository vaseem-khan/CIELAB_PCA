face=imread('face.jpg');
R=face(:,:,1);
G=face(:,:,2);
x=R(:);
y=G(:);
data=[x,y];
file= fopen('Matlab output.txt','w');
fprintf(file,'%d %d\n',data);
fclose(file);