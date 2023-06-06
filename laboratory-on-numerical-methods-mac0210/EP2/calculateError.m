# Nome: Beatriz Viana Costa
# NUSP: 13673214

function calculateError(originalImg, decompressedImg)

    orig = im2double(imread(originalImg));
    dec = im2double(imread(decompressedImg));

    err = errR = errG = errB = 0;

    p1 = size(dec);
    p2 = size(orig);

    n = min(p1(1), p2(1));

    #disp(size(dec));
    #disp(size(orig));

    # calcula o erro para imagens coloridas
    for i=1:n
        for j=1:n

        errR += (orig(i, j, 1) - dec(i, j, 1))^2;
        errG += (orig(i, j, 2) - dec(i, j, 2))^2; 
        errB += (orig(i, j, 3) - dec(i, j, 3))^2;

        endfor
    endfor

        errR *= (1/n^2);
        errG *= (1/n^2);
        errB *= (1/n^2);

    err = (sqrt(errR) + sqrt(errG) + sqrt(errB))/3;

    disp(err);

endfunction