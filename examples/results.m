clc
clear
close all

% msc in
fileName = "in.bin";
Size = 7011;
Ss = 1;
in = 0;
msc_in = read_complex_float( fileName, Size, Ss, in );

% msc out
fileName = "out.bin";
Size = 7011;
Ss = 10;
in = 0;
msc_out = read_complex_float( fileName, Size, Ss, in );

error = msc_in - msc_out;
wrongpos = find(error);
