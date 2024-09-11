A estratégia adotada foi criar uma tabela hash (hash table) onde cada posição armazena uma estrutura (struct) contendo uma string e um ponteiro para uma lista de inteiros. Ao adicionar uma nova palavra, a função de hashing calcula a posição correspondente na tabela e realiza as seguintes etapas:

Verificação da Posição:
Posição Vazia: Se a posição está vazia, a estrutura na tabela armazena a string da palavra e inicia uma lista de inteiros com o número do tweet em que a palavra apareceu.
Posição Ocupada:
Palavra Igual: Se a posição já está ocupada e a palavra que gerou o hash é igual àquela armazenada, o número do tweet é adicionado à lista de inteiros.
Palavra Diferente: Se a posição está ocupada e a palavra é diferente, a função realiza uma sondagem linear para encontrar uma nova posição. Durante a sondagem, a função pode retornar aos passos anteriores e tentar inserir a palavra em uma nova posição adequada.
