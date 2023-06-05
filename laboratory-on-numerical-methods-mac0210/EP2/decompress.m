# Nome: Beatriz Viana Costa
# NUSP: 13673214

function decompress(compressedImg, method, k, h)
    compImg = imread(compressedImg); 
    compImg = im2double (compImg);

    # separando os canais de cada cor
    R = compImg(:,:,1);
    G = compImg(:, :, 2);
    B = compImg(:, :, 3); 

    # a interpolação é feita para os três canais
    if (method == 1)
        Rimg = Bilinear(R, h, k);
        Gimg = Bilinear(G, h, k);
        Bimg = Bilinear(B, h, k);
    
    elseif (method == 2)
        Rimg = Bicubica(R, h, k);
        Gimg = Bicubica(G, h, k);
        Bimg = Bicubica(B, h, k);
    endif

    # os três canais resultantes são juntos
    decompressedImg = cat(3, Rimg, Gimg, Bimg);
    imwrite (decompressedImg, "decompressed.png", "Compression", "none");
  
endfunction

function ImgFinal = Bilinear (Img, h, k)
    A = [ 1, 0, 0,  0;
          1, 0, h,  0;
          1, h, 0,  0;
          1, h, h, h^2 ];

    n = size(Img);

    # coloca o espaçamento certo de k linha e colunas entre cada linha e coluna da matriz
    tam = n(1) + k* (n(1)-1);
    FinalImg = zeros(tam);
    FinalImg (1:k+1:end,1:k+1:end) = Img(:,:);  

    # interpola o ponto (x,y) da nova linha/coluna adicionada
    indexI = 1;

    for i = 1:(n(1)-1)
        indexJ = 1;

        for j = 1:(n(1)-1)
            Qij = quadQij(i,j);
            FinalImg(indexI:(indexI+k), indexJ:(indexJ+k)) = Qij(:,:);
            indexJ += k+1;
        endfor
        indexI += k+1;
    endfor

    function Qij = quadQij(i, j)
      coef = CoefsA(i,j);
      xi = Img(i,j);
      yj = Img(i,j);
    
      p = 0:k;
    
      xp = xi + p * (h/(k+1));
      yp = yj + p * (h/(k+1));  
      Qij = [];
      for ii = 1:k+1
        line = [];
        for jj = 1:k+1
          line = [line, Poli(xi, yj, coef, xp(ii), yp(jj))];
        endfor
        Qij = [Qij; line];
      endfor 
    endfunction
  
    # calcula o polinomio com os coeficientes encontrados
    function pij = Poli(xi, yj, coef, x,y)
        # relação de pij dada no enunciado
        pij = coef(1)+coef(2)*(x-xi)+coef(3)*(y-yj)+coef(4)*(x-xi)*(y-yj);
    endfunction
      
    function coef = CoefsA(i, j)
    # calcula a matriz de coeficente segundo o sistema dado no enunciado
    # Ax = b -> x = A\b
        b = [ Img(i,j);
              Img(i,j+1); 
              Img(i+1,j); 
              Img(i+1,j+1) ];

        b = double (b);
        coef = A \ b;
    endfunction  
  
  ImgFinal = FinalImg;
endfunction

function ImgFinal = Bicubica (Img, h, k)
    B = [ 1, 0,  0, 0;
          1,  h, h*h, h*h*h;
          0, 1, 0, 0;
          0, 1, 2*h, 3*h*h ]; 
  
    n = size(Img);

    # coloca o espaçamento certo de k linha e colunas entre cada linha e coluna da matriz
    tam = n(1) + k* (n(1)-1);
    FinalImg = zeros (tam);
    FinalImg (1:k+1:end,1:k+1:end) = Img(:,:);  
  
    # interpola o ponto (x,y) da nova linha/coluna adicionada
    indexI = 1;
    for i = 1:n(1)-1
        indexJ = 1;
        for j = 1:n(1)-1
            Qij = quadQij(i,j);
            # preenche as linhas e colunas que foram interpoladas
            FinalImg (indexI:(indexI+k), indexJ:(indexJ+k)) = Qij(:,:);
            indexJ += k+1;
        endfor
        indexI += k+1;
    endfor
  
    function Qij = quadQij(i, j)
        coef = CoefsA(i,j);

        xi = Img(i,j);
        yj = Img(i,j);

        p = 0:k;

        xp = xi + p * (h/(k+1));
        yp = yj + p * (h/(k+1));

        Qij = [];
        for ii = 1:k+1
            line = [];
            for jj = 1:k+1
                line = [line, Poli(xi, yj, coef, xp(ii), yp(jj))];
            endfor
            Qij = [Qij; line];
        endfor 
    endfunction

    function coefs = CoefsA(i, j)
        # matriz de derivadas
        fs = [ Img(i,j), Img(i,j+1), dDy(i,j), dDy(i,j+1);
              Img(i+1,j), Img(i+1,j+1), dDy(i+1,j), dDy(i+1,j+1);
              dDx(i,j), dDx(i,j+1), dDxy(i,j), dDxy(i,j+1);
              dDx(i+1,j), dDx(i+1,j+1), dDxy(i+1,j), dDxy(i+1,j+1) ];

        fs = double(fs);

        # relação fornecida no enunciado para encontrar os coeficientes
        coefs = inv(B) * fs *  inv(transpose(B));
    endfunction  
  
    # calcula a derivada em relação à x
    function d = dDx(i, j)
        # não está nas bordas    
        if (i != 1 && i != n(1))
            d = (Img(i+1,j) - Img(i-1,j)) / (2*h);

        # i está na borda de baixo
        elseif (i != 1)
            d = (Img(i,j) - Img(i-1,j)) / (2*h);

        # i está na borda de cima
        else
            d = (Img(i+1,j) - Img(i,j)) / (2*h);
        endif
    endfunction

    # calcula a derivada em relação à y
    function d = dDy(i, j)
        global t;
        
        # j não está nas bordas
        if (j != 1 && j != n(1))
            d = (Img(i,j+1) - Img(i,j-1)) / (2*h);
        
        # j está na borda da direita
        elseif (j != 1)
            d = (Img(i,j) - Img(i,j-1)) / (2*h);

        # j está na borda da esquerda
        else
            d = (Img(i,j+1) - Img(i,j)) / (2*h);
        endif
    endfunction

    # calcula a derivada em relação à x e y
    function d = dDxy(i, j)

        # i não está nas bordas
        if (i != 1 && i != n(1))
            d = (dDy(i+1,j) - dDy(i-1,j))/(2*h);

        # i está na borda de baixo
        elseif (i != 1)
            d = (dDy(i,j) - dDy(i-1,j))/(2*h);

        # i está na borda de cima
        else
            d = (dDy(i+1,j) - dDy(i,j))/(2*h);
        endif
    endfunction 

    # calcula o polinomio com os coeficientes encontrados
    function pij = Poli(xi, yj, coefs, x,y)
        # relação po polinomio pij dada no enunciado
        pij = [1, (x - xi), (x - xi)^2, (x - xi)^3] * coefs * [ 1; (y - yj); (y - yj)^2; (y - yj)^3];

    endfunction

    ImgFinal = FinalImg;  
endfunction
