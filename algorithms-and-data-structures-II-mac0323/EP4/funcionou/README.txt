INFORMAÇÕES:
    NOME: Beatriz Viana Costa
    NUSP: 13673214


ARQUIVO DE LEITURA:
O arquivo de leitura dos dados deve estar disposto da seguinte maneira:
<Expressão regular>
<Quantidade N de palavras que se deseja verificar>
<N linhas, cada uma contendo uma palavra>

A expressão regular não deve conter nenhum espaço, a não ser que esse de fato faça parte da expressão desejada.


MODO DE EXECUÇÃO:
Para compilar o programa é necessário digitar o comando "make" no terminal.
Após isso, para a execução deste, é necessário indicar o arquivo de entrada da seguinte maneira:
$ ./ep4 <nome do arquivo>
O nome do arquivo deve ser indicado com a extensão .txt.
O resultado dado será dado na respectiva ordem das palavras presentes no arquivo de entrada.


OBSERVAÇÃO:
O programa não funciona corretamente para o seguinte exemplo fornecido no enunciado:
((A*CG | A*TA) | AAG*T)*
4
AACGTAAATA
CAAGA
ACGTA
AAAGT