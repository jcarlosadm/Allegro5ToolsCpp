parserShoeBoxAtlas
==================

*Uma maneira de tratar dados recebidos do programa Shoebox para uso em c++*

No ShoeBox:

1. Use a opção "Sprite Sheet" para criar um atlas
2. Nas configurações, escolha a opção "Default" na lista de engines
3. Em "fileFormatLoop", apague tudo e cole: SubTexture="@id" x="@x" y="@y" width="@w" height="@h" framex="@fx" framey="@fy" framew="@fw" frameh="@fh"\n
4. Em "fileFormatOuter", apague tudo e cole: @TexName width="@W" height="@H" \n@loop
5. Em "texPowerOfTwo", eu prefiro deixar false, para ficar menor.
6. Altere a extensão do arquivo gerado (não a imagem) para .txt
