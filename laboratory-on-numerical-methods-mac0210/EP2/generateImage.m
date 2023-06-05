function generateImage(n)
    imagem = im2double(zeros(n, n, 3, 'uint8'));

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
    r = sinh(x * pi) + 10 *pi ;
endfunction

function g = G(x, y)
    g = tanh(x + y) + 10 *pi + co;
endfunction

function b = B(x, y)
    b = cosh(x * pi);
endfunction


