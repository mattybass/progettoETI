function []=differenzaduegrafici(a,c,b)
[frame,zenit,azimut] = textread(a,'%f%f%f');
h(1) = figure;
plot(frame,zenit);
hold on;
plot(frame,azimut);
[framee,zenitt,azimutt] = textread(c,'%f%f%f');
plot(framee,zenitt);
hold on;
plot(framee,azimutt);
savefig(h,b)
close(h)
figs = openfig(b);
for K = 1 : length(figs)
   filename = 'grafico.pdf';
   saveas(figs(K), filename);
end
