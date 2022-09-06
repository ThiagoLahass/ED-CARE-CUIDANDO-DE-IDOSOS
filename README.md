<h1 align="center"> EDCare: ED Cuidando dos Idosos! </h1>
<p align="center">
<img src="http://img.shields.io/static/v1?label=VERSAO&message=v0.0.0&color=blue&style=for-the-badge"/>
</p>
<p align="center">
<img src="http://img.shields.io/static/v1?label=code_quality&message=C&color=res&style=for-the-badge"/>
</p>
<p align="center">
<img src="http://img.shields.io/static/v1?label=STATUS&message=CONCLUIDO&color=GREEN&style=for-the-badge"/>
</p>

# Visão Geral:
  Programa implemetado na linguagem 'C', fazendo uso de dados estruturados, como listas encadeadas e tipos opacos.
  O programa em questão tem como objetivo a criação de um programa,
denominado EdCare, que permite que os idosos formem uma rede de apoio, na qual
eles se ajudem, ou, em casos mais graves, sejam ajudados por cuidadores, de forma
que as ações são tomadas a partir de dados sensoriados de temperatura, queda e
localização dos idosos, assim como a localização dos cuidadores.

# Execução do programa:
  Todos os comandos devem ser dados a partir do diretório raiz, onde se encontra o arquivo Makefile.
Nesse mesmo diretório é necessário existir as pastas 'Entradas' e 'Saidas' para executar os testes.
Os arquivos onde estão os dados dos sensores devem estar na pasta 'Entradas'.
- **Para apagar os arquivos temporários:**
make clean
- **Para compilar os códigos e criar o executável:**
make

- **Para rodar o programa com o uso do Makefile:**
make run X=(numero de leituras que devem ser feitas)

- **Para rodar o programa diretamente:**
./bin/main (numero de leituras que devem ser feitas)


