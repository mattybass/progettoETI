%TextRead and graphplot
function []=grafico(a,b)
[frame,zenit,azimut] = textread(a,'%f%f%f');
h(1) = figure;
plot(frame,zenit);
hold on;
plot(frame,azimut);
savefig(h,b)
close(h)
figs = openfig(b);
for K = 1 : length(figs)
   filename = 'grafico.pdf';
   saveas(figs(K), filename);
end
