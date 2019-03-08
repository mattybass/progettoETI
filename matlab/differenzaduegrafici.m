function []=differenzaduegrafici(a,c,b)
[frame,zenit,azimut] = textread(strcat(a,'.txt'),'%f%f%f');
h(1) = figure;
plot(frame,zenit);
hold on;
plot(frame,azimut);
[framee,zenitt,azimutt] = textread(strcat(c,'.txt'),'%f%f%f');
plot(framee,zenitt);
hold on;
plot(framee,azimutt);
savefig(h,strcat(b,'.fig'));
close(h)
figs = openfig(b);
for K = 1 : length(figs)
   filename = strcat(b,'.pdf');
   saveas(figs(K), filename);
end
