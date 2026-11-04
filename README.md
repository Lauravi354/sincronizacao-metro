# Sincronização do Metrô

Implementação em C de um sistema de sincronização entre passageiros e metrôs, utilizando threads POSIX, um mutex e variáveis de condição.

O programa controla a reserva de assentos e garante que o metrô só possa partir quando não houver passageiros embarcando e todas as vagas estiverem ocupadas ou não houver mais passageiros esperando.

## Arquivos

- `sync_car.c`: contém as funções de inicialização, espera por uma vaga, confirmação de embarque e carregamento do metrô.
- `sync_car.h`: contém a estrutura da estação e as declarações das quatro funções.
- `sync_car-runner.c`: programa de testes fornecido pelo professor. Contém a função `main` e inclui o cabeçalho `sync_car.h`.
- `makefile`: contém os comandos para compilar, executar e limpar os arquivos gerados.
- `README.md`: apresenta o projeto e as instruções de uso.

## Ambiente

O programa foi compilado e testado no Ubuntu pelo WSL, no Windows.

Para compilar, são necessários GCC, Make e suporte à biblioteca POSIX Threads. No Ubuntu, as ferramentas podem ser instaladas com:

```bash
sudo apt update
sudo apt install build-essential
```

## Compilação

No terminal, dentro da pasta do projeto, execute:

```bash
make
```

Os arquivos `sync_car.c` e `sync_car-runner.c` serão compilados separadamente e será gerado o executável `sync_car`.

## Execução dos testes

Execute:

```bash
./sync_car
```

Também é possível compilar e executar com:

```bash
make run
```

O teste do professor utiliza 100 passageiros e metrôs com quantidades aleatórias de assentos. Ele verifica situações sem passageiros, metrôs sem vagas, respeito à capacidade e espera pela confirmação de embarque.

Na execução realizada, os 100 passageiros embarcaram e todos os metrôs transportaram a quantidade esperada. O teste terminou com:

```text
Looks good!
```

Como as capacidades são aleatórias, os números exibidos podem mudar entre execuções. A aprovação nesse teste não garante, por si só, que todos os possíveis cenários de concorrência estejam corretos.

## Limpeza

Para remover o executável e os arquivos intermediários de compilação:

```bash
make clean
```

## Organização da sincronização

A estação mantém três contadores:

- `esperando`: passageiros aguardando uma vaga.
- `vagas`: assentos disponíveis para reserva.
- `embarcando`: passageiros com vaga reservada que ainda não confirmaram o embarque.

Um único mutex protege esses contadores. A condição `pode_embarcar` permite que passageiros aguardem vagas, enquanto `embarque_concluido` permite que o metrô aguarde o término do embarque.

As esperas utilizam `pthread_cond_wait`, evitando espera ocupada. O mutex é liberado durante essas esperas e durante o embarque, permitindo que vários passageiros estejam embarcando simultaneamente.