function []=graficocoordinate(a,b)
[x,z,y] = textread(strcat(a,'.txt'),'%f%f%f');
h(1) = figure;
frame=1:1800;
plot(frame,x);
hold on;
plot(frame,y);
hold on;
plot(frame,z);
savefig(h,strcat(b,'.fig'));
close(h);
figs = openfig(b);
for K = 1 : length(figs)
   filename = strcat(b,'.pdf');
   saveas(figs(K), filename);
end
close(h);
