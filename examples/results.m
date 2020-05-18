clc
clear
close all

% msc in
fileName = "in.bin";
Size = 7011;
Ss = 1;
in = 0;
msc_in = read_complex_float( fileName, Size, Ss, in );

% mapping
fileName = "mapping.bin";
Size = 1024;
Ss = 75;
in = 0;
mapping = read_complex_float( fileName, Size, Ss, in );

% msc out
fileName = "demapping.bin";
Size = 7011;
Ss = 18;
in = 0;
msc_out = read_complex_float( fileName, Size, Ss, in );

error = msc_in - msc_out;
wrongpos = find(error);
