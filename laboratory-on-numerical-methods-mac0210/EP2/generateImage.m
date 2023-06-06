function generateImage(n)
    imagem = im2double(zeros(n, n, 3, 'uint8'));

    disp(abs(-1));

    for i=1:n
        for j=1:n
            imagem(i, j, 1) = R(i, j);
            imagem(i, j, 2) = G(i, j);
            imagem(i, j, 3) = B(i, j);

        endfor
    endfor

    imwrite(imagem, "imagemTeste.png", "Compression", "none");
endfunction

function r = R(x, y)
    r = tan(x);
endfunction

function g = G(x, y)
    g =  tan(x*y);
endfunction

function b = B(x, y)
    b = tan(x);
endfunction


