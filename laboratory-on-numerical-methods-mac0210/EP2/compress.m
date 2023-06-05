# Nome: Beatriz Viana Costa
# NUSP: 13673214

function compress (originalImg, k)
    # originalImg é p nome da imagem original que será comprimida
    # k é a taxa de compressão, ou seja, número de linhas e colunas que serão removidas respectivamente 
    
    Img = imread(originalImg);

    p = size(Img);

    n1 = round((p(1)+k)/(k+1));
    n2 = round((p(2)+k)/(k+1));

    m = resize(Img, n1, n2, 3);

    for i=1:(k+1):p(1)
        for j=1:(k+1):p(2)
            m(round((i-1)/(k+1) + 1), round((j-1)/(k+1) + 1), :) = Img(i, j, :);
        endfor
    endfor
    
    imwrite(m, "compressed.png", "Compression","none");
endfunction 