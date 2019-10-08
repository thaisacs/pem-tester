# PEM-TESTER: Testador de Soluções do Projeto PEM

O problema de escalonamento de motoristas (PEM) é um problema computável que tem desafiado a computação por ser um tipo de problema de escalonamento muito complexo para ser solucionado por algoritmos exatos. A equipe deste projeto já teve alguns avanços científicos publicados em periódico internacional. Validar e avaliar as soluções obtidas também é um desafio pela sua complexidade. O objetivo deste projeto é desenvolver um testador de soluções para dar suporte as pesquisas que venham utilizar as instâncias do benchmark deste projeto (www.gpea.uem.br/benchmark.html).

### Installing

To build PEM-TESTER, you are going to need g++7.1 or later with C++17 support, CMake 2.8 or later, and LLVM 7.0. After installing all dependencies, it is a simple cmake/make usage

```
mkdir build
cd build
cmake ..
make
sudo make install
```

### Usage

```
pem-tester -i <caso-de-teste.txt> -o <solucao.yaml> -p <parametros.yaml> -s <solucao-amount>

```
