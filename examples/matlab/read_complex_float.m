function out=read_complex_float(fileName, Size, Ss, in)
% function to read complex float files
% out=read_complex_float(fileName, Mode, Ss, in)
% fileName: File Name
% Size: Numer of samples to read in a OFDM symbol
% Offset: Number of OFDM symbols offset
% Ss: Number of OFDM symbols to read

skip=Size*in*2*4;%(4->float)
fid = fopen(fileName, 'r');
fseek(fid,skip,-1);
data= fread(fid, Size*Ss*2, 'float');
datac=[data(1:2:end)+data(2:2:end)*i];
fclose(fid);

out=reshape(datac,Size,Ss);