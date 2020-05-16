clear;
mscSize = 7011;
in = [[1:mscSize]; zeros(1,mscSize)];

filename = "in.bin";
fid = fopen(filename, "w");

fwrite(fid, in, "float32");

fclose(fid);