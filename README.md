# **Trabalho Final - Laboratório de Programação**  
**Instituto Federal de Educação, Ciência e Tecnologia do Ceará (IFCE)**  

## **Descrição do Projeto**  
Este projeto tem como objetivo a **clusterização de imagens médicas** provenientes de exames de Papanicolau. O processo utiliza o algoritmo **K-means**, a **análise de silhueta** e um **leitor de imagens no formato PGM** (Textual P2 ou Binário P5).  

O código está estruturado de forma modular, seguindo o paradigma de **programação ligada (linkedizada)**, garantindo maior organização e reusabilidade das funções implementadas.  

---

## **Requisitos e Preparação**  
Antes de executar o programa, siga as etapas abaixo para garantir um funcionamento correto:  

1. **Obtenha as imagens no formato PGM**  
   - Faça o download da pasta contendo as imagens no formato **PGM P5 (Binário)**. Caso os arquivos estejam em outro formato, utilize um programa como o **GIMP** para convertê-los corretamente.  

2. **Configure o diretório das imagens**  
   - No arquivo `main.c`, defina o **caminho correto** para o diretório onde as imagens estão armazenadas.  

3. **Compilação do código**  
   - Para compilar o programa, utilize o seguinte comando no terminal:  
     ```sh
     make all
     ```
     - Caso esteja compilando no Windows:
     ```sh
     mingw32-make all
     ```
     Entre na pasta output ainda no terminal:
     ```sh
     cd C:\Users\seu\terminal\output
     ```
     e dentro da pasta digite para executar o programa:
     ```sh
     .\completo.exe
     ```
     Esse comando compila os arquivos necessários, ativando alertas e opções de depuração para facilitar a identificação de possíveis erros.
     Obs: Não se esqueça de instalar nas extensões o MakeFile para inserir o código make all
     Obs 2: O código lerPGM só aceita imagens do tipo P5. Se houver imagens P2 ou com cabeçalhos corrompidos, elas não serão carregadas.

4. **Execução e saída do programa**  
   - Após a execução, o programa criará uma **nova pasta de saída**, denominada por padrão **"Carcinoma_out"**.  
   - Todas as imagens processadas e clusterizadas estarão armazenadas nesta pasta para análise posterior.  

---

## **Referências e Links Úteis**  
- **Banco de imagens de exames de Papanicolau:**  
  [MDE-Lab - Aegean University](https://mde-lab.aegean.gr/index.php/downloads/)  

- **Métrica DICE (avaliação de segmentação de imagens):**  
  [ISBI 2014 Challenge - Universidade de Adelaide](https://cs.adelaide.edu.au/~carneiro/isbi14_challenge/)  
