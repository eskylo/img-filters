# Código de exemplo para propósito acadêmico
## Simples implementação C de uma calculadora
## estruturada em forma de projeto

Autor: Prof. Claudio Correa

## Resumo

Esse é um exemplo de implementação de uma calculadora
para as quatro operações aritméticas básicas, escrita 
em linguagem C, com o propósito de ilustrar a estrutura 
de desenvolvimento do projeto organizada em diretórios:

. include
. lib
. src

São disponibilizados recursos para gerar, automaticamente, 
os objetos para preparar uma biblioteca estática, compilar 
o código principal e ligar com a biblioteca para gerar o
executável final.

O procedimento pode ser realizado por meio das ferramentas
make (com auxílio do Makefile) e cmake (com auxílio do 
CMakeLists.txt)

IMPORTANTE: o código principal (<it>main()</it>) está em src

## make

Duas formas simples de gerar o executável:

<ul>
  <li>make calc</li>: compilação tradicional (sem gerar a biblioteca)</li>
  <li>make</li>: gera os objetos, a biblioteca estática e então, o executável</li>
</ul>

## cmake básico
### Ref.: <a href="https://cmake.org/examples">https://cmake.org/examples</a>
<ul>
  <li>	cmake -S . -B build</li>
  <li>	cmake --build build</li>
  <li>	cmake --build build --target test</li>
</ul>
### or
<ul>
  <li>	mkdir build && cd build</li>
  <li>	cmake .. && make VERBOSE=1</li>
  <li>	make test && doas make install/strip</li>
</ul>

A imagem apresenta a estrutura de diretórios:
 
 <img src="images/calcdirs.png">
 
## Descrição dos arquivos

CMakeLists.txt
Makefile
README.md
mycalc.pc.in

include:
calc.h

lib:
funcoesarit.c
funcoesaux.c

src:
calculadora.c

## git
### Ref.:

https://ilegra.com/blog/do-zero-git-github-como-criar-primeiro-repositorio-e-subir-seu-primeiro-projeto/#Instalacao_do_Git
https://ilegra.com/blog/do-zero-git-github-como-criar-primeiro-repositorio-e-subir-seu-primeiro-projeto/

http://devfuria.com.br/git/tutorial-para-iniciar-com-o-git-e-o-github/

https://medium.com/reprogramabr/git-e-github-por-onde-come%C3%A7ar-ca88a783c223#:~:text=Criando%20uma%20conta%20no%20GitHub,formul%C3%A1rio%20de%20cadastro%2C%20conforme%20imagem.

$ git config --global user.name "Your Name"
$ git config --global user.email "you@example.com"
