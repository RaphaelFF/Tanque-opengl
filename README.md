 # Projeto OpenGL - Tanque em 3D
<img src="/imag/Captura de tela 2024-09-25 205756.png" alt="Descrição da imagem">
Este projeto utiliza a biblioteca OpenGL para renderizar um tanque 3D com movimentação e rotação interativa. O tanque pode ser controlado usando o teclado para simular uma visão de jogo, onde ele se move pelo ambiente, rotaciona a torre e o canhão, e interage com uma cena 3D.

## Funcionalidades

- Movimentação do tanque (para frente, para trás, rotacionar)
- Controle da torre e do canhão (movimentação e elevação)
- Renderização de texturas para o tanque, chão e cenário
- Visualização da cena em uma câmera dinâmica ajustável
- Alternância entre visão do tanque e visão aérea da cena
- Skybox 3D para criar um ambiente imersivo

## Controles

- `W`: Move o tanque para frente
- `S`: Move o tanque para trás
- `A`: Rotaciona o tanque para a esquerda
- `D`: Rotaciona o tanque para a direita
- `1`: Rotaciona a torre para a esquerda
- `2`: Rotaciona a torre para a direita
- `3`: Eleva o canhão
- `4`: Abaixa o canhão
- `T`: Alterna para a visão do tanque
- `Y`: Alterna para a visão aérea
- `P`: Alterna para visão de perseguição
- `O`: Alterna para visão livre

## Dependências

Para rodar o projeto, você precisará das seguintes bibliotecas:

- [OpenGL](https://www.opengl.org/) - Para renderização 3D
- [GLUT](https://www.opengl.org/resources/libraries/glut/) - Para o gerenciamento de janelas e entrada do teclado
- [SOIL](http://www.lonesock.net/soil.html) - Para o carregamento de texturas

### Instalação das Dependências no Ubuntu

Você pode instalar as dependências necessárias com os seguintes comandos:

```bash
sudo apt-get update
sudo apt-get install freeglut3-dev
sudo apt-get install libglew-dev
sudo apt-get install libsoil-dev

