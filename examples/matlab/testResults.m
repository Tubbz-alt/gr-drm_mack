clc
clear
close all

% Cell mapping
fileName = "cellMapping.bin";
Size = 1024;
Ss = 44;
in = 0;
outMapping = read_complex_float( fileName, Size, Ss, in );

% Cell demapping
fileName = "cellDemapping.bin";
Size = 6845;
Ss = 1;
in = 0;
outDemapping = read_complex_float( fileName, Size, Ss, in );

diff = diff(outDemapping);
diffzero = diff - 1;
wrongpos = find(diffzero);
