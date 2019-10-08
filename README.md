# PEM-TESTER: Testador de Soluções do Projeto PEM

O problema de escalonamento de motoristas (PEM) é um problema computável que tem desafiado a computação por ser um tipo de problema de escalonamento muito complexo para ser solucionado por algoritmos exatos. A equipe deste projeto já teve alguns avanços científicos publicados em periódico internacional. Validar e avaliar as soluções obtidas também é um desafio pela sua complexidade. O objetivo deste projeto é desenvolver um testador de soluções para dar suporte as pesquisas que venham utilizar as instâncias do benchmark deste projeto (www.gpea.uem.br/benchmark.html).

### Installing

To build PEM-TESTER, you are going to need g++8.3.0 or later with C++17 support, CMake 3.13.4 or later, and LLVM 7.0. After installing all dependencies, it is a simple cmake/make usage:

```
mkdir build
cd build
cmake ..
make
sudo make install
```

Execute 

```
sudo apt install libgl-dev libglu-dev libglib2.0-dev libsm-dev libxrender-dev libfontconfig1-dev libxext-dev
```

If you get these errors

```
/usr/bin/ld: cannot find -lz 
collect2: error: ld returned 1 exit status
```

### Usage

```
pem-tester -i <caso-de-teste.txt> -o <solucao.yaml> -p <parametros.yaml> -s <solucao-amount>

```
